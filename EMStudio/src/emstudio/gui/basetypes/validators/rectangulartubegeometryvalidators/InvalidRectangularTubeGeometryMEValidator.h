/*
 * InvalidRectangularTubeGeometryMEValidator.h
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#ifndef INVALIDRECTANGULARTUBEGEOMETRYMEVALIDATOR_H_
#define INVALIDRECTANGULARTUBEGEOMETRYMEVALIDATOR_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "emstudio/gui/basetypes/RectangularTubeGeometryME.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

class InvalidRectangularTubeGeometryMEValidator : public BaseTypeValidator {
private:
	bool expressionsValid;
	bool lengthOK;
	bool baseCoord1OK;
	bool baseCoord2OK;
	bool baseCoord1ThickDifZero;
	bool baseCoord2ThickDifZero;
	bool topCoord1OK;
	bool topCoord2OK;
	bool topCoord1ThickDifZero;
	bool topCoord2ThickDifZero;
public:
	InvalidRectangularTubeGeometryMEValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidRectangularTubeGeometryMEValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

#endif /* INVALIDRECTANGULARTUBEGEOMETRYMEVALIDATOR_H_ */
