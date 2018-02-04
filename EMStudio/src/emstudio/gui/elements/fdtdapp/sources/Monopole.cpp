/*
 * Monopole.cpp
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#include "Monopole.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

Monopole::Monopole()
	: ElementsWithFacets(ElementTypeSmartPointer(new SourceType())) ,
	  excitation (), length(), orientation(),
	  linePoints(), sourcePoints(), wireRadius(), lineImpedance(), //velocityFactor(),
	  initialFrequency(), frequencyStep(), nFrequency(), showSolid(), visible() {

	lineImpedance.SetExpression("50");
//	colour.SetValue(wxColour(255,0,0));
	positionBottom.SetXExpression("25"); positionBottom.SetYExpression("25"); positionBottom.SetZExpression("1");
	length.SetExpression("25");
	linePoints.SetValue(100); sourcePoints.SetValue(90);
	wireRadius.SetExpression("1");
//	velocityFactor.SetValue(0.7);
	orientation.SetValue(Z);
	initialFrequency.SetExpression("25");
	frequencyStep.SetExpression("5");
	nFrequency.SetExpression("10");
	showSolid.SetValue(true);
	visible.SetValue(true);

	SetPriority(HIGH);

	BaseTypeValidatorSmartPointer validadorInteiroMaiorQueZero(new IntGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorQueZero(new DoubleGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorOuIgualAZero(new DoubleGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidExcitation(new InvalidExcitationMEValidator);

	AddProperty(Property("Orientation", &orientation));
	AddProperty(Property("Position (bottom)", &positionBottom, validadorInvalidPoint3D));
	AddProperty(Property("Length", &length, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Wire radius", &wireRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Excitation", &excitation, validadorInvalidExcitation));
	AddProperty(Property("Line impedance", &lineImpedance, validadorMathExpressionMaiorQueZero));
//	AddProperty(Property("Line points", &linePoints));
//	AddProperty(Property("Source points", &sourcePoints));
//	AddProperty(Property("Velocity factor", &velocityFactor));
	AddProperty(Property("Initial frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &frequencyStep, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorMathExpressionMaiorQueZero));
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));

}

Monopole::~Monopole() {
}


ElementGUISmartPointer Monopole::NewElementGUI() {
	return ElementGUISmartPointer(new Monopole());
}

wxString Monopole::GetRegisteredName() {
	return "Monopole";
}

wxIcon Monopole::GetIcon() {
	return UtilResource::GetIcon("monopole");
}

ElementDTOSmartPointer Monopole::NewElementDTO() {
	MonopoleDTO* result = new MonopoleDTO;

	result->SetExcitation(excitation.ConvertToExcitation());
	positionBottom.EvalExpressions();
	result->SetX(positionBottom.GetX());
	result->SetY(positionBottom.GetY());
	result->SetZ(positionBottom.GetZ());
	result->SetLength(length.ForceEval());
	result->SetOrientation(orientation);
	result->SetLinePoints(linePoints.GetValue());
	result->SetSourcePoints(sourcePoints.GetValue());
	result->SetWireRadius(wireRadius.ForceEval());
	result->SetLineImpedance(lineImpedance.ForceEval());
	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(frequencyStep.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());

	return ElementDTOSmartPointer(result);
}

bool Monopole::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	positionBottom.EvalExpressions();
	xmin = xmax = positionBottom.GetX();
	ymin = ymax = positionBottom.GetY();
	zmin = zmax = positionBottom.GetZ();

	double length_dbl = length.ForceEval();
	double wireRadius_dbl = wireRadius.ForceEval();


	bool negativeLength = length_dbl < 0;
	if (orientation.GetValue() == X) {
		if (negativeLength)
			xmin += length_dbl;
		else
			xmax += length_dbl;
		ymin -= wireRadius_dbl*1.5;
		ymax += wireRadius_dbl*1.5;
		zmin -= wireRadius_dbl*1.5;
		zmax += wireRadius_dbl*1.5;
	} else if (orientation.GetValue() == Y) {
		if (negativeLength)
			ymin += length_dbl;
		else
			ymax += length_dbl;
		xmin -= wireRadius_dbl*1.5;
		xmax += wireRadius_dbl*1.5;
		zmin -= wireRadius_dbl*1.5;
		zmax += wireRadius_dbl*1.5;
	} else if (orientation.GetValue() == Z) {
		if (negativeLength)
			zmin += length_dbl;
		else
			zmax += length_dbl;
		xmin -= wireRadius_dbl*1.5;
		xmax += wireRadius_dbl*1.5;
		ymin -= wireRadius_dbl*1.5;
		ymax += wireRadius_dbl*1.5;
	}
	return true;
}

void Monopole::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
		  return;

//	SetColor(colour.GetValue());
	SetColor(GetPECColor());

	double rotx = 0;
	double roty = 0;
	double rotz = 0;
	double angle = 90;

	if (orientation.GetValue() == X) {
		roty = 1;
	} else if (orientation.GetValue() == Y) {
		rotx = -1;
	} else if (orientation.GetValue() == Z) {
		roty = 1;
		angle = 0;
	}

	double length_dbl = length.ForceEval();
	double wireRadius_dbl = wireRadius.ForceEval();

	positionBottom.EvalExpressions();
	DrawCylinder(length_dbl, wireRadius_dbl, positionBottom.GetX(), positionBottom.GetY(), positionBottom.GetZ(), angle, rotx, roty, rotz, showSolid.IsValue());
	DrawSphere(wireRadius_dbl*1.5, positionBottom.GetX(), positionBottom.GetY(), positionBottom.GetZ(), 0, rotx, roty, rotz, showSolid.IsValue());
}

void Monopole::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + positionBottom.GetXExpression() + ") + " + px;
	wxString y = "(" + positionBottom.GetYExpression() + ") + " + py;
	wxString z = "(" + positionBottom.GetZExpression() + ") + " + pz;
	positionBottom.SetXExpression(x);
	positionBottom.SetYExpression(y);
	positionBottom.SetZExpression(z);
}
