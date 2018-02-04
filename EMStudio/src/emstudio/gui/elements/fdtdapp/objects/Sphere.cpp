/*
 * Sphere.cpp
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#include "Sphere.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/constants/Constants.h"

Sphere::Sphere()
	: ElementsWithFacets(ElementTypeSmartPointer(new Object3DType())) ,
	  center(), innerRadius(), outerRadius(), showSolid(), visible() {

	center.SetXExpression("25"); center.SetYExpression("25"); center.SetZExpression("25");
	innerRadius.SetExpression("0");
	outerRadius.SetExpression("10");
//	colour.SetValue(wxColour(0,0,255));
	showSolid.SetValue(false);
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddPriorityProperty(MINIMUM);
	AddProperty(Property("Center", &center, validadorInvalidPoint3D));
	AddProperty(Property("Outer Radius", &outerRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Inner Radius", &innerRadius, validadorMathExpressionMaiorOuIgualAZero));
	AddMaterialProperty("Material", "PEC");
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));
}

Sphere::~Sphere() {

}

ElementGUISmartPointer Sphere::NewElementGUI() {
	return ElementGUISmartPointer(new Sphere());
}

wxString Sphere::GetRegisteredName() {
	return "Sphere";
}

wxIcon Sphere::GetIcon() {
	return UtilResource::GetIcon("sphere");
}

ElementDTOSmartPointer Sphere::NewElementDTO() {
	SphereDTO* result = new SphereDTO();
	result->SetX(center.GetX());
	result->SetY(center.GetY());
	result->SetZ(center.GetZ());
	result->SetOuterRadius(outerRadius.ForceEval());
	result->SetInnerRadius(innerRadius.ForceEval());

	return ElementDTOSmartPointer(result);
}

bool Sphere::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	center.EvalExpressions();
	xmin = xmax = center.GetX();
	ymin = ymax = center.GetY();
	zmin = zmax = center.GetZ();

	double outerRadius_dbl = outerRadius.ForceEval();
	double innerRadius_dbl = innerRadius.ForceEval();

	xmin -= outerRadius_dbl;
	ymin -= outerRadius_dbl;
	zmin -= outerRadius_dbl;

	xmax += outerRadius_dbl;
	ymax += outerRadius_dbl;
	zmax += outerRadius_dbl;

	return true;
}

void Sphere::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
		return;
	SetColor(GetMaterialColor());
	DrawPolygons(GetFacets(), showSolid.IsValue());
//

/*
	if (!visible.IsValue())
	  return;
	bool fill = showSolid.IsValue();

	center.EvalExpressions();
	double outerRadius_dbl = outerRadius.ForceEval();
	double innerRadius_dbl = innerRadius.ForceEval();

	if (innerRadius_dbl > 0) {
		SetColor(wxColour(255,255,255));
		DrawSphere(innerRadius_dbl, center.GetX(), center.GetY(), center.GetZ(), 0, 0, 0, 0, fill);
	}
//	SetColor(colour.GetValue());
	SetColor(GetMaterialColor());
	DrawSphere(outerRadius_dbl, center.GetX(), center.GetY(), center.GetZ(), 0, 0, 0, 0, fill);
	*/
}

bool Sphere::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	double outerRadius_dbl = outerRadius.ForceEval();
	double innerRadius_dbl = innerRadius.ForceEval();

	if (outerRadius_dbl <= innerRadius_dbl) {
		errorMessage.Append("Outer Radius should be greater than Inner Radius.\n");
		valid = false;
	}

	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}
vector<Facet> Sphere::GetFacet(double radius) {
	vector<Facet> facets;
	center.EvalExpressions();

	double x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,phi1,phi2,theta;

	int segments = 32;
	for (int i = 0; i < segments ; i++)	{
		phi1 = i*PI/segments;
		z1 = center.GetZ() + radius * cos(phi1);
		phi2 = (i+1)*PI/segments;
		z2 = center.GetZ() + radius * cos(phi2);

		for (int j = 0; j < segments; j++) {
			theta = 2*PI*j/segments;
			x1 = center.GetX() + radius * sin(phi1) * sin(theta);
			y1 = center.GetY() + radius * sin(phi1) * cos(theta);
			x2 = center.GetX() + radius * sin(phi2) * sin(theta);
			y2 = center.GetY() + radius * sin(phi2) * cos(theta);

			theta = 2*PI*(j+1)/segments;
			x3 = center.GetX() + radius * sin(phi1) * sin(theta);
			y3 = center.GetY() + radius * sin(phi1) * cos(theta);
			x4 = center.GetX() + radius * sin(phi2) * sin(theta);
			y4 = center.GetY() + radius * sin(phi2) * cos(theta);

			Facet facet;
			facet.Add(Rvector3(x1,y1,z1));
			facet.Add(Rvector3(x2,y2,z2));
			facet.Add(Rvector3(x4,y4,z2));
			facet.Add(Rvector3(x3,y3,z1));

			facets.push_back(facet);
		}
	}

	return facets;

}
vector<Facet> Sphere::BuildFacets() {
	vector<Facet> facets = GetFacet(outerRadius.ForceEval());
	vector<Facet> innerFacets = GetFacet(innerRadius.ForceEval());

	for (size_t i = 0; i < innerFacets.size(); i++) {
		facets.push_back(innerFacets[i]);
	}


	return facets;

}
void Sphere::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + center.GetXExpression() + ") + " + px;
	wxString y = "(" + center.GetYExpression() + ") + " + py;
	wxString z = "(" + center.GetZExpression() + ") + " + pz;
	center.SetXExpression(x);
	center.SetYExpression(y);
	center.SetZExpression(z);
}
