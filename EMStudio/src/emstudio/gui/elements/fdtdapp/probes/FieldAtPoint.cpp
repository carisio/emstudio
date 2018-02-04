/*
 * FieldAtPoint.cpp
 *
 *  Created on: 02/03/2012
 *      Author: Administrador
 */

#include "FieldAtPoint.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

FieldAtPoint::FieldAtPoint()
	: ElementsWithFacets(ElementTypeSmartPointer(new ProbeType())) {

	color.SetValue(wxColour(0,0,255));
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer validadorInteiroMaiorQueZero(new IntGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorQueZero(new DoubleGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorOuIgualAZero(new DoubleGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	initialFrequency.SetExpression("25");
	frequencyStep.SetExpression("5");
	nFrequency.SetExpression("10");

	AddProperty(Property("Point", &point, validadorInvalidPoint3D));
	AddProperty(Property("Initial frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &frequencyStep, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Time response?", &timeResponse));
	AddProperty(Property("Color", &color));
	AddProperty(Property("Visible?", &visible));
}

FieldAtPoint::~FieldAtPoint() {
}


ElementGUISmartPointer FieldAtPoint::NewElementGUI() {
	return ElementGUISmartPointer(new FieldAtPoint());
}

wxString FieldAtPoint::GetRegisteredName() {
	return "Field at Point";
}

wxIcon FieldAtPoint::GetIcon() {
	return UtilResource::GetIcon("fieldatpoint");
}

ElementDTOSmartPointer FieldAtPoint::NewElementDTO() {
	FieldAtPointDTO* result = new FieldAtPointDTO;
	point.EvalExpressions();
	result->SetX(point.GetX());
	result->SetY(point.GetY());
	result->SetZ(point.GetZ());
	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(frequencyStep.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());
	result->SetShowTimeResponse(timeResponse.IsValue());

	return ElementDTOSmartPointer(result);

}

bool FieldAtPoint::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	point.EvalExpressions();
	xmin = xmax = point.GetX();
	ymin = ymax = point.GetY();
	zmin = zmax = point.GetZ();


	return true;
}

void FieldAtPoint::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
	point.EvalExpressions();
	SetColor(color.GetValue());
	DrawPoint(point.GetX(), point.GetY(), point.GetZ(), 10);
//	EnableLight();
}
void FieldAtPoint::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + point.GetXExpression() + ") + " + px;
	wxString y = "(" + point.GetYExpression() + ") + " + py;
	wxString z = "(" + point.GetZExpression() + ") + " + pz;
	point.SetXExpression(x);
	point.SetYExpression(y);
	point.SetZExpression(z);
}
