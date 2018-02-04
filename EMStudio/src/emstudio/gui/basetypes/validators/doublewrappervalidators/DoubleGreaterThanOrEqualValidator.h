/*
 * DoubleGreaterThanOrEqualValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#ifndef DOUBLEGREATERTHANOREQUALVALIDATOR_H_
#define DOUBLEGREATERTHANOREQUALVALIDATOR_H_

#include "../BaseTypeValidator.h"

class DoubleGreaterThanOrEqualValidator : public BaseTypeValidator{
private:
	double val;
public:
	DoubleGreaterThanOrEqualValidator(double val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~DoubleGreaterThanOrEqualValidator();
};

#endif /* DOUBLEGREATERTHANOREQUALVALIDATOR_H_ */
