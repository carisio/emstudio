/*
 * InvalidGroundParametersValidators.h
 *
 *  Created on: 19/03/2015
 *      Author: leandrocarisio
 */

#ifndef INVALIDGROUNDPARAMETERSVALIDATORS_H_
#define INVALIDGROUNDPARAMETERSVALIDATORS_H_

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "emstudio/gui/basetypes/GroundParameters.h"
#include "../BaseTypeValidator.h"
#include "wx/wx.h"

namespace mom {

class InvalidGroundParametersValidators : public BaseTypeValidator {
private:
	bool expressionsValid;
	bool ground2DefinedWithoutGround1;
	bool ground2DefinedAsFreeSpace;
	bool distBelowGroundGTOEZero;
	bool distFromOriginGTZero;
	bool nWiresGTOEZero;
	bool wireLengthGTOEZero;
	bool wireRadiusGTOEZero;
	bool radialsDoesNotFluctuateOverGround2;
public:
	InvalidGroundParametersValidators(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~InvalidGroundParametersValidators();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);

	virtual bool DoIsValid(BaseType* b);
};

} /* namespace mom */
#endif /* INVALIDGROUNDPARAMETERSVALIDATORS_H_ */
