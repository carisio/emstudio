/*
 * Excitation.h
 *
 *  Created on: 03/10/2011
 *      Author: leandrocarisio
 */

#ifndef EXCITATION_H_
#define EXCITATION_H_

#include <vector>

#include "wx/wx.h"
#include "wx/arrstr.h"
#include "wx/tokenzr.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/units/Units.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/muparser/MathParser.h"

class Excitation {
private:
	wxArrayString types;
	wxString type;
	std::vector< std::pair<wxString, double> > parameters;
	MathParser genericExcitation;

public:
	Excitation();

//	void SetValue(Excitation e);
	void SetType(wxString type);
	void SetExpressionForGenericExcitation(wxString s);

	wxString GetType();
	wxArrayString GetTypes();
	int GetNumberOfParameters();
	std::vector<std::pair<wxString,double> > GetParameters();
//	void SetParameter(int parameterNumber, std::pair<wxString, double> parameter);
	void SetParameter(int parameterNumber, double parameter);
	std::pair<wxString, double> GetParameter(int parameterNumber);
	double GetMaximumFrequency();

	double GetExcitationValue(double t);
	void Unnormalize(Units units);
	void Init();

	virtual ~Excitation();
};

#endif /* EXCITATION_H_ */
