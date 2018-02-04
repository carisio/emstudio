/*
 * IntMathExpression.cpp
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#include "IntMathExpressionParser.h"

IntMathExpressionParser::IntMathExpressionParser() {
	// N�o � necess�rio setar a vers�o, j� que isso � feita pela classe m�e.
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
