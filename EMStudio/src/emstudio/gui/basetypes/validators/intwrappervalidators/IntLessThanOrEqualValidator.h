/*
 * IntLessThanOrEqualValidator.h
 *
 *  Created on: 25/06/2012
 *      Author: Leandro
 */

#ifndef INTLESSTHANOREQUALVALIDATOR_H_
#define INTLESSTHANOREQUALVALIDATOR_H_

#include "../BaseTypeValidator.h"

class IntLessThanOrEqualValidator : public BaseTypeValidator {
private:
	int val;
public:
	IntLessThanOrEqualValidator(int val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~IntLessThanOrEqualValidator();
};

#endif /* INTLESSTHANOREQUALVALIDATOR_H_ */
