/*
 * Wire.cpp
 *
 *  Created on: 27/05/2014
 *      Author: leandrocarisio
 */

#include "Wire.h"
#include "emstudio/util/nec/UtilSegments.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

Wire::Wire() : ElementsWithSegments(ElementTypeSmartPointer(new WireType())) {

	bottomCenter.SetXExpression("25"); bottomCenter.SetYExpression("25"); bottomCenter.SetZExpression("5");
	topCenter.SetXExpression("25"); topCenter.SetYExpression("25"); topCenter.SetZExpression("45");
	wireRadius.SetExpression("1");
	numberOfSegments.SetExpression("40");

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddProperty(Property("Bottom (center)", &bottomCenter, validadorInvalidPoint3D));
	AddProperty(Property("Top (center)", &topCenter, validadorInvalidPoint3D));
	AddProperty(Property("Wire radius", &wireRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Segments", &numberOfSegments, validadorMathExpressionMaiorQueZero));
	AddSolidProperty();
	AddVisibleProperty();
}

Wire::~Wire() {

}


ElementGUISmartPointer Wire::NewElementGUI() {
	return ElementGUISmartPointer(new Wire());
}

wxString Wire::GetRegisteredName() {
	return "Wire";
}

wxIcon Wire::GetIcon() {
	return UtilResource::GetIcon("thinwire");
}

ElementDTOSmartPointer Wire::NewElementDTO() {
	WireDTO* result = new WireDTO;
	bottomCenter.EvalExpressions();
	topCenter.EvalExpressions();
	result->SetP1(Rvector3(bottomCenter.GetX(), bottomCenter.GetY(), bottomCenter.GetZ()));
	result->SetP2(Rvector3(topCenter.GetX(), topCenter.GetY(), topCenter.GetZ()));
	result->SetRadius(wireRadius.ForceEval());
	result->SetNumberOfSegments(numberOfSegments.ForceEval());

	return ElementDTOSmartPointer(result);
}
bool Wire::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	topCenter.EvalExpressions();
	bottomCenter.EvalExpressions();

	if (bottomCenter.GetX() == topCenter.GetX() && bottomCenter.GetY() == topCenter.GetY() && bottomCenter.GetZ() == topCenter.GetZ()) {
		errorMessage.Append("Bottom center and top center should be different.\n");
		valid = false;
	}
	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

void Wire::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString xl = "(" + bottomCenter.GetXExpression() + ") + " + px;
	wxString yl = "(" + bottomCenter.GetYExpression() + ") + " + py;
	wxString zl = "(" + bottomCenter.GetZExpression() + ") + " + pz;
	wxString xu = "(" + topCenter.GetXExpression() + ") + " + px;
	wxString yu = "(" + topCenter.GetYExpression() + ") + " + py;
	wxString zu = "(" + topCenter.GetZExpression() + ") + " + pz;
	bottomCenter.SetXExpression(xl);
	bottomCenter.SetYExpression(yl);
	bottomCenter.SetZExpression(zl);
	topCenter.SetXExpression(xu);
	topCenter.SetYExpression(yu);
	topCenter.SetZExpression(zu);
}
Segments Wire::BuildSegments() {
	bottomCenter.EvalExpressions();
	topCenter.EvalExpressions();
	return UtilSegments::GetWireSegments(numberOfSegments.ForceEval(),
			bottomCenter.GetX(), bottomCenter.GetY(), bottomCenter.GetZ(),
			topCenter.GetX(), topCenter.GetY(), topCenter.GetZ(),
			wireRadius.ForceEval());

}

}
