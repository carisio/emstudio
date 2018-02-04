/*
 * GenericPECSheetDTO.cpp
 *
 *  Created on: 16/04/2013
 *      Author: Leandro
 */

#include "GenericPECSheetDTO.h"

GenericPECSheetDTO::GenericPECSheetDTO() {

}

GenericPECSheetDTO::~GenericPECSheetDTO() {
}

Priority GenericPECSheetDTO::GetPriority() {
	Priority p;
	p.SetValue(MEDIUM);
	return p;
}

wxString GenericPECSheetDTO::GetDTOClassName() {
	return "GenericPECSheetDTO";
}

void GenericPECSheetDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	vector<pair<double, double> > coord = sheet.GetCoordinates();
	vector<pair<double, double> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		pair<double, double> newPair(coord[i].first*space, coord[i].second*space);
		newCoordinates.push_back(newPair);
	}
	sheet.SetCoordinates(newCoordinates);

	if (sheet.IsCutAtX()) {
		sheet.SetCutAtX(sheet.GetCutAt()*space);
	} else if (sheet.IsCutAtY()) {
		sheet.SetCutAtY(sheet.GetCutAt()*space);
	} else if (sheet.IsCutAtZ()) {
		sheet.SetCutAtZ(sheet.GetCutAt()*space);
	}
}

//void GenericPECSheetDTO::SetMatchWithPML(MatchWithPML m) {
//	matchWithPML = m;
//}
//MatchWithPML GenericPECSheetDTO::GetMatchWithPML() {
//	return matchWithPML;
//}

void GenericPECSheetDTO::SetGenericSheet(GenericSheet g) {
	sheet = g;
}
GenericSheet GenericPECSheetDTO::GetGenericSheet() {
	return sheet;
}
