/*
 * MathExpressionGreaterThanValidator.cpp
 *
 *  Created on: 23/09/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionGreaterThanValidator.h"

MathExpressionGreaterThanValidator::MathExpressionGreaterThanValidator(double val, BaseTypeValidatorSmartPointer parent)
		: MathExpressionValidator(parent), val(val){

}

MathExpressionGreaterThanValidator::~MathExpressionGreaterThanValidator() {
}

wxString MathExpressionGreaterThanValidator::DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be greater than ").Append(Converter::DoubleToFormattedString(val, 2)).Append(".");
}

bool MathExpressionGreaterThanValidator::DoIsResultOfExpressionValid(BaseType* b) {
	MathExpressionParser* mep = static_cast<MathExpressionParser*>(b);

	return mep->Eval() > val;
}
