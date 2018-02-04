/*
 * Cube.cpp
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#include "Box.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"

Box::Box()
	: ElementsWithFacets(ElementTypeSmartPointer(new Object3DType())) {

	this->visible = BoolWrapper();

	lowerBoundary.SetXExpression("10"); lowerBoundary.SetYExpression("10"); lowerBoundary.SetZExpression("10");
	upperBoundary.SetXExpression("40"); upperBoundary.SetYExpression("40"); upperBoundary.SetZExpression("40");

	showSolid.SetValue(true);
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddPriorityProperty(MINIMUM);
	AddProperty(Property("Lower Boundary", &lowerBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Upper Boundary", &upperBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Rotate", &rotateAxis, validadorInvalidPoint3D));
	AddProperty(Property("Translate", &translateTo, validadorInvalidPoint3D));
	AddProperty(Property("Match with PML", &matchWithPML));
	AddMaterialProperty("Material", "PEC");
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));
}

Box::~Box() {
}

ElementGUISmartPointer Box::NewElementGUI() {
	return ElementGUISmartPointer(new Box());
}

wxString Box::GetRegisteredName() {
	return "Box";
}

wxIcon Box::GetIcon() {
	return UtilResource::GetIcon("box");
}

ElementDTOSmartPointer Box::NewElementDTO() {
	BoxDTO* result = new BoxDTO;

//	Diferentemente dos outros objetos, nesse caso é necessário levar também o que o usuário digitou, pq isso será usado lá no core
//  caso o casamento com a pml tenha sido feita
	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	rotateAxis.EvalExpressions();

	result->SetX1(lowerBoundary.GetX());
	result->SetY1(lowerBoundary.GetY());
	result->SetZ1(lowerBoundary.GetZ());
	result->SetX2(upperBoundary.GetX());
	result->SetY2(upperBoundary.GetY());
	result->SetZ2(upperBoundary.GetZ());
	result->SetMatchWithPML(matchWithPML);

	return ElementDTOSmartPointer(result);
}

/* Depois do rotate tem que deixar no automático */
//bool Box::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
//	if (!visible.IsValue())
//		return false;
//
//	lowerBoundary.EvalExpressions();
//	upperBoundary.EvalExpressions();
//	rotateAxis.EvalExpressions();
//
//	xmin = lowerBoundary.GetX();
//	xmax = upperBoundary.GetX();
//	ymin = lowerBoundary.GetY();
//	ymax = upperBoundary.GetY();
//	zmin = lowerBoundary.GetZ();
//	zmax = upperBoundary.GetZ();
//
//	return true;
//}
bool Box::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	FillApproximateDimensionsWithFacets(xmin, ymin, zmin, xmax, ymax, zmax);
	return true;
}
void Box::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	cout << "Chamando Box::Draw" << endl;
	SetColor(GetMaterialColor());
//	cout << "Cor selecionada: " << (int)GetMaterialColor().Red() << ", " << (int)GetMaterialColor().Green() << ", " << (int)GetMaterialColor().Blue() << endl;
	DrawPolygons(GetFacets(), showSolid.IsValue());
}

bool Box::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;

	valid = CheckBoundaries(lowerBoundary, upperBoundary, errorMessage, "Lower Boundary", "Upper Boundary");

	bool matchedWithPML = matchWithPML.IsMatchedWithPML(xNeg | yNeg | zNeg | xPos | yPos | zPos);
	bool rotated = (rotateAxis.GetX() != 0 || rotateAxis.GetY() != 0 || rotateAxis.GetZ() != 0);
	bool translated = (translateTo.GetX() != 0 || translateTo.GetY() != 0 || translateTo.GetZ() != 0);
	if (matchedWithPML && (rotated || translated)) {
		valid = false;
		errorMessage.Append("Unset rotate and translate to match the box with PML\n");
	}

	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

vector<Facet> Box::BuildFacets() {
	vector<Facet> facets;

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	rotateAxis.EvalExpressions();

	double xmin = lowerBoundary.GetX();
	double ymin = lowerBoundary.GetY();
	double zmin = lowerBoundary.GetZ();
	double xmax = upperBoundary.GetX();
	double ymax = upperBoundary.GetY();
	double zmax = upperBoundary.GetZ();

	Facet f1;
	f1.Add(Rvector3(xmin, ymin, zmin));
	f1.Add(Rvector3(xmax,ymin,zmin));
	f1.Add(Rvector3(xmax,ymax,zmin));
	f1.Add(Rvector3(xmin,ymax,zmin));
	facets.push_back(f1);

	Facet f2;
	f2.Add(Rvector3(xmin, ymin, zmin));
	f2.Add(Rvector3(xmin,ymax,zmin));
	f2.Add(Rvector3(xmin,ymax,zmax));
	f2.Add(Rvector3(xmin,ymin,zmax));
	facets.push_back(f2);

	Facet f3;
	f3.Add(Rvector3(xmin, ymin, zmin));
	f3.Add(Rvector3(xmax,ymin,zmin));
	f3.Add(Rvector3(xmax,ymin,zmax));
	f3.Add(Rvector3(xmin,ymin,zmax));
	facets.push_back(f3);

	Facet f4;
	f4.Add(Rvector3(xmax, ymax, zmax));
	f4.Add(Rvector3(xmin,ymax,zmax));
	f4.Add(Rvector3(xmin,ymin,zmax));
	f4.Add(Rvector3(xmax,ymin,zmax));
	facets.push_back(f4);

	Facet f5;
	f5.Add(Rvector3(xmax, ymax, zmax));
	f5.Add(Rvector3(xmax,ymin,zmax));
	f5.Add(Rvector3(xmax,ymin,zmin));
	f5.Add(Rvector3(xmax,ymax,zmin));
	facets.push_back(f5);

	Facet f6;
	f6.Add(Rvector3(xmax, ymax, zmax));
	f6.Add(Rvector3(xmin,ymax,zmax));
	f6.Add(Rvector3(xmin,ymax,zmin));
	f6.Add(Rvector3(xmax,ymax,zmin));
	facets.push_back(f6);

	rotateAxis.EvalExpressions();
	translateTo.EvalExpressions();

	RotateFacets(facets, Rvector3((xmin+xmax)/2,(ymin+ymax)/2,(zmin+zmax)/2), rotateAxis.GetX(), rotateAxis.GetY(), rotateAxis.GetZ());
	TranslateFacets(facets,translateTo.GetX(), translateTo.GetY(), translateTo.GetZ());

	return facets;
}
void Box::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString xl = "(" + lowerBoundary.GetXExpression() + ") + " + px;
	wxString yl = "(" + lowerBoundary.GetYExpression() + ") + " + py;
	wxString zl = "(" + lowerBoundary.GetZExpression() + ") + " + pz;
	wxString xu = "(" + upperBoundary.GetXExpression() + ") + " + px;
	wxString yu = "(" + upperBoundary.GetYExpression() + ") + " + py;
	wxString zu = "(" + upperBoundary.GetZExpression() + ") + " + pz;
	lowerBoundary.SetXExpression(xl);
	lowerBoundary.SetYExpression(yl);
	lowerBoundary.SetZExpression(zl);
	upperBoundary.SetXExpression(xu);
	upperBoundary.SetYExpression(yu);
	upperBoundary.SetZExpression(zu);
}
