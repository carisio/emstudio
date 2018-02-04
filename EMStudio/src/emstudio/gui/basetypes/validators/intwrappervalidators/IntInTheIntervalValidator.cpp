/*
 * IntInTheIntervalValidator.cpp
 *
 *  Created on: 13/11/2012
 *      Author: leandrocarisio
 */

#include "IntInTheIntervalValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/IntWrapper.h"

IntInTheIntervalValidator::IntInTheIntervalValidator(int initial, int final, BaseTypeValidatorSmartPointer parent)
		: BaseTypeValidator(parent), i(initial), f(final) {

}

IntInTheIntervalValidator::~IntInTheIntervalValidator() {
}

wxString IntInTheIntervalValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be in [").Append(Converter::IntToFormattedString(i)).Append(" , ").Append(Converter::IntToFormattedString(f)).Append("].");
}
bool IntInTheIntervalValidator::DoIsValid(BaseType* b) {
	double temp = (static_cast<IntWrapper*>(b))->GetValue();
	return temp >= i && temp <= f;
}
