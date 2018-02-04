/*
 * DoubleVector.cpp
 *
 *  Created on: 28/04/2013
 *      Author: Leandro
 */

#include "DoubleVector.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

DoubleVector::DoubleVector() : data(Array1D<double>(1)){
	SetWriteVersion(1);
}

DoubleVector::~DoubleVector() {
}

void DoubleVector::Copy(BaseType* b) {
	data = ((static_cast<DoubleVector*>(b))->GetData());
}

wxString DoubleVector::GetBaseTypeClassName() {
	return "DoubleVector";
}

void DoubleVector::SetUserFriendlyStringRepresentation(wxString str) {
	// Não faz nada, pois não tem como fazer essa atribuição
}
wxString DoubleVector::GetUserFriendlyStringRepresentation() {
	return "";
}
void DoubleVector::DoWrite(OutputBuffer& buffer) {
	buffer.WriteArray1D(data);
}
void DoubleVector::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	data = buffer.ReadArray1D();
}

Array1D<double>& DoubleVector::GetData() {
	return data;
}
void DoubleVector::SetData(Array1D<double> v) {
	data = v;
}
