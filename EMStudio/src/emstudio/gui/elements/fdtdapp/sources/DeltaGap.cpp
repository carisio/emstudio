/*
 * DeltaGap.cpp
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#include "DeltaGap.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

DeltaGap::DeltaGap()
	: ElementsWithFacets(ElementTypeSmartPointer(new SourceType())) ,
	  colour(), excitation (), orientation(),
	  initialFrequency(), stepFrequency(), nFrequency(), visible() {


	colour.SetValue(wxColour(255,0,0));
//	resistance.SetExpression("50");
	orientation.SetValue(Z);
	initialFrequency.SetExpression("25");
	stepFrequency.SetExpression("5");
	nFrequency.SetExpression("10");
//	resistiveSource.SetValue(true);
	visible.SetValue(true);

	position.SetXExpression("25");
	position.SetYExpression("25");
	position.SetZExpression("25");

	SetPriority(HIGH);

//	BaseTypeValidatorSmartPointer validadorDoubleMaiorQueZero(new DoubleGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorOuIgualAZero(new DoubleGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidExcitation(new InvalidExcitationMEValidator);

	AddProperty(Property("Orientation", &orientation));
	AddProperty(Property("Position", &position, validadorInvalidPoint3D));
	AddProperty(Property("Excitation", &excitation, validadorInvalidExcitation));
//	AddProperty(Property("Resistive source?", &resistiveSource));
//	AddProperty(Property("Source resistance", &resistance, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Initial Frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &stepFrequency, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Color", &colour));
	AddProperty(Property("Visible?", &visible));
}

DeltaGap::~DeltaGap() {

}

ElementGUISmartPointer DeltaGap::NewElementGUI() {
	return ElementGUISmartPointer(new DeltaGap());
}

wxString DeltaGap::GetRegisteredName() {
	return "Delta Gap";
}

wxIcon DeltaGap::GetIcon() {
	return UtilResource::GetIcon("deltagap");
}

ElementDTOSmartPointer DeltaGap::NewElementDTO() {
	DeltaGapDTO* result = new DeltaGapDTO;
	result->SetExcitation(excitation.ConvertToExcitation());
	position.EvalExpressions();
	result->SetX(position.GetX());
	result->SetY(position.GetY());
	result->SetZ(position.GetZ());
//	result->SetResistance(resistance.ForceEval());
	result->SetOrientation(orientation);
	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(stepFrequency.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());
//	result->SetResistiveSource(resistiveSource.IsValue());

	return ElementDTOSmartPointer(result);
}


bool DeltaGap::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	position.EvalExpressions();
	xmin = xmax = position.GetX();
	ymin = ymax = position.GetY();
	zmin = zmax = position.GetZ();


	return true;
}

void DeltaGap::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
	SetColor(colour.GetValue());
	position.EvalExpressions();
	DrawPoint(position.GetX(), position.GetY(), position.GetZ(), 10);
//	EnableLight();
}

bool DeltaGap::IsAllPropertiesTogetherValid() {
//	wxString errorMessage;
//	bool valid = true;
//
//	if (resistiveSource.IsValue() && resistance.ForceEval() == 0) {
//		errorMessage.Append("Resistance should be greater than 0 when Resistive Source is checked/\n");
//		valid = false;
//	}
//
//	SetAllPropertiesTogetherErrorMessage(errorMessage);
//	return valid;
	return true;
}

void DeltaGap::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + position.GetXExpression() + ") + " + px;
	wxString y = "(" + position.GetYExpression() + ") + " + py;
	wxString z = "(" + position.GetZExpression() + ") + " + pz;
	position.SetXExpression(x);
	position.SetYExpression(y);
	position.SetZExpression(z);
}
