/*
 * DoubleGreaterThanOrEqualValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#include "DoubleGreaterThanOrEqualValidator.h"

#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/DoubleWrapper.h"

DoubleGreaterThanOrEqualValidator::DoubleGreaterThanOrEqualValidator(double val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {
}

DoubleGreaterThanOrEqualValidator::~DoubleGreaterThanOrEqualValidator() {
}


wxString DoubleGreaterThanOrEqualValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be equal or greater than ").Append(Converter::DoubleToFormattedString(val, 2)).Append(".");
}
bool DoubleGreaterThanOrEqualValidator::DoIsValid(BaseType* b) {
	return (static_cast<DoubleWrapper*>(b))->GetValue() >= val;
}
