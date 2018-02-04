/*
 * MathExpressionInTheIntervalValidator.h
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONINTHEINTERVALVALIDATOR_H_
#define MATHEXPRESSIONINTHEINTERVALVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "MathExpressionValidator.h"
#include "wx/wx.h"

class MathExpressionInTheIntervalValidator : public MathExpressionValidator {
private:
	double min, max;

public:
	MathExpressionInTheIntervalValidator(double min, double max, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~MathExpressionInTheIntervalValidator();

	virtual wxString DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName);
	virtual bool DoIsResultOfExpressionValid(BaseType* b);
};

#endif /* MATHEXPRESSIONINTHEINTERVALVALIDATOR_H_ */
