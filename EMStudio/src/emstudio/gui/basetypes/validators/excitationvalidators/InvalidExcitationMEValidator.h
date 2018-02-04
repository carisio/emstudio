/*
 * InvalidExcitationMEValidator.h
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#ifndef INVALIDEXCITATIONMEVALIDATOR_H_
#define INVALIDEXCITATIONMEVALIDATOR_H_

#include "wx/wx.h"
#include "emstudio/gui/basetypes/ExcitationME.h"
#include "../BaseTypeValidator.h"

class InvalidExcitationMEValidator : public BaseTypeValidator {
public:
	InvalidExcitationMEValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidExcitationMEValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

#endif /* INVALIDEXCITATIONMEVALIDATOR_H_ */
