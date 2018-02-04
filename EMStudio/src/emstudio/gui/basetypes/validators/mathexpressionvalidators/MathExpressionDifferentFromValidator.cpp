/*
 * MathExpressionDifferentFromValidator.cpp
 *
 *  Created on: 01/10/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionDifferentFromValidator.h"

MathExpressionDifferentFromValidator::MathExpressionDifferentFromValidator(double val, BaseTypeValidatorSmartPointer parent)
		: MathExpressionValidator(parent), val(val) {

}

MathExpressionDifferentFromValidator::~MathExpressionDifferentFromValidator() {
}

wxString MathExpressionDifferentFromValidator::DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be different from ").Append(Converter::DoubleToFormattedString(val, 2)).Append(".");
}

bool MathExpressionDifferentFromValidator::DoIsResultOfExpressionValid(BaseType* b) {
	MathExpressionParser* mep = static_cast<MathExpressionParser*>(b);

	return mep->Eval() != val;
}
