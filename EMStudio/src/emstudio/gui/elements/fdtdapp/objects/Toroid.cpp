/*
 * Toroid.cpp
 *
 *  Created on: 29/09/2011
 *      Author: Leandro
 */

#include "Toroid.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/resources/UtilResource.h"

Toroid::Toroid() : ElementsWithFacets(ElementTypeSmartPointer(new Object3DType())) ,
//	colour(),
	toroidRadius(), wireRadius(),
	orientation(), showSolid(), visible() {

//	colour.SetValue(wxColour(0, 0, 255));
	orientation.SetValue(Z);
	center.SetXExpression("25"); center.SetYExpression("25"); center.SetZExpression("25");
	toroidRadius.SetExpression("15"); wireRadius.SetExpression("5");
	showSolid.SetValue(false);
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddPriorityProperty(MINIMUM);
	AddProperty(Property("Orientation", &orientation));
	AddProperty(Property("Center", &center, validadorInvalidPoint3D));
	AddProperty(Property("Toroid radius", &toroidRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Wire radius", &wireRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Rotate", &rotateAxis, validadorInvalidPoint3D));
	AddProperty(Property("Translate", &translateTo, validadorInvalidPoint3D));
	AddMaterialProperty("Material", "PEC");
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));

}

Toroid::~Toroid() {

}

ElementGUISmartPointer Toroid::NewElementGUI() {
	return ElementGUISmartPointer(new Toroid());
}

wxString Toroid::GetRegisteredName() {
	return "Toroid";
}

wxIcon Toroid::GetIcon() {
	return UtilResource::GetIcon("toroid");
}

ElementDTOSmartPointer Toroid::NewElementDTO() {
	ToroidDTO* result = new ToroidDTO;

//	Não precisa disso, pois agora o que interessa são as faces
//	result->SetToroidRadius(toroidRadius.ForceEval());
//	result->SetOrientation(orientation);
//	result->SetWireRadius(wireRadius.ForceEval());
//	result->SetX(center.GetX());
//	result->SetY(center.GetY());
//	result->SetZ(center.GetZ());

	return ElementDTOSmartPointer(result);
}


bool Toroid::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	FillApproximateDimensionsWithFacets(xmin, ymin, zmin, xmax, ymax, zmax);
	return true;
}

void Toroid::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	SetColor(colour.GetValue());
	SetColor(GetMaterialColor());
	DrawPolygons(GetFacets(), showSolid.IsValue());
}

bool Toroid::IsAllPropertiesTogetherValid() {
//	wxString errorMessage;
	bool valid = true;;

//	if (outerRadius.GetValue() <= innerRadius.GetValue()) {
//		errorMessage.Append("Outer Radius should be greater than Inner Radius.\n");
//		valid = false;
//	}
//
//	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

vector<Facet> Toroid::BuildFacets() {
	vector<Facet> facets;

	double x1,x2,x3,x4;
	double y1,y2,y3,y4;
	double z1,z2,z3,z4;
	double phi,theta, u,v;

	Facet face;

	double toroidRadius_dbl = toroidRadius.ForceEval();
	double wireRadius_dbl = wireRadius.ForceEval();
	center.EvalExpressions();
	rotateAxis.EvalExpressions();

	//Toroide;
	double segments = 32;
	for(phi = 0; phi < 360.0; phi += 360.0/segments) {
		for(theta = 0; theta < 360; theta += 360/segments) {
			v = (phi/180.0*PI);
			u = (theta/180.0*PI);
			x1 = center.GetX() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y1 = center.GetY() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z1 = center.GetZ() + sin(v)*wireRadius_dbl;
			u = ((theta+360/segments)/180.0*PI);
			x2 = center.GetX() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y2 = center.GetY() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z2 = center.GetZ() + sin(v)*wireRadius_dbl;
			v = ((phi+360/segments)/180.0*PI);
			x3 = center.GetX() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y3 = center.GetY() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z3 = center.GetZ() + sin(v)*wireRadius_dbl;
			u = (theta/180.0*PI);
			x4 = center.GetX() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y4 = center.GetY() + (toroidRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z4 = center.GetZ() + sin(v)*wireRadius_dbl;

			face = Facet();
			face.Add(Rvector3(x1,y1,z1));
			face.Add(Rvector3(x2,y2,z2));
			face.Add(Rvector3(x3,y3,z3));
			face.Add(Rvector3(x4,y4,z4));
			facets.push_back(face);
	    }
	}


	if (orientation.GetValue() == X) {
		RotateFacets(facets, Rvector3(center.GetX(), center.GetY(), center.GetZ()), 0, 90, 0);
	} else if (orientation.GetValue() == Y) {
		RotateFacets(facets, Rvector3(center.GetX(), center.GetY(), center.GetZ()), -90, 0, 0);
	}

	rotateAxis.EvalExpressions();
	translateTo.EvalExpressions();

	RotateFacets(facets,rotateAxis.GetX(), rotateAxis.GetY(), rotateAxis.GetZ());
	TranslateFacets(facets,translateTo.GetX(), translateTo.GetY(), translateTo.GetZ());

	return facets;
}
void Toroid::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + center.GetXExpression() + ") + " + px;
	wxString y = "(" + center.GetYExpression() + ") + " + py;
	wxString z = "(" + center.GetZExpression() + ") + " + pz;
	center.SetXExpression(x);
	center.SetYExpression(y);
	center.SetZExpression(z);
}
