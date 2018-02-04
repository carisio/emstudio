/*
 * Point3D.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "Point3D.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

Point3D::Point3D()
	: x(0), y(0), z(0) {
	SetWriteVersion(1);
}

void Point3D::SetX(double x) {
	this->x = x;
}
void Point3D::SetY(double y) {
	this->y = y;
}
void Point3D::SetZ(double z) {
	this->z = z;
}
double Point3D::GetX() const {
	return x;
}
double Point3D::GetY() const {
	return y;
}
double Point3D::GetZ() const {
	return z;
}

void Point3D::Copy(BaseType* p) {
	SetX(((static_cast<Point3D*>(p))->GetX()));
	SetY(((static_cast<Point3D*>(p))->GetY()));
	SetZ(((static_cast<Point3D*>(p))->GetZ()));
}

wxString Point3D::GetBaseTypeClassName() {
	return "Point3D";
}

wxString Point3D::GetUserFriendlyStringRepresentation() {
	return "(" + Converter::DoubleToFormattedString(x, 2) + " " +
			Converter::DoubleToFormattedString(y, 2) + " " +
			Converter::DoubleToFormattedString(z, 2) + ")";
}

void Point3D::SetUserFriendlyStringRepresentation(wxString str) {

}
void Point3D::DoWrite(OutputBuffer& buffer) {
	buffer.WriteDouble(x);
	buffer.WriteDouble(y);
	buffer.WriteDouble(z);
}
void Point3D::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	x = buffer.ReadDouble();
	y = buffer.ReadDouble();
	z = buffer.ReadDouble();
}

Point3D::~Point3D() {
}
