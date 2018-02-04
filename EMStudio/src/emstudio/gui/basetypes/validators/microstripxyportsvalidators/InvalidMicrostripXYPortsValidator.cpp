/*
 * InvalidMicrostripXYPortsValidator.cpp
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#include "InvalidMicrostripXYPortsValidator.h"

InvalidMicrostripXYPortsValidator::InvalidMicrostripXYPortsValidator(BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent) {

}

InvalidMicrostripXYPortsValidator::~InvalidMicrostripXYPortsValidator() {

}


wxString InvalidMicrostripXYPortsValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" has an invalid expression.");
}

bool InvalidMicrostripXYPortsValidator::DoIsValid(BaseType* b) {
	MicrostripXYPortsME* ports = static_cast<MicrostripXYPortsME*>(b);

	return ports->IsPortsValid();
}

