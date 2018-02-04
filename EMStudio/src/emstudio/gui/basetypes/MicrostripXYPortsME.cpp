/*
 * MicrostripXYPortsME.cpp
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#include "MicrostripXYPortsME.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"
#include <iostream>

MicrostripXYPortsME::MicrostripXYPortsME() : coordinates() {
	SetWriteVersion(1);
}

MicrostripXYPortsME::~MicrostripXYPortsME() {
}

std::vector<std::pair<wxString, wxString> > MicrostripXYPortsME::GetCoordinates() {
	return coordinates;
}
void MicrostripXYPortsME::SetCoordinates(std::vector<std::pair<wxString, wxString> > coor) {
	coordinates = coor;
}
void MicrostripXYPortsME::Copy(BaseType* p) {
	MicrostripXYPortsME* pMicrostripXYPortsME = static_cast<MicrostripXYPortsME*>(p);

	SetCoordinates(pMicrostripXYPortsME->GetCoordinates());
}
wxString MicrostripXYPortsME::GetBaseTypeClassName() {
	return "MicrostripXYPortsME";
}

wxString MicrostripXYPortsME::GetUserFriendlyStringRepresentation() {
	if (!IsPortsValid()) {
		return "Invalid expression";
	}

	wxString result;
	result.Append(Converter::IntToFormattedString(coordinates.size()));
	if (coordinates.size() > 1)
		result.Append(" ports");
	else
		result.Append(" port");

	return result;
}
bool MicrostripXYPortsME::IsPortsValid() {
	bool result = true;

	MathParser p;

	for (size_t i = 0; i < coordinates.size() && result; i++) {
		p.SetExpression(coordinates[i].first);
		result = result && p.DefineConstantsAndCheckIfIsValid();
		p.SetExpression(coordinates[i].second);
		result = result && p.DefineConstantsAndCheckIfIsValid();
	}

	return result;
}
MicrostripXYPorts MicrostripXYPortsME::ConvertToMicrostripXYPorts() {
	MicrostripXYPorts microStripXYPorts;

	// Atualiza também microStripXYPorts
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
	microStripXYPorts.SetCoordinates(coord);

	return microStripXYPorts;
}
void MicrostripXYPortsME::SetUserFriendlyStringRepresentation(wxString str) {

}
void MicrostripXYPortsME::DoWrite(OutputBuffer& buffer) {
	MathParser mp;

	// Coordinates size
	int size = coordinates.size();
	buffer.WriteInt(size);
	// Coordinates
	std::vector<std::pair<wxString, wxString> >::iterator it = coordinates.begin();
	std::vector<std::pair<wxString, wxString> >::iterator end = coordinates.end();

	while(it != end) {
		mp.SetExpression(it->first);
		wxString expWithDecPtInfo = mp.GetExpressionWithDecimalSeparatorInformation();
		buffer.WriteString(expWithDecPtInfo);
		mp.SetExpression(it->second);
		expWithDecPtInfo = mp.GetExpressionWithDecimalSeparatorInformation();
		buffer.WriteString(expWithDecPtInfo);
		it++;
	}
}
void MicrostripXYPortsME::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	MathParser mp;

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

	// É necessário usar os acessores para atualizar diretamente o atributo microstripXYPorts
	SetCoordinates(newCoordinates);
}

