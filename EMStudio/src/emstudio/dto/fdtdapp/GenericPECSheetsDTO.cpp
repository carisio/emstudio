/*
 * GenericPECSheetsDTO.cpp
 *
 *  Created on: 16/12/2013
 *      Author: leandrocarisio
 */

#include "GenericPECSheetsDTO.h"

GenericPECSheetsDTO::GenericPECSheetsDTO() {

}

GenericPECSheetsDTO::~GenericPECSheetsDTO() {
}

Priority GenericPECSheetsDTO::GetPriority() {
	Priority p;
	p.SetValue(MEDIUM);
	return p;
}

wxString GenericPECSheetsDTO::GetDTOClassName() {
	return "GenericPECSheetsDTO";
}

void GenericPECSheetsDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	std::vector<GenericSheet> newSheets;

	for (size_t i = 0; i < sheets.size(); i++) {
		GenericSheet sheet = sheets[i];
		std::vector<pair<double, double> > coord = sheet.GetCoordinates();
		std::vector<pair<double, double> > newCoordinates;

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
		newSheets.push_back(sheet);
	}
	SetGenericSheets(newSheets);
}

void GenericPECSheetsDTO::SetGenericSheets(std::vector<GenericSheet> s) {
	sheets = s;
}
std::vector<GenericSheet> GenericPECSheetsDTO::GetGenericSheets() {
	return sheets;
}
