/*
 * MathExpressionGreaterThanOrEqualValidator.h
 *
 *  Created on: 01/10/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONGREATERTHANOREQUALVALIDATOR_H_
#define MATHEXPRESSIONGREATERTHANOREQUALVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "MathExpressionValidator.h"
#include "wx/wx.h"

class MathExpressionGreaterThanOrEqualValidator : public MathExpressionValidator {
private:
	double val;

public:
	MathExpressionGreaterThanOrEqualValidator(double val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~MathExpressionGreaterThanOrEqualValidator();

	virtual wxString DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName);
	virtual bool DoIsResultOfExpressionValid(BaseType* b);
};

#endif /* MATHEXPRESSIONGREATERTHANOREQUALVALIDATOR_H_ */
