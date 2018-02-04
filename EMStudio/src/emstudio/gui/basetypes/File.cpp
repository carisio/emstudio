/*
 * File.cpp
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#include "File.h"

File::File() : fileName(""), wildcard("Text files (*.txt)|*.txt") {
	SetWriteVersion(1);
}

File::~File() {

}

void File::SetFileName(wxString fileName) {
	this->fileName = fileName;
}
void File::SetWildcard(wxString wildcard) {
	this->wildcard = wildcard;
}
wxString File::GetFileName() {
	return fileName;
}
wxString File::GetWildcard() {
	return wildcard;
}
/**
 * Retorna true se o processamento do arquivo tiver sido bem sucedido, false caso contrário
 */
bool File::ProcessFile(wxString fileName) {
	return true;
}
void File::Copy(BaseType* p) {
	fileName = (((static_cast<File*>(p))->GetFileName()));
	wildcard = (((static_cast<File*>(p))->GetWildcard()));
}

wxString File::GetBaseTypeClassName() {
	return "File";
}

wxString File::GetUserFriendlyStringRepresentation() {
	wxString shortFileName = "";
	if (fileName != "")
		shortFileName = fileName.Mid(fileName.Last('\\'));

	return shortFileName;
}

void File::SetUserFriendlyStringRepresentation(wxString str) {
	// Faz nada
}
void File::DoWrite(OutputBuffer& buffer) {
	buffer.WriteString(fileName);
	buffer.WriteString(wildcard);
}
void File::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	fileName = buffer.ReadString();
	wildcard = buffer.ReadString();
}


