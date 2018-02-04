/*
 * IntGreaterThanOrEqualValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#ifndef INTGREATERTHANOREQUALVALIDATOR_H_
#define INTGREATERTHANOREQUALVALIDATOR_H_

#include "../BaseTypeValidator.h"

class IntGreaterThanOrEqualValidator : public BaseTypeValidator {
private:
	int val;
public:
	IntGreaterThanOrEqualValidator(int val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~IntGreaterThanOrEqualValidator();
};

#endif /* INTGREATERTHANOREQUALVALIDATOR_H_ */
