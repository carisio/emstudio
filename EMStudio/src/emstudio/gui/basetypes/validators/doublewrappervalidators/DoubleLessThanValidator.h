/*
 * DoubleLessThanValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#ifndef DOUBLELESSTHANVALIDATOR_H_
#define DOUBLELESSTHANVALIDATOR_H_

#include "../BaseTypeValidator.h"

class DoubleLessThanValidator : public BaseTypeValidator {
private:
	double val;
public:
	DoubleLessThanValidator(double val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~DoubleLessThanValidator();
};

#endif /* DOUBLELESSTHANVALIDATOR_H_ */
