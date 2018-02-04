/*
 * Converter.h
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "wx/wx.h"
#include <sstream>
#include <limits>
#include <iomanip>
#include "emstudio/util/tnt/tnt.h"
#include <vector>
using namespace::TNT;
using namespace::std;

class Converter {
public:
	Converter();
	virtual ~Converter();

	static wxString StringToXMLString(wxString s);
	static wxString XMLStringToString(wxString s);

	static double FormattedStringToDouble(wxString s);
	static float FormattedStringToFloat(wxString s);
	static int FormattedStringToInt(wxString s);
	static long FormattedStringToLong(wxString s);
	static bool FormattedStringToBool(wxString s);

	static wxString DoubleToString(double& d);
	static wxString DoubleToScientificNotationString(double d, int precision);
	static wxString DoubleToScientificNotationString(double d);
	static wxString DoubleToFormattedString(double d, int precision = 5);
	static wxString DoubleToFormattedString_MaxPrecision(double d);
	static wxString FloatToFormattedString(float f, int precision = 5);
	static wxString BoolToFormattedString(bool b);
	static wxString IntToFormattedString(int i);
	static wxString LongToFormattedString(long l);
	static wxString GetFalseString();
	static wxString GetTrueString();

};

#endif /* CONVERTER_H_ */
