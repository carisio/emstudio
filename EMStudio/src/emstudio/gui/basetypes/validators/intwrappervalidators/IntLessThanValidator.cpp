/*
 * IntLessThanValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#include "IntLessThanValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/IntWrapper.h"

IntLessThanValidator::IntLessThanValidator(int val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {
}

IntLessThanValidator::~IntLessThanValidator() {
}

wxString IntLessThanValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be less than ").Append(Converter::IntToFormattedString(val)).Append(".");
}
bool IntLessThanValidator::DoIsValid(BaseType* b) {
	return (static_cast<IntWrapper*>(b))->GetValue() < val;
}
