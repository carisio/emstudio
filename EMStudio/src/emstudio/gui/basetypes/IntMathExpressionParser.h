/*
 * IntMathExpression.h
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#ifndef INTMATHEXPRESSION_H_
#define INTMATHEXPRESSION_H_

#include "MathExpressionParser.h"

class IntMathExpressionParser : public MathExpressionParser {
public:
	IntMathExpressionParser();
	virtual ~IntMathExpressionParser();

	virtual double Eval();

	virtual wxString GetBaseTypeClassName();
	virtual wxString GetUserFriendlyStringRepresentation();
};

#endif /* INTMATHEXPRESSION_H_ */
