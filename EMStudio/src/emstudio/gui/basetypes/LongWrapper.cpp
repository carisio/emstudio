/*
 * LongWrapper.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "LongWrapper.h"

LongWrapper::LongWrapper()
	: value(0) {
	SetWriteVersion(1);
}

long LongWrapper::GetValue() const {
    return value;
}

void LongWrapper::SetValue(long value) {
    this->value = value;
}

LongWrapper::~LongWrapper() {

}

void LongWrapper::Copy(BaseType* b) {
	this->SetValue((static_cast<LongWrapper*>(b))->GetValue());
}

wxString LongWrapper::GetUserFriendlyStringRepresentation() {
	return Converter::LongToFormattedString(value);
}

void LongWrapper::SetUserFriendlyStringRepresentation(wxString str) {
	SetValue(Converter::FormattedStringToLong(str));
}

wxString LongWrapper::GetBaseTypeClassName() {
	return "LongWrapper";
}

void LongWrapper::DoWrite(OutputBuffer& buffer) {
	buffer.WriteLong(value);
}
void LongWrapper::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	value = buffer.ReadLong();
}
