/*
 * InvalidMicrostripXYPortsValidator.h
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#ifndef INVALIDMICROSTRIPXYPORTSVALIDATOR_H_
#define INVALIDMICROSTRIPXYPORTSVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "emstudio/gui/basetypes/MicrostripXYPortsME.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

class InvalidMicrostripXYPortsValidator : public BaseTypeValidator {
public:
	InvalidMicrostripXYPortsValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidMicrostripXYPortsValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};
#endif /* INVALIDMICROSTRIPXYPORTSVALIDATOR_H_ */
