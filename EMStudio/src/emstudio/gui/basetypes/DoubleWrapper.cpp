/*
 * DoubleWrapper.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "DoubleWrapper.h"

DoubleWrapper::DoubleWrapper()
	: value(0) {
	SetWriteVersion(1);
}

double DoubleWrapper::GetValue() const {
    return value;
}

void DoubleWrapper::SetValue(double value) {
    this->value = value;
}

DoubleWrapper::~DoubleWrapper() {

}

void DoubleWrapper::Copy(BaseType* b) {
	this->SetValue((static_cast<DoubleWrapper*>(b))->GetValue());
}

wxString DoubleWrapper::GetBaseTypeClassName() {
	return "DoubleWrapper";
}

wxString DoubleWrapper::GetUserFriendlyStringRepresentation() {
	return Converter::DoubleToFormattedString(value);
}

void DoubleWrapper::SetUserFriendlyStringRepresentation(wxString str) {
	SetValue(Converter::FormattedStringToDouble(str));
}
void DoubleWrapper::DoWrite(OutputBuffer& buffer) {
	buffer.WriteDouble(value);
}
void DoubleWrapper::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	value = buffer.ReadDouble();
}
