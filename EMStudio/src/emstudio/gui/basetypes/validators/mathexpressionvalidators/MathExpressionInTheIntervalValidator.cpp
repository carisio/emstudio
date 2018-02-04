/*
 * MathExpressionInTheIntervalValidator.cpp
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionInTheIntervalValidator.h"

MathExpressionInTheIntervalValidator::MathExpressionInTheIntervalValidator(double min, double max, BaseTypeValidatorSmartPointer parent)
	: MathExpressionValidator(parent), min(min), max(max) {

}

MathExpressionInTheIntervalValidator::~MathExpressionInTheIntervalValidator() {

}

wxString MathExpressionInTheIntervalValidator::DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should be in [").Append(Converter::DoubleToFormattedString(min)).Append(" , ").Append(Converter::DoubleToFormattedString(max)).Append("].");
}

bool MathExpressionInTheIntervalValidator::DoIsResultOfExpressionValid(BaseType* b) {
	MathExpressionParser* mep = static_cast<MathExpressionParser*>(b);
	double value = mep->Eval();

	return value >= min && value <= max;
}
