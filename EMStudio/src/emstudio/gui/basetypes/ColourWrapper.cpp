/*
 * ColourWrapper.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "ColourWrapper.h"

ColourWrapper::ColourWrapper()
	: value() {
	SetWriteVersion(1);
}

wxColour ColourWrapper::GetValue() const {
    return value;
}

void ColourWrapper::SetValue(wxColour value) {
    this->value = value;
}

ColourWrapper::~ColourWrapper() {

}

void ColourWrapper::Copy(BaseType* b) {
	this->SetValue((static_cast<ColourWrapper*>(b))->GetValue());
}

wxString ColourWrapper::GetBaseTypeClassName() {
	return "ColourWrapper";
}

wxString ColourWrapper::GetUserFriendlyStringRepresentation() {
	wxString result;
	result.append(Converter::IntToFormattedString(value.Red())).append(" ").append(Converter::IntToFormattedString(value.Green())).append(" ").append(Converter::IntToFormattedString(value.Blue()));
	return result;
}

void ColourWrapper::SetUserFriendlyStringRepresentation(wxString str) {
	wxStringTokenizer tokenizer(str, " ");

	wxString r = tokenizer.GetNextToken();
	wxString g = tokenizer.GetNextToken();
	wxString b = tokenizer.GetNextToken();

	SetValue(wxColour(Converter::FormattedStringToInt(r), Converter::FormattedStringToInt(g), Converter::FormattedStringToInt(b)));
}
void ColourWrapper::DoWrite(OutputBuffer& buffer) {
	char c = value.Red();
	buffer.WriteChar(c);
	c = value.Green();
	buffer.WriteChar(c);
	c = value.Blue();
	buffer.WriteChar(c);
}
void ColourWrapper::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	char r = buffer.ReadChar();
	char g = buffer.ReadChar();
	char b = buffer.ReadChar();

	value.Set(r, g, b);
}
