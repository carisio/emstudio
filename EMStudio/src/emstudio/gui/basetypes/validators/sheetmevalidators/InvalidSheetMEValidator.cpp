/*
 * InvalidSheetMEValidator.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "InvalidSheetMEValidator.h"

InvalidSheetMEValidator::InvalidSheetMEValidator(BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent) {

}

InvalidSheetMEValidator::~InvalidSheetMEValidator() {

}


wxString InvalidSheetMEValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" has an invalid expression.");
}

bool InvalidSheetMEValidator::DoIsValid(BaseType* b) {
	SheetME* point3D = static_cast<SheetME*>(b);

	return point3D->IsSheetValid();
}
