/*
 * FloatWrapper.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "FloatWrapper.h"

FloatWrapper::FloatWrapper()
	: value(0.0f) {
	SetWriteVersion(1);
}

FloatWrapper::~FloatWrapper() {

}

float FloatWrapper::GetValue() const {
    return value;
}

void FloatWrapper::SetValue(float value) {
    this->value = value;
}

void FloatWrapper::Copy(BaseType* b) {
	this->SetValue((static_cast<FloatWrapper*>(b))->GetValue());
}

wxString FloatWrapper::GetBaseTypeClassName() {
	return "FloatWrapper";
}

wxString FloatWrapper::GetUserFriendlyStringRepresentation() {
	return Converter::FloatToFormattedString(value);
}

void FloatWrapper::SetUserFriendlyStringRepresentation(wxString str) {
	SetValue(Converter::FormattedStringToFloat(str));
}
void FloatWrapper::DoWrite(OutputBuffer& buffer) {
	buffer.WriteFloat(value);
}
void FloatWrapper::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	value = buffer.ReadFloat();
}
