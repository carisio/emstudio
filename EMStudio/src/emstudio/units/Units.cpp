/*
 * Units.cpp
 *
 *  Created on: 23/09/2011
 *      Author: leandrocarisio
 */

#include "Units.h"

Units::Units() {
	InitializeUnits();
}

Units::~Units() {

}

pair<wxString, double> Units::GetUserDefinedSpaceUnit() {
	return spaceUnitChoosen;
}
pair<wxString, double> Units::GetUserDefinedTimeUnit() {
	return timeUnitChoosen;
}
pair<wxString, double> Units::GetUserDefinedFrequencyUnit() {
	return frequencyUnitChoosen;
}

void Units::SetUserDefinedSpaceUnit(pair<wxString, double> unit) {
	spaceUnitChoosen = unit;
}
void Units::SetUserDefinedTimeUnit(pair<wxString, double> unit) {
	timeUnitChoosen = unit;
}
void Units::SetUserDefinedFrequencyUnit(pair<wxString, double> unit) {
	frequencyUnitChoosen = unit;
}
void Units::SetUserDefinedSpaceUnit(wxString label) {
	SetUserDefinedSpaceUnit(GetPair(GetAvailableSpaceUnits(), label));
}
void Units::SetUserDefinedTimeUnit(wxString label) {
	SetUserDefinedTimeUnit(GetPair(GetAvailableTimeUnits(), label));
}
void Units::SetUserDefinedFrequencyUnit(wxString label) {
	SetUserDefinedFrequencyUnit(GetPair(GetAvailableFrequencyUnits(), label));
}

list< pair<wxString, double> > Units::GetAvailableSpaceUnits() {
	return spaceUnits;
}
list< pair<wxString, double> > Units::GetAvailableTimeUnits() {
	return timeUnits;
}
list< pair<wxString, double> > Units::GetAvailableFrequencyUnits() {
	return frequencyUnits;
}

void Units::InitializeUnits() {
	spaceUnits = list< pair<wxString, double> >();
	spaceUnits.push_back( pair<wxString, double>(wxT("nm"), 1e-9) );
	spaceUnits.push_back( pair<wxString, double>(wxT("um"), 1e-6) );
	spaceUnits.push_back( pair<wxString, double>(wxT("mil"), 0.0254/1000) );
	spaceUnits.push_back( pair<wxString, double>(wxT("mm"), 1e-3) );
	spaceUnits.push_back( pair<wxString, double>(wxT("cm"), 1e-2) );
	spaceUnits.push_back( pair<wxString, double>(wxT("in"), 0.0254) );
	spaceUnits.push_back( pair<wxString, double>(wxT("ft"), 0.304799 ) );
	spaceUnits.push_back( pair<wxString, double>(wxT("yd"), 0.914399 ) );
	spaceUnits.push_back( pair<wxString, double>(wxT("m"), 1) );
	spaceUnits.push_back( pair<wxString, double>(wxT("km"), 1e3) );

	timeUnits = list< pair<wxString, double> >();
	timeUnits.push_back( pair<wxString, double>(wxT("ps"), 1e-12) );
	timeUnits.push_back( pair<wxString, double>(wxT("ns"), 1e-9) );
	timeUnits.push_back( pair<wxString, double>(wxT("us"), 1e-6) );
	timeUnits.push_back( pair<wxString, double>(wxT("ms"), 1e-3) );
	timeUnits.push_back( pair<wxString, double>(wxT("s"), 1) );

	frequencyUnits = list< pair<wxString, double> >();
	frequencyUnits.push_back( pair<wxString, double>(wxT("Hz"), 1) );
	frequencyUnits.push_back( pair<wxString, double>(wxT("kHz"), 1e3) );
	frequencyUnits.push_back( pair<wxString, double>(wxT("MHz"), 1e6) );
	frequencyUnits.push_back( pair<wxString, double>(wxT("GHz"), 1e9) );
	frequencyUnits.push_back( pair<wxString, double>(wxT("THz"), 1e12) );

	SetDefaultUnits();
}

void Units::SetDefaultUnits() {
//	SetUserDefinedSpaceUnit(pair<wxString, double>(wxT("mm"), 1e-3));
//	SetUserDefinedTimeUnit(pair<wxString, double>(wxT("ps"), 1e-9));
//	SetUserDefinedFrequencyUnit(pair<wxString, double>(wxT("GHz"), 1e9));
	SetUserDefinedSpaceUnit("mm");
	SetUserDefinedTimeUnit("ps");
	SetUserDefinedFrequencyUnit("GHz");

}

wxArrayString Units::GetLabels(list<pair<wxString, double> > llist) {
	wxArrayString labels;
	list<pair<wxString, double> >::iterator iterator = llist.begin();
	while (iterator != llist.end()) {
		labels.Add(iterator->first);
		iterator++;
	}

	return labels;
}

pair<wxString, double> Units::GetPair(list<pair<wxString, double> > llist, wxString label) {
	list<pair<wxString, double> >::iterator iterator = llist.begin();
	while (iterator != llist.end()) {
		if (iterator->first == label)
			return *iterator;
		iterator++;
	}
	return pair<wxString, double>();
}
