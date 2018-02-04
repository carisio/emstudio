/*
 * RadiationPattern.cpp
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#include "RadiationPattern.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"

RadiationPattern::RadiationPattern() : ElementsWithFacets(ElementTypeSmartPointer(new ProbeType())) {

	initialFrequency.SetExpression("25");
	frequencyStep.SetExpression("0");
	nFrequency.SetExpression("1");
	colour.SetValue(wxColour(255,0,0));
	visible.SetValue(true);
	lowerBoundary.SetXExpression("10"); lowerBoundary.SetYExpression("10"); lowerBoundary.SetZExpression("10");
	upperBoundary.SetXExpression("40"); upperBoundary.SetYExpression("40"); upperBoundary.SetZExpression("40");

	BaseTypeValidatorSmartPointer validadorNFrequency(new MathExpressionInTheIntervalValidator(1, 10));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddProperty(Property("Lower Boundary", &lowerBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Upper Boundary", &upperBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Initial frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &frequencyStep, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorNFrequency));
	AddProperty(Property("Color", &colour));
	AddProperty(Property("Visible?", &visible));
}

RadiationPattern::~RadiationPattern() {
}


ElementGUISmartPointer RadiationPattern::NewElementGUI() {
	return ElementGUISmartPointer(new RadiationPattern());
}

wxString RadiationPattern::GetRegisteredName() {
	return "Radiation Pattern";
}

wxIcon RadiationPattern::GetIcon() {
	return UtilResource::GetIcon("radiationpattern");
}

ElementDTOSmartPointer RadiationPattern::NewElementDTO() {
	RadiationPatternDTO* result = new RadiationPatternDTO;

	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(frequencyStep.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	result->SetXmin(lowerBoundary.GetX());
	result->SetXmax(upperBoundary.GetX());
	result->SetYmin(lowerBoundary.GetY());
	result->SetYmax(upperBoundary.GetY());
	result->SetZmin(lowerBoundary.GetZ());
	result->SetZmax(upperBoundary.GetZ());


	return ElementDTOSmartPointer(result);
}

bool RadiationPattern::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;
	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	xmin = this->lowerBoundary.GetX();
	ymin = this->lowerBoundary.GetY();
	zmin = this->lowerBoundary.GetZ();
	xmax = this->upperBoundary.GetX();
	ymax = this->upperBoundary.GetY();
	zmax = this->upperBoundary.GetZ();

	return true;
}

void RadiationPattern::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
	SetColor(colour.GetValue());

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();

	DrawPlaneX(lowerBoundary.GetY(), lowerBoundary.GetZ(), upperBoundary.GetY(), upperBoundary.GetZ(), lowerBoundary.GetX());
	DrawPlaneX(lowerBoundary.GetY(), lowerBoundary.GetZ(), upperBoundary.GetY(), upperBoundary.GetZ(), upperBoundary.GetX());

	DrawPlaneY(lowerBoundary.GetX(), lowerBoundary.GetZ(), upperBoundary.GetX(), upperBoundary.GetZ(), lowerBoundary.GetY());
	DrawPlaneY(lowerBoundary.GetX(), lowerBoundary.GetZ(), upperBoundary.GetX(), upperBoundary.GetZ(), upperBoundary.GetY());

	DrawPlaneZ(lowerBoundary.GetX(), lowerBoundary.GetY(), upperBoundary.GetX(), upperBoundary.GetY(), lowerBoundary.GetZ());
	DrawPlaneZ(lowerBoundary.GetX(), lowerBoundary.GetY(), upperBoundary.GetX(), upperBoundary.GetY(), upperBoundary.GetZ());
//	EnableLight();
}

bool RadiationPattern::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;

	valid = CheckBoundaries(lowerBoundary, upperBoundary, errorMessage, "Lower Boundary", "Upper Boundary");

	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

void RadiationPattern::DoMove(Point3DME p) {
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
