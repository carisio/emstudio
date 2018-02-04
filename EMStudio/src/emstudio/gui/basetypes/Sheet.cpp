/*
 * Sheet.cpp
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#include "Sheet.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

Sheet::Sheet()
	: x0(0), y0(0), z0(0), x1(0), y1(0), z1(0) {
	SetWriteVersion(1);
	SetCutAtZ(25);
}

Sheet::~Sheet() {
}

double Sheet::GetX0() {
	return x0;
}
double Sheet::GetY0() {
	return y0;
}
double Sheet::GetZ0() {
	return z0;
}
double Sheet::GetX1() {
	return x1;
}
double Sheet::GetY1() {
	return y1;
}
double Sheet::GetZ1() {
	return z1;
}
void Sheet::SetX0(double x) {
	x0 = x;
}
void Sheet::SetY0(double y) {
	y0 = y;
}
void Sheet::SetZ0(double z) {
	z0 = z;
}
void Sheet::SetX1(double x) {
	x1 = x;
}
void Sheet::SetY1(double y) {
	y1 = y;
}
void Sheet::SetZ1(double z) {
	z1 = z;
}
bool Sheet::IsCutAtX() {
	return plane == Sheet::YZ;
}
bool Sheet::IsCutAtY() {
	return plane == Sheet::ZX;
}
bool Sheet::IsCutAtZ() {
	return plane == Sheet::XY;
}
void Sheet::SetCutAtX(double x) {
	plane = Sheet::YZ;
	x0 = x;
	x1 = x;
}
void Sheet::SetCutAtY(double y) {
	plane = Sheet::ZX;
	y0 = y;
	y1 = y;
}
void Sheet::SetCutAtZ(double z) {
	plane = Sheet::XY;
	z0 = z;
	z1 = z;
}

void Sheet::Copy(BaseType* p) {
	Sheet* pSheet = static_cast<Sheet*>(p);
	SetX0(pSheet->GetX0());
	SetX1(pSheet->GetX1());
	SetY0(pSheet->GetY0());
	SetY1(pSheet->GetY1());
	SetZ0(pSheet->GetZ0());
	SetZ1(pSheet->GetZ1());
	if (pSheet->IsCutAtX()) {
		SetCutAtX(pSheet->GetCutAt());
	} else if (pSheet->IsCutAtY()) {
		SetCutAtY(pSheet->GetCutAt());
	} else if (pSheet->IsCutAtZ()) {
		SetCutAtZ(pSheet->GetCutAt());
	}
}
double Sheet::GetCutAt() {
	if (IsCutAtX()) {
		return x0;
	} else if (IsCutAtY()) {
		return y0;
	} else if (IsCutAtZ()) {
		return z0;
	}
	return 0;
}
wxString Sheet::GetBaseTypeClassName() {
	return "Sheet";
}

wxString Sheet::GetUserFriendlyStringRepresentation() {
	wxString result;
	if (IsCutAtX()) {
		double y = y1-y0; y = y < 0 ? -y : y;
		double z = z1-z0; z = z < 0 ? -z : z;

		result.Append("X = ").
				Append(Converter::DoubleToFormattedString(x0, 2)).
				Append(", ").
				Append(Converter::DoubleToFormattedString(y, 2)).
				Append(" x ").
				Append(Converter::DoubleToFormattedString(z, 2));

	} else if (IsCutAtY()) {
		double x = x1-x0; x = x < 0 ? -x : x;
		double z = z1-z0; z = z < 0 ? -z : z;

		result.Append("Y = ").
				Append(Converter::DoubleToFormattedString(y0, 2)).
				Append(", ").
				Append(Converter::DoubleToFormattedString(x, 2)).
				Append(" x ").
				Append(Converter::DoubleToFormattedString(z, 2));
	} else if (IsCutAtZ()) {
		double x = x1-x0; x = x < 0 ? -x : x;
		double y = y1-y0; y = y < 0 ? -y : y;

		result.Append("Z = ").
				Append(Converter::DoubleToFormattedString(z0, 2)).
				Append(", ").
				Append(Converter::DoubleToFormattedString(x, 2)).
				Append(" x ").
				Append(Converter::DoubleToFormattedString(y, 2));
	}
	return result;
}

void Sheet::SetUserFriendlyStringRepresentation(wxString str) {

}

void Sheet::DoWrite(OutputBuffer& buffer) {

	buffer.WriteInt(plane);
	buffer.WriteDouble(x0);
	buffer.WriteDouble(y0);
	buffer.WriteDouble(z0);
	buffer.WriteDouble(x1);
	buffer.WriteDouble(y1);
	buffer.WriteDouble(z1);
}
void Sheet::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	plane = buffer.ReadInt();
	x0 = buffer.ReadDouble();
	y0 = buffer.ReadDouble();
	z0 = buffer.ReadDouble();
	x1 = buffer.ReadDouble();
	y1 = buffer.ReadDouble();
	z1 = buffer.ReadDouble();
}
