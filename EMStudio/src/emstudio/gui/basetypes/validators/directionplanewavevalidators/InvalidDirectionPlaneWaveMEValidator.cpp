/*
 * InvalidDirectionPlaneWaveMEValidator.cpp
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#include "InvalidDirectionPlaneWaveMEValidator.h"

InvalidDirectionPlaneWaveMEValidator::InvalidDirectionPlaneWaveMEValidator(BaseTypeValidatorSmartPointer parent)
		: BaseTypeValidator(parent) {

}

InvalidDirectionPlaneWaveMEValidator::~InvalidDirectionPlaneWaveMEValidator() {

}


wxString InvalidDirectionPlaneWaveMEValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" has an invalid expression.");
}

bool InvalidDirectionPlaneWaveMEValidator::DoIsValid(BaseType* b) {
	DirectionPlaneWaveME* d = static_cast<DirectionPlaneWaveME*>(b);

	return d->isExpressionsValid();
}
