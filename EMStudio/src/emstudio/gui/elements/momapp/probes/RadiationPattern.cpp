/*
 * RadiationPattern.cpp
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#include "RadiationPattern.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

RadiationPattern::RadiationPattern() : ElementsWithSegments(ElementTypeSmartPointer(new ProbeType())) {
	initialFrequency.SetExpression("25");
	frequencyStep.SetExpression("0");
	nFrequency.SetExpression("1");

	BaseTypeValidatorSmartPointer validadorNFrequency(new MathExpressionInTheIntervalValidator(1, 30));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));

	AddProperty(Property("Initial frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &frequencyStep, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorNFrequency));
}

RadiationPattern::~RadiationPattern() {
}

ElementGUISmartPointer RadiationPattern::NewElementGUI() {
	return ElementGUISmartPointer(new RadiationPattern());
}

wxString RadiationPattern::GetRegisteredName() {
	return "RadiationPattern";
}

wxIcon RadiationPattern::GetIcon() {
	return UtilResource::GetIcon("radiationpattern");
}

ElementDTOSmartPointer RadiationPattern::NewElementDTO() {
	RadiationPatternDTO* result = new RadiationPatternDTO;

	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(frequencyStep.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());

	return ElementDTOSmartPointer(result);
}

void RadiationPattern::DoMove(Point3DME p) {
}

} /* namespace mom */
