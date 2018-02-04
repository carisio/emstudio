/*
 * DefaultValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#include "DefaultValidator.h"

DefaultValidator::DefaultValidator(BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent) {

}

DefaultValidator::~DefaultValidator() {
}

wxString DefaultValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return "";
}
bool DefaultValidator::DoIsValid(BaseType* b) {
	return true;
}
