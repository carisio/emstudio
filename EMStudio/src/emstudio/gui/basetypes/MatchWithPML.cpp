/*
 * MatchWithPML.cpp
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#include "MatchWithPML.h"

MatchWithPML::MatchWithPML() : matchWithPML(0) {
	SetWriteVersion(1);
}

MatchWithPML::~MatchWithPML() {
}

void MatchWithPML::SetUserFriendlyStringRepresentation(wxString s) {

}
wxString MatchWithPML::GetUserFriendlyStringRepresentation() {
	return Converter::BoolToFormattedString(matchWithPML);
}

void MatchWithPML::DoWrite(OutputBuffer& buffer) {
	buffer.WriteChar(matchWithPML);
}
void MatchWithPML::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	matchWithPML = buffer.ReadChar();
}

void MatchWithPML::Copy(BaseType* b) {
	MatchWithPML* ptr = (static_cast<MatchWithPML*>(b));

	matchWithPML = ptr->matchWithPML;
}

wxString MatchWithPML::GetBaseTypeClassName() {
	return "MatchWithPML";
}

void MatchWithPML::SetMatchedWithPML(char bit, bool state) {
	if (state)
		SetBit(bit);
	else
		UnsetBit(bit);
}
void MatchWithPML::SetBit(char bit) {
	matchWithPML = matchWithPML | bit;
}
void MatchWithPML::UnsetBit(char bit) {
	matchWithPML = matchWithPML & (~bit);
}

bool MatchWithPML::IsMatchedWithPML(char wall) {
	return (matchWithPML & wall);
}
