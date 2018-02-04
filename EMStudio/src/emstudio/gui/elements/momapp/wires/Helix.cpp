/*
 * Helix.cpp
 *
 *  Created on: 28/05/2014
 *      Author: leandrocarisio
 */

#include "Helix.h"
#include "emstudio/util/nec/UtilSegments.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

Helix::Helix() : ElementsWithSegments(ElementTypeSmartPointer(new Object3DType())) {
	wireRadius.SetExpression("1");
	helixRadiusTop.SetExpression("5");
	helixRadiusBottom.SetExpression("10");
	spaceBetweenTurns.SetExpression("2");
	length.SetExpression("10");
	numberOfSegments.SetExpression("500");

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));

	AddProperty(Property("Bottom radius", &helixRadiusBottom, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Top radius", &helixRadiusTop, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Length", &length, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Turn separation", &spaceBetweenTurns, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Wire radius", &wireRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Segments", &numberOfSegments, validadorMathExpressionMaiorQueZero));
	AddSolidProperty();
	AddVisibleProperty();
}

Helix::~Helix() {

}


ElementGUISmartPointer Helix::NewElementGUI() {
	return ElementGUISmartPointer(new Helix());
}

wxString Helix::GetRegisteredName() {
	return "Helix";
}

wxIcon Helix::GetIcon() {
	return UtilResource::GetIcon("helix");
}

ElementDTOSmartPointer Helix::NewElementDTO() {
	CircularTubeDTO* result = new CircularTubeDTO;

	return ElementDTOSmartPointer(result);
}
bool Helix::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;

	return valid;
}

void Helix::DoMove(Point3DME p) {
}

Segments Helix::BuildSegments() {
	return UtilSegments::GetHelixSegments(numberOfSegments.ForceEval(), helixRadiusBottom.ForceEval(), helixRadiusTop.ForceEval(), length.ForceEval(), spaceBetweenTurns.ForceEval(), wireRadius.ForceEval());
}


} /* namespace mom */
