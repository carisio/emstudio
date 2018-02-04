/*
 * MathExpressionValidator.h
 *
 *  Created on: 01/10/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONVALIDATOR_H_
#define MATHEXPRESSIONVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

class MathExpressionValidator : public BaseTypeValidator {
private:
	bool isExpressionValid;
public:
	MathExpressionValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~MathExpressionValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual wxString DoGetErrorMessageBasedOnResultOfExpression(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
	virtual bool DoIsResultOfExpressionValid(BaseType* b);
};

#endif /* MATHEXPRESSIONVALIDATOR_H_ */
