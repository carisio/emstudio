/*
 * DoubleMatrix3D.cpp
 *
 *  Created on: 28/04/2013
 *      Author: Leandro
 */

#include "DoubleMatrix3D.h"
#include "wx/tokenzr.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/time/TicTac.h"

DoubleMatrix3D::DoubleMatrix3D() : data(Array3D<double>(1, 1, 1)){
	SetWriteVersion(1);
}

DoubleMatrix3D::~DoubleMatrix3D() {
}

void DoubleMatrix3D::Copy(BaseType* b) {
	data = ((static_cast<DoubleMatrix3D*>(b))->GetData());
}

wxString DoubleMatrix3D::GetBaseTypeClassName() {
	return "DoubleMatrix3D";
}

void DoubleMatrix3D::SetUserFriendlyStringRepresentation(wxString str) {
	// Não faz nada, pois não tem como fazer essa atribuição
}
wxString DoubleMatrix3D::GetUserFriendlyStringRepresentation() {
	return "";
}
void DoubleMatrix3D::DoWrite(OutputBuffer& buffer) {
	buffer.WriteArray3D(data);
}
void DoubleMatrix3D::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	data = buffer.ReadArray3D();
}

Array3D<double>& DoubleMatrix3D::GetData() {
	return data;
}
void DoubleMatrix3D::SetData(Array3D<double> v) {
	data = v;
}
