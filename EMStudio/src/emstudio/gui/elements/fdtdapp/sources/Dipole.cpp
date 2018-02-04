/*
 * Dipole.cpp
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#include "Dipole.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

Dipole::Dipole()
	: ElementsWithFacets(ElementTypeSmartPointer(new SourceType())) ,
	  excitation (), length(), orientation(),
	  linePoints(), sourcePoints(), wireRadius(), lineImpedance(),
	  initialFrequency(), frequencyStep(), nFrequency(), showSolid(), visible() {


//	colour.SetValue(wxColour(255,0,0));

	length.SetExpression("30");

	positionCenter.SetXExpression("25");
	positionCenter.SetYExpression("25");
	positionCenter.SetZExpression("25");


	linePoints.SetValue(100); sourcePoints.SetValue(90);
	wireRadius.SetExpression("1");
	lineImpedance.SetExpression("50");
//	velocityFactor.SetValue(0.7);
	orientation.SetValue(Z);
	initialFrequency.SetExpression("25");
	frequencyStep.SetExpression("5");
	nFrequency.SetExpression("10");
	showSolid.SetValue(true);
	visible.SetValue(true);

	SetPriority(HIGH);

	BaseTypeValidatorSmartPointer validadorInteiroMaiorQueZero(new IntGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorOuIgualAZero(new DoubleGreaterThanOrEqualValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorQueZero(new DoubleGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidExcitation(new InvalidExcitationMEValidator);

	AddProperty(Property("Orientation", &orientation));
	AddProperty(Property("Position (center)", &positionCenter, validadorInvalidPoint3D));
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

Dipole::~Dipole() {

}


ElementGUISmartPointer Dipole::NewElementGUI() {
	return ElementGUISmartPointer(new Dipole());
}

wxString Dipole::GetRegisteredName() {
	return "Dipole";
}

wxIcon Dipole::GetIcon() {
	return UtilResource::GetIcon("dipole");
}

ElementDTOSmartPointer Dipole::NewElementDTO() {
	DipoleDTO* result = new DipoleDTO;

    result->SetOrientation(orientation);
    result->SetExcitation(excitation.ConvertToExcitation());
    result->SetFrequencyStep(frequencyStep.ForceEval());
    result->SetNFrequency(nFrequency.ForceEval());
    result->SetInitialFrequency(initialFrequency.ForceEval());
    result->SetLength(length.ForceEval());
    result->SetLineImpedance(lineImpedance.ForceEval());
    result->SetLinePoints(linePoints.GetValue());
    result->SetSourcePoints(sourcePoints.GetValue());
    result->SetWireRadius(wireRadius.ForceEval());
    positionCenter.EvalExpressions();
    result->SetX(positionCenter.GetX());
    result->SetY(positionCenter.GetY());
    result->SetZ(positionCenter.GetZ());

	return ElementDTOSmartPointer(result);
}

bool Dipole::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	double length_dbl = length.ForceEval();
	double wireRadius_dbl = wireRadius.ForceEval();

	positionCenter.EvalExpressions();
	xmin = xmax = positionCenter.GetX();
	ymin = ymax = positionCenter.GetY();
	zmin = zmax = positionCenter.GetZ();

	if (orientation.GetValue() == X) {
		xmin -= length_dbl/2;
		xmax += length_dbl/2;
		ymin -= wireRadius_dbl*1.5;
		ymax += wireRadius_dbl*1.5;
		zmin -= wireRadius_dbl*1.5;
		zmax += wireRadius_dbl*1.5;
	} else if (orientation.GetValue() == Y) {
		ymin -= length_dbl/2;
		ymax += length_dbl/2;
		xmin -= wireRadius_dbl*1.5;
		xmax += wireRadius_dbl*1.5;
		zmin -= wireRadius_dbl*1.5;
		zmax += wireRadius_dbl*1.5;
	} else if (orientation.GetValue() == Z) {
		zmin -= length_dbl/2;
		zmax += length_dbl/2;
		xmin -= wireRadius_dbl*1.5;
		xmax += wireRadius_dbl*1.5;
		ymin -= wireRadius_dbl*1.5;
		ymax += wireRadius_dbl*1.5;
	}

	return true;
}

void Dipole::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

	double length_dbl = length.ForceEval();
	double wireRadius_dbl = wireRadius.ForceEval();

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

	positionCenter.EvalExpressions();
	DrawCylinder(length_dbl/2, wireRadius_dbl, positionCenter.GetX(), positionCenter.GetY(), positionCenter.GetZ(), angle, rotx, roty, rotz, showSolid.IsValue());
	DrawCylinder(length_dbl/2, wireRadius_dbl, positionCenter.GetX(), positionCenter.GetY(), positionCenter.GetZ(), angle + 180, rotx, roty, rotz, showSolid.IsValue());
	DrawSphere(wireRadius_dbl*1.5, positionCenter.GetX(), positionCenter.GetY(), positionCenter.GetZ(), 0, rotx, roty, rotz, showSolid.IsValue());
}

void Dipole::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + positionCenter.GetXExpression() + ") + " + px;
	wxString y = "(" + positionCenter.GetYExpression() + ") + " + py;
	wxString z = "(" + positionCenter.GetZExpression() + ") + " + pz;
	positionCenter.SetXExpression(x);
	positionCenter.SetYExpression(y);
	positionCenter.SetZExpression(z);
}
