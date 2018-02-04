/*
 * DoubleLessThanValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#include "DoubleLessThanValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/DoubleWrapper.h"

DoubleLessThanValidator::DoubleLessThanValidator(double val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {
}

DoubleLessThanValidator::~DoubleLessThanValidator() {
}

wxString DoubleLessThanValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be less than ").Append(Converter::DoubleToFormattedString(val, 2)).Append(".");
}
bool DoubleLessThanValidator::DoIsValid(BaseType* b) {
	return (static_cast<DoubleWrapper*>(b))->GetValue() < val;
}
