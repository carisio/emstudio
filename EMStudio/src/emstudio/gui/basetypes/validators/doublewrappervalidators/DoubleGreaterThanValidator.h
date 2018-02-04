/*
 * DoubleGreaterThanValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#ifndef DOUBLEGREATERTHANVALIDATOR_H_
#define DOUBLEGREATERTHANVALIDATOR_H_

#include "../BaseTypeValidator.h"

class DoubleGreaterThanValidator : public BaseTypeValidator {
private:
	double val;

public:
	DoubleGreaterThanValidator(double val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~DoubleGreaterThanValidator();
};

#endif /* DOUBLEGREATERTHANVALIDATOR_H_ */
