/*
 * DoubleInTheIntervalValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: Leandro
 */

#ifndef DOUBLEINTHEINTERVALVALIDATOR_H_
#define DOUBLEINTHEINTERVALVALIDATOR_H_

#include "../BaseTypeValidator.h"

class DoubleInTheIntervalValidator : public BaseTypeValidator {
private:
	double i;
	double f;
public:
	DoubleInTheIntervalValidator(double initial, double final, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);

	virtual ~DoubleInTheIntervalValidator();
};

#endif /* DOUBLEINTHEINTERVALVALIDATOR_H_ */
