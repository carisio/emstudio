/*
 * DoubleDifferentFromValidator.cpp
 *
 *  Created on: 21/06/2013
 *      Author: leandrocarisio
 */

#include "DoubleDifferentFromValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/DoubleWrapper.h"

DoubleDifferentFromValidator::DoubleDifferentFromValidator(double val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {
}

DoubleDifferentFromValidator::~DoubleDifferentFromValidator() {
}

wxString DoubleDifferentFromValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be different from ").Append(Converter::DoubleToFormattedString(val, 2)).Append(".");
}
bool DoubleDifferentFromValidator::DoIsValid(BaseType* b) {
	return (static_cast<DoubleWrapper*>(b))->GetValue() != val;
}



