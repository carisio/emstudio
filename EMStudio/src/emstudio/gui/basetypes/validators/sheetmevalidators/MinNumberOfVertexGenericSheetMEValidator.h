/*
 * MinNumberOfVertexGenericSheetMEValidator.h
 *
 *  Created on: 19/11/2013
 *      Author: leandrocarisio
 */

#ifndef MINNUMBEROFVERTEXGENERICSHEETMEVALIDATOR_H_
#define MINNUMBEROFVERTEXGENERICSHEETMEVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "emstudio/gui/basetypes/GenericSheetME.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

class MinNumberOfVertexGenericSheetMEValidator : public BaseTypeValidator {
private:
	int minSize;
public:
	MinNumberOfVertexGenericSheetMEValidator(int minSize = 3, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~MinNumberOfVertexGenericSheetMEValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

#endif /* MINNUMBEROFVERTEXGENERICSHEETMEVALIDATOR_H_ */
