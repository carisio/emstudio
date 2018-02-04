/*
 * IntGreaterThanValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#ifndef INTGREATERTHANVALIDATOR_H_
#define INTGREATERTHANVALIDATOR_H_

#include "../BaseTypeValidator.h"

class IntGreaterThanValidator : public BaseTypeValidator {
private:
	int val;

public:
	IntGreaterThanValidator(int val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~IntGreaterThanValidator();
};

#endif /* INTGREATERTHANVALIDATOR_H_ */
