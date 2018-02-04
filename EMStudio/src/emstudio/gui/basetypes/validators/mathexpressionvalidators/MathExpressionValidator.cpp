/*
 * MathExpressionValidator.cpp
 *
 *  Created on: 01/10/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionValidator.h"

MathExpressionValidator::MathExpressionValidator(BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent) {

}

MathExpressionValidator::~MathExpressionValidator() {
}


wxString MathExpressionValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	if (!isExpressionValid)
		return baseTypeName.Append(" has an invalid expression.");
	else
		return DoGetErrorMessageBasedOnResultOfExpression(b, baseTypeName);
}

bool MathExpressionValidator::DoIsValid(BaseType* b) {
	MathExpressionParser* mep = static_cast<MathExpressionParser*>(b);

	isExpressionValid = mep->IsExpressionValid();
	if (isExpressionValid) {
		return DoIsResultOfExpressionValid(b);
	} else {
		return false;
	}
}

/* Por padrão não avalia o conteúdo da expressão */
wxString MathExpressionValidator::DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName) {
	return "";
}
bool MathExpressionValidator::DoIsResultOfExpressionValid(BaseType* b) {
	return true;
}
