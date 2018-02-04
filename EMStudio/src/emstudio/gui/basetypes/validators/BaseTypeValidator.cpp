/*
 * BaseTypeValidator.cpp
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#include "BaseTypeValidator.h"
#include "wx/log.h"

BaseTypeValidator::BaseTypeValidator(BaseTypeValidatorSmartPointer parent)
	: parent(parent) {

}

BaseTypeValidator::~BaseTypeValidator() {

}
BaseTypeValidatorSmartPointer BaseTypeValidator::GetParent() {
	return parent;
}
void BaseTypeValidator::SetParent(BaseTypeValidatorSmartPointer p) {
	parent = p;
}

bool BaseTypeValidator::IsValid(BaseType* b) {
	bool result = DoIsValid(b);

	if (parent != 0) {
		wxLogDebug("Meu resultado eh %d e o resultado do meu pai eh %d", result, parent->IsValid(b));
		result = result && parent->IsValid(b);
	}

	return result;
}

wxString BaseTypeValidator::GetErrorMessage(BaseType* b, wxString baseTypeName) {
	bool valid = DoIsValid(b);
	wxString result;
	if (!valid) {
		result = DoGetErrorMessage(b, baseTypeName).Append("\n");

		wxLogDebug("Eu nao sou valido. Esta eh a minha mensagem: %s", result.c_str());
	}

	if (parent != 0 && !(parent->IsValid(b))) {
		result.Append(parent->GetErrorMessage(b, baseTypeName));
		wxLogDebug("Esta eh a mensagem de erro do meu pai: %s", result.c_str());
	}

	return result;
}
