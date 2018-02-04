/*
 * InvalidPoint3DMEValidator.h
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#ifndef INVALIDPOINT3DMEVALIDATOR_H_
#define INVALIDPOINT3DMEVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "emstudio/gui/basetypes/Point3DME.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

class InvalidPoint3DMEValidator : public BaseTypeValidator {
public:
	InvalidPoint3DMEValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidPoint3DMEValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

bool CheckBoundaries(Point3DME& lowerBoundary, Point3DME& upperBoudary, wxString& errorMessage, wxString lowerBoundaryName, wxString upperBoundaryName);

#endif /* INVALIDPOINT3DMEVALIDATOR_H_ */
