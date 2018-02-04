/*
 * IntLessThanValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#ifndef INTLESSTHANVALIDATOR_H_
#define INTLESSTHANVALIDATOR_H_

#include "../BaseTypeValidator.h"

class IntLessThanValidator : public BaseTypeValidator {
private:
	int val;
public:
	IntLessThanValidator(int val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~IntLessThanValidator();
};

#endif /* INTLESSTHANVALIDATOR_H_ */
