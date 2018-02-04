/*
 * VoltageSource.cpp
 *
 *  Created on: 02/06/2014
 *      Author: leandrocarisio
 */

#include "VoltageSource.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/dto/momapp/VoltageSourceDTO.h"

namespace mom {

VoltageSource::VoltageSource() : ElementsWithSegments(ElementTypeSmartPointer(new SourceType())) {
	draw = false;
	position.SetXExpression("10"); position.SetYExpression("10"); position.SetZExpression("10");
	realPart.SetExpression("1"); imagPart.SetExpression("0");
	colour.SetValue(wxColour(255,0,0));

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddProperty(Property("Position", &position, validadorInvalidPoint3D));
	AddProperty(Property("Voltage (real)", &realPart, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Voltage (imaginary)", &imagPart));
	AddProperty(Property("Color", &colour));
	AddVisibleProperty();
}

VoltageSource::~VoltageSource() {
}
void VoltageSource::ProjectChanged() {
	position.EvalExpressions();
	double d;
	draw = FindClosestSegmentInAllElements(position.GetX(), position.GetY(), position.GetZ(), s, d);
}

ElementGUISmartPointer VoltageSource::NewElementGUI() {
	return ElementGUISmartPointer(new VoltageSource());
}

wxString VoltageSource::GetRegisteredName() {
	return "Voltage Source";
}

wxIcon VoltageSource::GetIcon() {
	return UtilResource::GetIcon("deltagap");
}

ElementDTOSmartPointer VoltageSource::NewElementDTO() {
	VoltageSourceDTO* result = new VoltageSourceDTO;
	position.EvalExpressions();

	result->SetRealPart(realPart.ForceEval());
	result->SetImagPart(imagPart.ForceEval());
	result->SetX(position.GetX());
	result->SetY(position.GetY());
	result->SetZ(position.GetZ());

	return ElementDTOSmartPointer(result);
}
bool VoltageSource::IsAllPropertiesTogetherValid() {
	return true;
}

void VoltageSource::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + position.GetXExpression() + ") + " + px;
	wxString y = "(" + position.GetYExpression() + ") + " + py;
	wxString z = "(" + position.GetZExpression() + ") + " + pz;
	position.SetXExpression(x);
	position.SetYExpression(y);
	position.SetZExpression(z);
}
void VoltageSource::Draw(OpenGLStateMachine* opengl) {
	if (!IsVisible() || !draw)
	  return;

//	DisableLight();
	SetColor(colour.GetValue());
	position.EvalExpressions();
	DrawPoint(s.GetP1().X + (s.GetP2().X - s.GetP1().X)/2, s.GetP1().Y + (s.GetP2().Y - s.GetP1().Y)/2, s.GetP1().Z + (s.GetP2().Z - s.GetP1().Z)/2, 10);
//	SetColor(wxColour(255,255,255));
//	DrawPoint(position.GetX(), position.GetY(), position.GetZ(), 10);
//	EnableLight();
}
bool VoltageSource::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!IsVisible())
		return false;

	position.EvalExpressions();
	xmin = xmax = position.GetX();
	ymin = ymax = position.GetY();
	zmin = zmax = position.GetZ();


	return true;
}


} /* namespace mom */
