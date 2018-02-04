/*
 * Property.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "Property.h"

Property::Property(wxString name, BaseType* baseType, BaseTypeValidatorSmartPointer validator)
	: name(name), baseType(baseType), baseTypeName(baseType->GetBaseTypeClassName()), validator(validator) {

}

Property::Property(wxString name, BaseType* baseType)
	: name(name), baseType(baseType), baseTypeName(baseType->GetBaseTypeClassName()) {

	validator = BaseTypeValidatorSmartPointer(new DefaultValidator());
}

BaseType* Property::GetValue() {
	return baseType;
}
void Property::SetValue(BaseType* baseType) {
	this->baseType->Copy(baseType);
}

wxString Property::GetName() const {
    return name;
}

wxString Property::GetBaseTypeClassName() {
	return baseTypeName;
}
Property::~Property() {
	// Não pode apagar o ponteiro aqui, pois a propriedade não vive sem o ElementGUI. ElementGUI apagará as coisas.
}
BaseTypeValidatorSmartPointer Property::GetValidator() {
	return validator;
}
void Property::SetValidator(BaseTypeValidatorSmartPointer validator) {
	this->validator = validator;
}
bool Property::IsValid() {
	return validator->IsValid(baseType);
}
wxString Property::GetErrorMessage() {
	return validator->GetErrorMessage(baseType, name);
}
