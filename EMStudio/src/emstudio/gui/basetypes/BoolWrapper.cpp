/*
 * BoolWrapper.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "BoolWrapper.h"
#include "emstudio/util/converters/Converter.h"

BoolWrapper::BoolWrapper()
	: value(false) {
	SetWriteVersion(1);
}

bool BoolWrapper::IsValue() const {
    return value;
}

void BoolWrapper::SetValue(bool value) {
    this->value = value;
}

BoolWrapper::~BoolWrapper() {

}

void BoolWrapper::Copy(BaseType* b) {
	this->SetValue((static_cast<BoolWrapper*>(b))->IsValue());
}

wxString BoolWrapper::GetBaseTypeClassName() {
	return "BoolWrapper";
}

wxString BoolWrapper::GetUserFriendlyStringRepresentation() {
	return Converter::BoolToFormattedString(value);
}

void BoolWrapper::SetUserFriendlyStringRepresentation(wxString str) {
	SetValue(Converter::FormattedStringToBool(str));
}

void BoolWrapper::DoWrite(OutputBuffer& buffer) {
	buffer.WriteBool(value);
}
void BoolWrapper::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	value = buffer.ReadBool();
}
