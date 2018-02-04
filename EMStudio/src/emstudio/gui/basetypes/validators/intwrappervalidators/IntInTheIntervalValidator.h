/*
 * IntInTheIntervalValidator.h
 *
 *  Created on: 13/11/2012
 *      Author: leandrocarisio
 */

#ifndef INTINTHEINTERVALVALIDATOR_H_
#define INTINTHEINTERVALVALIDATOR_H_

#include "../BaseTypeValidator.h"

class IntInTheIntervalValidator : public BaseTypeValidator {
private:
	int i;
	int f;
public:
	IntInTheIntervalValidator(int initial, int final, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~IntInTheIntervalValidator();
};

#endif /* INTINTHEINTERVALVALIDATOR_H_ */
