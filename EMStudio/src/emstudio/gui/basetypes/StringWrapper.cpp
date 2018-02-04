/*
 * StringWrapper.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "StringWrapper.h"

StringWrapper::StringWrapper()
	: value("") {
	SetWriteVersion(1);
}

wxString StringWrapper::GetValue() const {
    return value;
}

void StringWrapper::SetValue(wxString s) {
	value = s;
}
StringWrapper::~StringWrapper() {

}

void StringWrapper::Copy(BaseType* b) {
	value = ((static_cast<StringWrapper*>(b))->GetValue());
}

wxString StringWrapper::GetBaseTypeClassName() {
	return "StringWrapper";
}

wxString StringWrapper::GetUserFriendlyStringRepresentation() {
	return GetValue();
}

void StringWrapper::SetUserFriendlyStringRepresentation(wxString str) {
	SetValue(str);
}
void StringWrapper::DoWrite(OutputBuffer& buffer) {
	buffer.WriteString(value);

}
void StringWrapper::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	value = buffer.ReadString();
}
