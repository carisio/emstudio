/*
 * GenericSheetME.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetME.h"

#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"
#include <iostream>

GenericSheetME::GenericSheetME() : coordinates(), cutAt("10") {
	SetWriteVersion(1);

	plane = GenericSheetME::XY;
	coordinates.push_back(std::pair<wxString, wxString>("5", "5"));
	coordinates.push_back(std::pair<wxString, wxString>("5", "10"));
	coordinates.push_back(std::pair<wxString, wxString>("10", "10"));
}

GenericSheetME::~GenericSheetME() {
}

bool GenericSheetME::IsCutAtX() {
	return plane == GenericSheetME::YZ;
}
bool GenericSheetME::IsCutAtY() {
	return plane == GenericSheetME::ZX;
}
bool GenericSheetME::IsCutAtZ() {
	return plane == GenericSheetME::XY;
}
void GenericSheetME::SetCutAtX(wxString x) {
	plane = GenericSheetME::YZ;
	cutAt = x;

	// Atualiza também gs
	BuildGS();
}
void GenericSheetME::SetCutAtY(wxString y) {
	plane = GenericSheetME::ZX;
	cutAt = y;

	// Atualiza também gs
	BuildGS();
}
void GenericSheetME::SetCutAtZ(wxString z) {
	plane = GenericSheetME::XY;
	cutAt = z;

	// Atualiza também gs
	BuildGS();
}

std::vector<std::pair<wxString, wxString> > GenericSheetME::GetCoordinates() {
	return coordinates;
}
void GenericSheetME::SetCoordinates(std::vector<std::pair<wxString, wxString> > coor) {
	coordinates = coor;

	// Atualiza também gs
	BuildGS();
}
double GenericSheetME::GetCutAt() {
	MathParser mp;
	mp.SetExpression(cutAt);
	mp.DefineConstantsAndCheckIfIsValid();
	return mp.Eval();
}
wxString GenericSheetME::GetCutAtExpression() {
	return cutAt;
}
void GenericSheetME::Copy(BaseType* p) {
	GenericSheetME* pGenericSheet = static_cast<GenericSheetME*>(p);

	if (pGenericSheet->IsCutAtX()) {
		SetCutAtX(pGenericSheet->GetCutAtExpression());
	} else if (pGenericSheet->IsCutAtY()) {
		SetCutAtY(pGenericSheet->GetCutAtExpression());
	} else if (pGenericSheet->IsCutAtZ()) {
		SetCutAtZ(pGenericSheet->GetCutAtExpression());
	}
	SetCoordinates(pGenericSheet->GetCoordinates());
}
wxString GenericSheetME::GetBaseTypeClassName() {
	return "GenericSheetME";
}

wxString GenericSheetME::GetUserFriendlyStringRepresentation() {
	if (!IsGenericSheetValid()) {
		return "Invalid expression";
	}

	MathParser p;
	p.SetExpression(GetCutAtExpression());
	p.DefineConstantsAndCheckIfIsValid();
	wxString cutAtStr = Converter::DoubleToFormattedString(p.Eval(), 2);

	wxString result;
	if (IsCutAtX()) {
		result.Append("X = ").Append(cutAtStr);
	} else if (IsCutAtY()) {
		result.Append("Y = ").Append(cutAtStr);
	} else if (IsCutAtZ()) {
		result.Append("Z = ").Append(cutAtStr);
	}
	result.Append(", ").Append(Converter::IntToFormattedString(coordinates.size())).Append(" vertex");

	return result;
}
bool GenericSheetME::IsGenericSheetValid() {
	bool result = true;
	MathParser p;
	p.SetExpression(GetCutAtExpression());
	result = p.DefineConstantsAndCheckIfIsValid();

	for (size_t i = 0; i < coordinates.size() && result; i++) {
		p.SetExpression(coordinates[i].first);
		result = result && p.DefineConstantsAndCheckIfIsValid();
		p.SetExpression(coordinates[i].second);
		result = result && p.DefineConstantsAndCheckIfIsValid();
	}

	return result;
}
void GenericSheetME::BuildGS() {
	// Atualiza também gs
	MathParser mp;

	std::vector<std::pair<double, double> > coord;
	for (size_t i = 0; i < coordinates.size(); i++) {
		mp.SetExpression(coordinates[i].first);
		mp.DefineConstantsAndCheckIfIsValid();
		double p1 = mp.Eval();
		mp.SetExpression(coordinates[i].second);
		mp.DefineConstantsAndCheckIfIsValid();
		double p2 = mp.Eval();
		std::pair<double, double> p = std::pair<double, double>(p1, p2);
		coord.push_back(p);
	}
	gs.SetCoordinates(coord);

	mp.SetExpression(GetCutAtExpression());
	mp.DefineConstantsAndCheckIfIsValid();
	if (IsCutAtX()) {
		gs.SetCutAtX(mp.Eval());
	} else if (IsCutAtY()) {
		gs.SetCutAtY(mp.Eval());
	} else if (IsCutAtZ()) {
		gs.SetCutAtZ(mp.Eval());
	}
}

GenericSheet GenericSheetME::ConvertToGenericSheet(bool forceRebuildGenericSheet) {
	// Reconstroi gs
	if (forceRebuildGenericSheet)
		BuildGS();

	return gs;
}
void GenericSheetME::SetUserFriendlyStringRepresentation(wxString str) {

}
void GenericSheetME::DoWrite(OutputBuffer& buffer) {
	MathParser mp;

	// Plane
	buffer.WriteInt(plane);
	// CutAtExpression
	mp.SetExpression(cutAt);
	wxString expWithDecPtInfo = mp.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(expWithDecPtInfo);
	// Coordinates size
	int size = coordinates.size();
	buffer.WriteInt(size);
	// Coordinates
	std::vector<std::pair<wxString, wxString> >::iterator it = coordinates.begin();
	std::vector<std::pair<wxString, wxString> >::iterator end = coordinates.end();

	while(it != end) {
		mp.SetExpression(it->first);
		expWithDecPtInfo = mp.GetExpressionWithDecimalSeparatorInformation();
		buffer.WriteString(expWithDecPtInfo);
		mp.SetExpression(it->second);
		expWithDecPtInfo = mp.GetExpressionWithDecimalSeparatorInformation();
		buffer.WriteString(expWithDecPtInfo);
		it++;
	}
}
void GenericSheetME::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	MathParser mp;

	int plane = buffer.ReadInt();
	wxString cutAtExp = buffer.ReadString();
	mp.SetExpressionWithDecimalSeparatorInformation(cutAtExp);
	wxString cutAt = mp.GetExpression();

	int size = buffer.ReadInt();

	std::vector<std::pair<wxString, wxString> > newCoordinates;
	for (int i = 0; i < size; i++) {
		wxString xExp = buffer.ReadString();
		wxString yExp = buffer.ReadString();
		mp.SetExpressionWithDecimalSeparatorInformation(xExp);
		wxString x = mp.GetExpression();
		mp.SetExpressionWithDecimalSeparatorInformation(yExp);
		wxString y = mp.GetExpression();
		newCoordinates.push_back(std::pair<wxString, wxString>(x, y));
	}

	// É necessário usar os acessores para atualizar diretamente o atributo gs
	if (plane == XY) {
		SetCutAtZ(cutAt);
	} else if (plane == YZ) {
		SetCutAtX(cutAt);
	} else if (plane == ZX) {
		SetCutAtY(cutAt);
	}
	SetCoordinates(newCoordinates);
}

