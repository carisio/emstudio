/*
 * FieldAtPath.cpp
 *
 *  Created on: 21/03/2012
 *      Author: Leandro
 */

#include "FieldAtPath.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

FieldAtPath::FieldAtPath() : ElementsWithFacets(ElementTypeSmartPointer(new ProbeType())) ,
	colour(), length(), orientation(), visible() {

	positionBottom.SetXExpression("25"); positionBottom.SetYExpression("25"); positionBottom.SetZExpression("1");
	length.SetExpression("25");
	colour.SetValue(wxColour(0,0,255));
	visible.SetValue(true);

	initialFrequency.SetExpression("25");
	frequencyStep.SetExpression("0");
	nFrequency.SetExpression("1");

	BaseTypeValidatorSmartPointer validadorInteiroMaiorQueZero(new IntGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorQueZero(new DoubleGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInteiroEntre1E10(new MathExpressionInTheIntervalValidator(1,10));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorOuIgualAZero(new DoubleGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddProperty(Property("Orientation", &orientation));
	AddProperty(Property("Position (bottom)", &positionBottom, validadorInvalidPoint3D));
	AddProperty(Property("Length", &length, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Initial frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &frequencyStep, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorInteiroEntre1E10));
	AddProperty(Property("Color", &colour));
	AddProperty(Property("Visible?", &visible));
}

FieldAtPath::~FieldAtPath() {

}


ElementGUISmartPointer FieldAtPath::NewElementGUI() {
	return ElementGUISmartPointer(new FieldAtPath());
}

wxString FieldAtPath::GetRegisteredName() {
	return "Field at Path";
}

wxIcon FieldAtPath::GetIcon() {
	return UtilResource::GetIcon("fieldatpath");
}

ElementDTOSmartPointer FieldAtPath::NewElementDTO() {
	FieldAtPathDTO* result = new FieldAtPathDTO;
	positionBottom.EvalExpressions();
	result->SetX(positionBottom.GetX());
	result->SetY(positionBottom.GetY());
	result->SetZ(positionBottom.GetZ());
	result->SetLength(length.ForceEval());
	result->SetOrientation(orientation);
	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(frequencyStep.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());
	return ElementDTOSmartPointer(result);
}

bool FieldAtPath::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	positionBottom.EvalExpressions();
	xmin = xmax = positionBottom.GetX();
	ymin = ymax = positionBottom.GetY();
	zmin = zmax = positionBottom.GetZ();

	bool negativeLength = length.ForceEval() < 0;
	if (orientation.GetValue() == X) {
		if (negativeLength)
			xmin += length.ForceEval();
		else
			xmax += length.ForceEval();
	} else if (orientation.GetValue() == Y) {
		if (negativeLength)
			ymin += length.ForceEval();
		else
			ymax += length.ForceEval();
	} else if (orientation.GetValue() == Z) {
		if (negativeLength)
			zmin += length.ForceEval();
		else
			zmax += length.ForceEval();
	}
	return true;
}

void FieldAtPath::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

	SetColor(colour.GetValue());

	double x1, x2, y1, y2, z1, z2;
	positionBottom.EvalExpressions();
	x1 = x2 = positionBottom.GetX();
	y1 = y2 = positionBottom.GetY();
	z1 = z2 = positionBottom.GetZ();

	if (orientation.GetValue() == X) {
		x2 = x1 + length.ForceEval();
	} else if (orientation.GetValue() == Y) {
		y2 = y1 + length.ForceEval();
	} else if (orientation.GetValue() == Z) {
		z2 = z1 + length.ForceEval();
	}

	DrawLine(x1, y1, z1, x2, y2, z2, 3);
}
void FieldAtPath::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + positionBottom.GetXExpression() + ") + " + px;
	wxString y = "(" + positionBottom.GetYExpression() + ") + " + py;
	wxString z = "(" + positionBottom.GetZExpression() + ") + " + pz;
	positionBottom.SetXExpression(x);
	positionBottom.SetYExpression(y);
	positionBottom.SetZExpression(z);
}
