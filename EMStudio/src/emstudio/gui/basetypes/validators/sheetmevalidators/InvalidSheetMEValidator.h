/*
 * InvalidSheetMEValidator.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef INVALIDSHEETMEVALIDATOR_H_
#define INVALIDSHEETMEVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "emstudio/gui/basetypes/SheetME.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

class InvalidSheetMEValidator : public BaseTypeValidator {
public:
	InvalidSheetMEValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidSheetMEValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

#endif /* INVALIDSHEETMEVALIDATOR_H_ */
