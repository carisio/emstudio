/*
 * TransmissionLine.cpp
 *
 *  Created on: 05/06/2014
 *      Author: leandrocarisio
 */

#include "TransmissionLine.h"
#include "emstudio/dto/momapp/TransmissionLineDTO.h"
#include "emstudio/util/nec/UtilSegments.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

TransmissionLine::TransmissionLine() : ElementsWithSegments(ElementTypeSmartPointer(new ConnectionType())) {
	draw = false;
	port1.SetXExpression("0"), port1.SetYExpression("0"), port1.SetZExpression("0");
	port2.SetXExpression("1"), port2.SetYExpression("1"), port2.SetZExpression("1");
	impedance.SetExpression("50");
	length.SetExpression("10");
	admittanceRealPort1.SetExpression("0"); admittanceImagPort1.SetExpression("0");
	admittanceRealPort2.SetExpression("0"); admittanceImagPort2.SetExpression("0");
	crossedLine.SetValue(false);
	colour.SetValue(wxColour(0,0,255));

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualQueZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddProperty(Property("Port 1", &port1, validadorInvalidPoint3D));
	AddProperty(Property("Port 2", &port2, validadorInvalidPoint3D));
	AddProperty(Property("Impedance", &impedance, validadorMathExpressionMaiorOuIgualQueZero));
	AddProperty(Property("Length", &length, validadorMathExpressionMaiorOuIgualQueZero));
	AddProperty(Property("Crossed line?", &crossedLine));
	AddProperty(Property("Admittance at port 1 (real)", &admittanceRealPort1));
	AddProperty(Property("Admittance at port 1 (imaginary)", &admittanceImagPort1));
	AddProperty(Property("Admittance at port 2 (real)", &admittanceRealPort2));
	AddProperty(Property("Admittance at port 2 (imaginary)", &admittanceImagPort2));
	AddProperty(Property("Color", &colour));
	AddVisibleProperty();
}

TransmissionLine::~TransmissionLine() {

}


ElementGUISmartPointer TransmissionLine::NewElementGUI() {
	return ElementGUISmartPointer(new TransmissionLine());
}

wxString TransmissionLine::GetRegisteredName() {
	return "Transmission Line";
}

wxIcon TransmissionLine::GetIcon() {
	return UtilResource::GetIcon("dipole");
}

ElementDTOSmartPointer TransmissionLine::NewElementDTO() {
	int crossed = crossedLine.IsValue() ? -1 : 1;

	TransmissionLineDTO* result = new TransmissionLineDTO;
	port1.EvalExpressions();
	port2.EvalExpressions();
	result->SetPort1(Rvector3(port1.GetX(), port1.GetY(), port1.GetZ()));
	result->SetPort2(Rvector3(port2.GetX(), port2.GetY(), port2.GetZ()));
	result->SetImpedance(impedance.ForceEval() * crossed);
	result->SetLength(length.ForceEval());
	result->SetAdmittanceRealPort1(admittanceRealPort1.ForceEval());
	result->SetAdmittanceImagPort1(admittanceImagPort1.ForceEval());
	result->SetAdmittanceRealPort2(admittanceRealPort2.ForceEval());
	result->SetAdmittanceImagPort2(admittanceImagPort2.ForceEval());

	return ElementDTOSmartPointer(result);
}
bool TransmissionLine::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	port1.EvalExpressions();
	port2.EvalExpressions();

	double distanceBetweenPorts = sqrt(pow(port1.GetX()-port2.GetX(), 2) + pow(port1.GetY()-port2.GetY(), 2) + pow(port1.GetZ()-port2.GetZ(), 2));

	if (length.ForceEval() < distanceBetweenPorts && length.ForceEval() != 0) {
		errorMessage.Append("Transmission line length should be greater than or equal the distance between ports.\n");
		valid = false;
	}
	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

void TransmissionLine::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString xl = "(" + port1.GetXExpression() + ") + " + px;
	wxString yl = "(" + port1.GetYExpression() + ") + " + py;
	wxString zl = "(" + port1.GetZExpression() + ") + " + pz;
	wxString xu = "(" + port2.GetXExpression() + ") + " + px;
	wxString yu = "(" + port2.GetYExpression() + ") + " + py;
	wxString zu = "(" + port2.GetZExpression() + ") + " + pz;
	port1.SetXExpression(xl);
	port1.SetYExpression(yl);
	port1.SetZExpression(zl);
	port2.SetXExpression(xu);
	port2.SetYExpression(yu);
	port2.SetZExpression(zu);
}
void TransmissionLine::Draw(OpenGLStateMachine* opengl) {
	if (!IsVisible() || !draw)
	  return;

//	DisableLight();
	SetColor(colour.GetValue());
	port1.EvalExpressions();
	port2.EvalExpressions();
	impedance.ForceEval();

	if (crossedLine.IsValue()) {
		DrawLine(s1.GetP1().X, s1.GetP1().Y, s1.GetP1().Z, s2.GetP2().X, s2.GetP2().Y, s2.GetP2().Z, 2);
		DrawLine(s1.GetP2().X, s1.GetP2().Y, s1.GetP2().Z, s2.GetP1().X, s2.GetP1().Y, s2.GetP1().Z, 2);
	} else {
		DrawLine(s1.GetP1().X, s1.GetP1().Y, s1.GetP1().Z, s2.GetP1().X, s2.GetP1().Y, s2.GetP1().Z, 2);
		DrawLine(s1.GetP2().X, s1.GetP2().Y, s1.GetP2().Z, s2.GetP2().X, s2.GetP2().Y, s2.GetP2().Z, 2);
	}
//	EnableLight();
}
void TransmissionLine::ProjectChanged() {
	// Encontra os segmentos mais próximos de port1 e port2
	port1.EvalExpressions();
	port2.EvalExpressions();
	double d1, d2;
	draw = FindClosestSegmentInAllElements(port1.GetX(), port1.GetY(), port1.GetZ(), s1, d1);
	draw = FindClosestSegmentInAllElements(port2.GetX(), port2.GetY(), port2.GetZ(), s2, d2);
	cout << "s1.p1 = " << s1.GetP1().X << "\t" << s1.GetP1().Y << "\t" << s1.GetP1().Z << endl;
	cout << "s1.p2 = " << s1.GetP2().X << "\t" << s1.GetP2().Y << "\t" << s1.GetP2().Z << endl;
	cout << "s2.p1 = " << s2.GetP1().X << "\t" << s2.GetP1().Y << "\t" << s2.GetP1().Z << endl;
	cout << "s2.p2 = " << s2.GetP2().X << "\t" << s2.GetP2().Y << "\t" << s2.GetP2().Z << endl;
}
bool TransmissionLine::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!IsVisible())
		return false;

	port1.EvalExpressions();
	port2.EvalExpressions();
	if (port1.GetX() < port2.GetX()) {
		xmin = port1.GetX();
		xmax = port2.GetX();
	} else {
		xmin = port2.GetX();
		xmax = port1.GetX();
	}
	if (port1.GetY() < port2.GetY()) {
		ymin = port1.GetY();
		ymax = port2.GetY();
	} else {
		ymin = port2.GetY();
		ymax = port1.GetY();
	}
	if (port1.GetZ() < port2.GetZ()) {
		zmin = port1.GetZ();
		zmax = port2.GetZ();
	} else {
		zmin = port2.GetZ();
		zmax = port1.GetZ();
	}

	return true;
}

}
