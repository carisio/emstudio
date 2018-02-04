/*
 * IntGreaterThanOrEqualValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#include "IntGreaterThanOrEqualValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/IntWrapper.h"

IntGreaterThanOrEqualValidator::IntGreaterThanOrEqualValidator(int val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {
}

IntGreaterThanOrEqualValidator::~IntGreaterThanOrEqualValidator() {
}

wxString IntGreaterThanOrEqualValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be equal or greater than ").Append(Converter::IntToFormattedString(val)).Append(".");
}
bool IntGreaterThanOrEqualValidator::DoIsValid(BaseType* b) {
	return (static_cast<IntWrapper*>(b))->GetValue() >= val;
}
