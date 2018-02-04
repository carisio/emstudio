/*
 * InvalidGenericSheetValidator.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "InvalidGenericSheetMEValidator.h"

InvalidGenericSheetMEValidator::InvalidGenericSheetMEValidator(BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent) {

}

InvalidGenericSheetMEValidator::~InvalidGenericSheetMEValidator() {

}


wxString InvalidGenericSheetMEValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" has an invalid expression.");
}

bool InvalidGenericSheetMEValidator::DoIsValid(BaseType* b) {
	GenericSheetME* gs = static_cast<GenericSheetME*>(b);

	return gs->IsGenericSheetValid();
}

