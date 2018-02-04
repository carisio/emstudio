/*
 * IntWrapper.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "IntWrapper.h"

IntWrapper::IntWrapper()
	: value(0) {
	SetWriteVersion(1);
}

IntWrapper::~IntWrapper() {

}

int IntWrapper::GetValue() const {
    return value;
}

void IntWrapper::SetValue(int value) {
    this->value = value;
}

void IntWrapper::Copy(BaseType* b) {
	this->SetValue((static_cast<IntWrapper*>(b))->GetValue());
}

wxString IntWrapper::GetBaseTypeClassName() {
	return "IntWrapper";
}

wxString IntWrapper::GetUserFriendlyStringRepresentation() {
	return Converter::IntToFormattedString(value);
}

void IntWrapper::SetUserFriendlyStringRepresentation(wxString str) {
	SetValue(Converter::FormattedStringToInt(str));
}
void IntWrapper::DoWrite(OutputBuffer& buffer) {
	buffer.WriteInt(value);
}
void IntWrapper::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	value = buffer.ReadInt();
}
