/*
 * IntLessThanOrEqualValidator.cpp
 *
 *  Created on: 25/06/2012
 *      Author: Leandro
 */

#include "IntLessThanOrEqualValidator.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/basetypes/IntWrapper.h"

IntLessThanOrEqualValidator::IntLessThanOrEqualValidator(int val, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), val(val) {

}

IntLessThanOrEqualValidator::~IntLessThanOrEqualValidator() {
}

wxString IntLessThanOrEqualValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be equal or less than ").Append(Converter::IntToFormattedString(val)).Append(".");
}

bool IntLessThanOrEqualValidator::DoIsValid(BaseType* b) {
	return (static_cast<IntWrapper*>(b))->GetValue() <= val;
}
