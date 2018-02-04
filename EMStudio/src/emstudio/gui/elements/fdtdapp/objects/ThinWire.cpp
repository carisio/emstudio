/*
 * ThinWire.cpp
 *
 *  Created on: 29/09/2011
 *      Author: Leandro
 */

#include "ThinWire.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"

ThinWire::ThinWire()
	: ElementsWithFacets(ElementTypeSmartPointer(new Object3DType())), /*wireColour(), colour(), */length(), radius(),
	  orientation(), showSolid(), visible() {

	positionBottom.SetXExpression("25"); positionBottom.SetYExpression("25"); positionBottom.SetZExpression("1");
	length.SetExpression("25"); radius.SetExpression("1");
//	wireColour.SetValue(wxColour(255,0,0));
//	colour.SetValue(wxColour(0,0,255));
	showSolid.SetValue(true);
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddProperty(Property("Orientation", &orientation));
	AddProperty(Property("Position (Bottom)", &positionBottom, validadorInvalidPoint3D));
	AddProperty(Property("Length", &length, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Wire radius", &radius, validadorMathExpressionMaiorQueZero));
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));
}

ThinWire::~ThinWire() {

}

ElementGUISmartPointer ThinWire::NewElementGUI() {
	return ElementGUISmartPointer(new ThinWire());
}

wxString ThinWire::GetRegisteredName() {
	return "Thin Wire";
}

wxIcon ThinWire::GetIcon() {
	return UtilResource::GetIcon("thinwire");
}

ElementDTOSmartPointer ThinWire::NewElementDTO() {
	ThinWireDTO* result = new ThinWireDTO;
	result->SetX(positionBottom.GetX());
	result->SetY(positionBottom.GetY());
	result->SetZ(positionBottom.GetZ());
	result->SetLength(length.ForceEval());
	result->SetRadius(radius.ForceEval());
	result->SetOrientation(orientation);

	return ElementDTOSmartPointer(result);
}

bool ThinWire::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	positionBottom.EvalExpressions();
	xmin = xmax = positionBottom.GetX();
	ymin = ymax = positionBottom.GetY();
	zmin = zmax = positionBottom.GetZ();

	double length_dbl = length.ForceEval();
	double radius_dbl = radius.ForceEval();

	bool negativeLength = length_dbl < 0;
	if (orientation.GetValue() == X) {
		if (negativeLength)
			xmin += length_dbl;
		else
			xmax += length_dbl;
		ymin -= radius_dbl;
		ymax += radius_dbl;
		zmin -= radius_dbl;
		zmax += radius_dbl;
	} else if (orientation.GetValue() == Y) {
		if (negativeLength)
			ymin += length_dbl;
		else
			ymax += length_dbl;
		xmin -= radius_dbl;
		xmax += radius_dbl;
		zmin -= radius_dbl;
		zmax += radius_dbl;
	} else if (orientation.GetValue() == Z) {
		if (negativeLength)
			zmin += length_dbl;
		else
			zmax += length_dbl;
		xmin -= radius_dbl;
		xmax += radius_dbl;
		ymin -= radius_dbl;
		ymax += radius_dbl;
	}
	return true;
}

void ThinWire::Draw(OpenGLStateMachine* opengl) {
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
	double radius_dbl = radius.ForceEval();

	positionBottom.EvalExpressions();
	DrawCylinder(length_dbl, radius_dbl, positionBottom.GetX(), positionBottom.GetY(), positionBottom.GetZ(), angle, rotx, roty, rotz, showSolid.IsValue());
}
void ThinWire::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + positionBottom.GetXExpression() + ") + " + px;
	wxString y = "(" + positionBottom.GetYExpression() + ") + " + py;
	wxString z = "(" + positionBottom.GetZExpression() + ") + " + pz;
	positionBottom.SetXExpression(x);
	positionBottom.SetYExpression(y);
	positionBottom.SetZExpression(z);
}
