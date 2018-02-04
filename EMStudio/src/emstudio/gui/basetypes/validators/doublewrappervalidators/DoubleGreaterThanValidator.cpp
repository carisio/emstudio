/*
 * DoubleGreaterThanValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#include "DoubleGreaterThanValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/DoubleWrapper.h"

DoubleGreaterThanValidator::DoubleGreaterThanValidator(double val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {
}

DoubleGreaterThanValidator::~DoubleGreaterThanValidator() {
}

wxString DoubleGreaterThanValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be greater than ").Append(Converter::DoubleToFormattedString(val, 2)).Append(".");
}
bool DoubleGreaterThanValidator::DoIsValid(BaseType* b) {
	return (static_cast<DoubleWrapper*>(b))->GetValue() > val;
}
