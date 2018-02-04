/*
 * InvalidExcitationMEValidator.cpp
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#include "InvalidExcitationMEValidator.h"

InvalidExcitationMEValidator::InvalidExcitationMEValidator(BaseTypeValidatorSmartPointer parent)
		: BaseTypeValidator(parent) {

}

InvalidExcitationMEValidator::~InvalidExcitationMEValidator() {

}


wxString InvalidExcitationMEValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" has an invalid expression.");
}

bool InvalidExcitationMEValidator::DoIsValid(BaseType* b) {
	ExcitationME* e = static_cast<ExcitationME*>(b);

	return e->IsExcitationValid();
}
