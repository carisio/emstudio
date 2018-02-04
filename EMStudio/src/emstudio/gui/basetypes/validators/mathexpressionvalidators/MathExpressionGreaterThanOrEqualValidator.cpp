/*
 * MathExpressionGreaterThanOrEqualValidator.cpp
 *
 *  Created on: 01/10/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionGreaterThanOrEqualValidator.h"

MathExpressionGreaterThanOrEqualValidator::MathExpressionGreaterThanOrEqualValidator(double val, BaseTypeValidatorSmartPointer parent)
		: MathExpressionValidator(parent), val(val){

}

MathExpressionGreaterThanOrEqualValidator::~MathExpressionGreaterThanOrEqualValidator() {
}

wxString MathExpressionGreaterThanOrEqualValidator::DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be equal or greater than ").Append(Converter::DoubleToFormattedString(val, 2)).Append(".");
}

bool MathExpressionGreaterThanOrEqualValidator::DoIsResultOfExpressionValid(BaseType* b) {
	MathExpressionParser* mep = static_cast<MathExpressionParser*>(b);

	return mep->Eval() >= val;
}
