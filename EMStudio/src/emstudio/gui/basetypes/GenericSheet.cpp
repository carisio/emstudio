/*
 * GenericSheet.cpp
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#include "GenericSheet.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"
#include <iostream>

GenericSheet::GenericSheet() : coordinates(), cutAt(10) {
	SetWriteVersion(1);

	plane = GenericSheet::XY;
	coordinates.push_back(pair<double, double>(5,5));
	coordinates.push_back(pair<double, double>(5,10));
	coordinates.push_back(pair<double, double>(10,10));
}

GenericSheet::~GenericSheet() {
}

bool GenericSheet::IsCutAtX() {
	return plane == GenericSheet::YZ;
}
bool GenericSheet::IsCutAtY() {
	return plane == GenericSheet::ZX;
}
bool GenericSheet::IsCutAtZ() {
	return plane == GenericSheet::XY;
}
void GenericSheet::SetCutAtX(double x) {
	plane = GenericSheet::YZ;
	cutAt = x;
}
void GenericSheet::SetCutAtY(double y) {
	plane = GenericSheet::ZX;
	cutAt = y;
}
void GenericSheet::SetCutAtZ(double z) {
	plane = GenericSheet::XY;
	cutAt = z;
}

std::vector<std::pair<double, double> > GenericSheet::GetCoordinates() {
	return coordinates;
}
void GenericSheet::SetCoordinates(std::vector<std::pair<double, double> > coor) {
	coordinates = coor;
}

void GenericSheet::Copy(BaseType* p) {
	GenericSheet* pGenericSheet = static_cast<GenericSheet*>(p);

	if (pGenericSheet->IsCutAtX()) {
		SetCutAtX(pGenericSheet->GetCutAt());
	} else if (pGenericSheet->IsCutAtY()) {
		SetCutAtY(pGenericSheet->GetCutAt());
	} else if (pGenericSheet->IsCutAtZ()) {
		SetCutAtZ(pGenericSheet->GetCutAt());
	}
	SetCoordinates(pGenericSheet->GetCoordinates());
}
double GenericSheet::GetCutAt() {
	return cutAt;
}
wxString GenericSheet::GetBaseTypeClassName() {
	return "GenericSheet";
}

wxString GenericSheet::GetUserFriendlyStringRepresentation() {
	wxString result;
	if (IsCutAtX()) {
		result.Append("X = ").
				Append(Converter::DoubleToFormattedString(cutAt, 2));

	} else if (IsCutAtY()) {
		result.Append("Y = ").
				Append(Converter::DoubleToFormattedString(cutAt, 2));
	} else if (IsCutAtZ()) {
		result.Append("Z = ").
				Append(Converter::DoubleToFormattedString(cutAt, 2));
	}
	result.Append(", ").Append(Converter::IntToFormattedString(coordinates.size())).Append(" vertex");

	return result;
}

void GenericSheet::SetUserFriendlyStringRepresentation(wxString str) {

}
void GenericSheet::DoWrite(OutputBuffer& buffer) {
	buffer.WriteInt(plane);
	buffer.WriteDouble(cutAt);

	int size = coordinates.size();
	buffer.WriteInt(size);

	vector<pair<double, double> >::iterator it = coordinates.begin();
	vector<pair<double, double> >::iterator end = coordinates.end();

	while(it != end) {
		buffer.WriteDouble(it->first);
		buffer.WriteDouble(it->second);
		it++;
	}
}
void GenericSheet::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	plane = buffer.ReadInt();
	cutAt = buffer.ReadDouble();

	int size = buffer.ReadInt();

	vector<pair<double, double> > newCoordinates;
	for (int i = 0; i < size; i++) {
		double x = buffer.ReadDouble();
		double y = buffer.ReadDouble();
		newCoordinates.push_back(pair<double, double>(x, y));
	}

	coordinates = newCoordinates;
}

