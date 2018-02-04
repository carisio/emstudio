/*
 * InvalidGenericSheetValidator.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef INVALIDGENERICSHEETVALIDATOR_H_
#define INVALIDGENERICSHEETVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "emstudio/gui/basetypes/GenericSheetME.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

class InvalidGenericSheetMEValidator : public BaseTypeValidator {
public:
	InvalidGenericSheetMEValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidGenericSheetMEValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

#endif /* INVALIDGENERICSHEETVALIDATOR_H_ */
