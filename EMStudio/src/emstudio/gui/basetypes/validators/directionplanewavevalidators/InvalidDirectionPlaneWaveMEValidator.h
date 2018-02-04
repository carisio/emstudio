/*
 * InvalidDirectionPlaneWaveMEValidator.h
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#ifndef INVALIDDIRECTIONPLANEWAVEMEVALIDATOR_H_
#define INVALIDDIRECTIONPLANEWAVEMEVALIDATOR_H_

#include "wx/wx.h"
#include "emstudio/gui/basetypes/DirectionPlaneWaveME.h"
#include "../BaseTypeValidator.h"

class InvalidDirectionPlaneWaveMEValidator : public BaseTypeValidator {
public:
	InvalidDirectionPlaneWaveMEValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidDirectionPlaneWaveMEValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

#endif /* INVALIDDIRECTIONPLANEWAVEMEVALIDATOR_H_ */
