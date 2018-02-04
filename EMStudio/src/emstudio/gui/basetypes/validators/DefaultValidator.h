/*
 * DefaultValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#ifndef DEFAULTVALIDATOR_H_
#define DEFAULTVALIDATOR_H_

#include "BaseTypeValidator.h"

class DefaultValidator : public BaseTypeValidator {
public:
	DefaultValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~DefaultValidator();
};

#endif /* DEFAULTVALIDATOR_H_ */
