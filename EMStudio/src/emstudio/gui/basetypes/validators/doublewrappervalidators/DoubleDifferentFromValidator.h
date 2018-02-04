/*
 * DoubleDifferentFromValidator.h
 *
 *  Created on: 21/06/2013
 *      Author: leandrocarisio
 */

#ifndef DOUBLEDIFFERENTFROMVALIDATOR_H_
#define DOUBLEDIFFERENTFROMVALIDATOR_H_

#include "../BaseTypeValidator.h"

class DoubleDifferentFromValidator : public BaseTypeValidator {
private:
	double val;
public:
	DoubleDifferentFromValidator(double val, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~DoubleDifferentFromValidator();
};

#endif /* DOUBLEDIFFERENTFROMVALIDATOR_H_ */
