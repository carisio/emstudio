/*
 * MathExpressionDifferentFromValidator.h
 *
 *  Created on: 01/10/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONDIFFERENTFROMVALIDATOR_H_
#define MATHEXPRESSIONDIFFERENTFROMVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "MathExpressionValidator.h"
#include "wx/wx.h"

class MathExpressionDifferentFromValidator : public MathExpressionValidator {
private:
	double val;
public:
	MathExpressionDifferentFromValidator(double val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~MathExpressionDifferentFromValidator();

	virtual wxString DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName);
	virtual bool DoIsResultOfExpressionValid(BaseType* b);
};

#endif /* MATHEXPRESSIONDIFFERENTFROMVALIDATOR_H_ */
