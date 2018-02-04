/*
 * IntMathExpression.cpp
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#include "IntMathExpressionParser.h"

IntMathExpressionParser::IntMathExpressionParser() {
	// Não é necessário setar a versão, já que isso é feita pela classe mãe.
//	SetWriteVersion(1);
}

IntMathExpressionParser::~IntMathExpressionParser() {
}

wxString IntMathExpressionParser::GetBaseTypeClassName() {
	return "IntMathExpressionParser";
}

double IntMathExpressionParser::Eval() {
	return (int)(MathExpressionParser::Eval());
}

wxString IntMathExpressionParser::GetUserFriendlyStringRepresentation() {
	wxString result;
	if (IsExpressionValid()) {
		result = Converter::IntToFormattedString((int)Eval());
	} else {
		result = "Invalid expression";
	}
	return result;
}
