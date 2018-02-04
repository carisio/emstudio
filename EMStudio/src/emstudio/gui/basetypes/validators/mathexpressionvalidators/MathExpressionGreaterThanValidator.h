/*
 * MathExpressionGreaterThanValidator.h
 *
 *  Created on: 23/09/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONGREATERTHANVALIDATOR_H_
#define MATHEXPRESSIONGREATERTHANVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "MathExpressionValidator.h"
#include "wx/wx.h"


class MathExpressionGreaterThanValidator : public MathExpressionValidator {
private:
	double val;

public:
	MathExpressionGreaterThanValidator(double val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~MathExpressionGreaterThanValidator();

	virtual wxString DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName);
	virtual bool DoIsResultOfExpressionValid(BaseType* b);
};

#endif /* MATHEXPRESSIONGREATERTHANVALIDATOR_H_ */
