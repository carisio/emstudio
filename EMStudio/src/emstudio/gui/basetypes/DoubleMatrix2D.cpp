/*
 * DoubleMatrix2D.cpp
 *
 *  Created on: 28/04/2013
 *      Author: Leandro
 */

#include "DoubleMatrix2D.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

DoubleMatrix2D::DoubleMatrix2D() : data(Array2D<double>(1, 1)) {
	SetWriteVersion(1);
}

DoubleMatrix2D::~DoubleMatrix2D() {
}

void DoubleMatrix2D::Copy(BaseType* b) {
	data = ((static_cast<DoubleMatrix2D*>(b))->GetData());
}

wxString DoubleMatrix2D::GetBaseTypeClassName() {
	return "DoubleMatrix2D";
}

void DoubleMatrix2D::SetUserFriendlyStringRepresentation(wxString str) {
	// Não faz nada, pois não tem como fazer essa atribuição
}
wxString DoubleMatrix2D::GetUserFriendlyStringRepresentation() {
	return "";
}
void DoubleMatrix2D::DoWrite(OutputBuffer& buffer) {
	buffer.WriteArray2D(data);
}
void DoubleMatrix2D::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	data = buffer.ReadArray2D();
}

Array2D<double>& DoubleMatrix2D::GetData() {
	return data;
}
void DoubleMatrix2D::SetData(Array2D<double> v) {
	data = v;
}
