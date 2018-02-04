/*
 * Units.h
 *
 *  Created on: 23/09/2011
 *      Author: leandrocarisio
 */

#ifndef UNITS_H_
#define UNITS_H_

#include <list>
#include <tr1/memory>
#include "wx/wx.h"
#include "wx/arrstr.h"
using namespace::std;

class Units;
typedef std::tr1::shared_ptr<Units> UnitsSmartPointer;

class Units {
private:
	list< pair<wxString, double> > spaceUnits;
	list< pair<wxString, double> > timeUnits;
	list< pair<wxString, double> > frequencyUnits;

	pair<wxString, double> spaceUnitChoosen;
	pair<wxString, double> timeUnitChoosen;
	pair<wxString, double> frequencyUnitChoosen;

public:
	Units();

	pair<wxString, double> GetUserDefinedSpaceUnit();
	pair<wxString, double> GetUserDefinedTimeUnit();
	pair<wxString, double> GetUserDefinedFrequencyUnit();

	void SetUserDefinedSpaceUnit(pair<wxString, double>);
	void SetUserDefinedTimeUnit(pair<wxString, double>);
	void SetUserDefinedFrequencyUnit(pair<wxString, double>);
	void SetUserDefinedSpaceUnit(wxString);
	void SetUserDefinedTimeUnit(wxString);
	void SetUserDefinedFrequencyUnit(wxString);

	list< pair<wxString, double> > GetAvailableSpaceUnits();
	list< pair<wxString, double> > GetAvailableTimeUnits();
	list< pair<wxString, double> > GetAvailableFrequencyUnits();

	void SetDefaultUnits();

	wxArrayString GetLabels(list<pair<wxString, double> >);
	pair<wxString, double> GetPair(list<pair<wxString, double> > llist, wxString label);

	void InitializeUnits();

	virtual ~Units();
};

#endif /* UNITS_H_ */
