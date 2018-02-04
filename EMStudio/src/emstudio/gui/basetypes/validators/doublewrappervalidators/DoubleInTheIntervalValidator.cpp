/*
 * DoubleInTheIntervalValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#include "DoubleInTheIntervalValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/DoubleWrapper.h"

DoubleInTheIntervalValidator::DoubleInTheIntervalValidator(double initial, double final, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), i(initial), f(final) {

}

DoubleInTheIntervalValidator::~DoubleInTheIntervalValidator() {
}

wxString DoubleInTheIntervalValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be in [").Append(Converter::DoubleToFormattedString(i, 2)).Append(" , ").Append(Converter::DoubleToFormattedString(f, 2)).Append("].");
}
bool DoubleInTheIntervalValidator::DoIsValid(BaseType* b) {
	double temp = (static_cast<DoubleWrapper*>(b))->GetValue();
	return temp >= i && temp <= f;
}
