/*
 * Sphere.cpp
 *
 *  Created on: 15/07/2014
 *      Author: leandrocarisio
 */

#include "WireSphere.h"
#include "emstudio/util/nec/UtilSegments.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

WireSphere::WireSphere() : ElementsWithSegments(ElementTypeSmartPointer(new WireType())) {
	center.SetXExpression("0"); center.SetYExpression("0"); center.SetZExpression("0");
	sphereRadius.SetExpression("10");
	wireRadius.SetExpression("1");
	numberOfSegments.SetExpression("40");

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddProperty(Property("Center", &center, validadorInvalidPoint3D));
	AddProperty(Property("Sphere radius", &sphereRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Wire radius", &wireRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Segments", &numberOfSegments, validadorMathExpressionMaiorQueZero));
	AddSolidProperty();
	AddVisibleProperty();

}

WireSphere::~WireSphere() {
}


ElementGUISmartPointer WireSphere::NewElementGUI() {
	return ElementGUISmartPointer(new WireSphere());
}

wxString WireSphere::GetRegisteredName() {
	return "Wire Sphere";
}

wxIcon WireSphere::GetIcon() {
	return UtilResource::GetIcon("sphere");
}

ElementDTOSmartPointer WireSphere::NewElementDTO() {
	WireDTO* result = new WireDTO;

	return ElementDTOSmartPointer(result);
}
bool WireSphere::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;



	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

void WireSphere::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + center.GetXExpression() + ") + " + px;
	wxString y = "(" + center.GetYExpression() + ") + " + py;
	wxString z = "(" + center.GetZExpression() + ") + " + pz;
	center.SetXExpression(x);
	center.SetYExpression(y);
	center.SetZExpression(z);
}
Segments WireSphere::BuildSegments() {
	center.EvalExpressions();
	sphereRadius.Eval();

	return Segments();
}

} /* namespace mom */
