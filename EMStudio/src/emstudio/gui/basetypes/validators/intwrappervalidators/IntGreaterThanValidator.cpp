/*
 * IntGreaterThanValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#include "IntGreaterThanValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/IntWrapper.h"

IntGreaterThanValidator::IntGreaterThanValidator(int val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {
}

IntGreaterThanValidator::~IntGreaterThanValidator() {
}

wxString IntGreaterThanValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be greater than ").Append(Converter::IntToFormattedString(val)).Append(".");
}
bool IntGreaterThanValidator::DoIsValid(BaseType* b) {
	return (static_cast<IntWrapper*>(b))->GetValue() > val;
}
