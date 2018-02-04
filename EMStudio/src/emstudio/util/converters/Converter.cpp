/*
 * Converter.cpp
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#include "Converter.h"
#include <stdlib.h>
#include <locale.h>

#define white_space(c) ((c) == ' ' || (c) == '\t')
#define valid_digit(c) ((c) >= '0' && (c) <= '9')
#define valid_digit_signal(c) ((c) == '-' || (c) == '+' || ((c) >= '0' && (c) <= '9'))

Converter::Converter() {

}

Converter::~Converter() {

}

double Converter::FormattedStringToDouble(wxString s) {
	double val = 0;
	s.ToDouble(&val);
	return val;
}

float Converter::FormattedStringToFloat(wxString s) {
	double val = 0;
	s.ToDouble(&val);
	return (float)val;
}

int Converter::FormattedStringToInt(wxString s) {
	long val = 0;
	s.ToLong(&val);
	return (int)val;
}
long Converter::FormattedStringToLong(wxString s) {
	long val = 0;
	s.ToLong(&val);
	return val;
}
bool Converter::FormattedStringToBool(wxString s) {
	if (s == "true")
		return true;
	else
		return false;
}
wxString Converter::DoubleToString(double& d) {
	return wxString::FromCDouble(d);
}
wxString Converter::DoubleToScientificNotationString(double d, int precision) {
	wxString fmt("%.");
	fmt.Append(Converter::IntToFormattedString(precision)).Append("e");
	return wxString::Format(fmt, d);
}
wxString Converter::DoubleToScientificNotationString(double d) {
	return wxString::Format("%e", d);
}
wxString Converter::DoubleToFormattedString(double d, int precision) {
	return wxString::FromDouble(d, precision);
}
wxString Converter::DoubleToFormattedString_MaxPrecision(double d) {
	// Converte um número para a maior quantidade de casas decimais possível.
	// Por exemplo: 1.2354848 vai transformá-lo em "1.23548480000000000000"
	wxString s = wxString::FromDouble(d, std::numeric_limits<double>::digits10);
	// Corta os zeros a direita da casa decimal
	s = s.Mid(0, 1+s.find_last_not_of('0', s.length()));
	// Verifica se o último caracter é numérico. Se não for, é uma casa decimal. Exclui (dependendo do locate, a casa decimal pode ter vários caracteres).
	char lastDigit = s.Last();
	while (!(lastDigit >= '0' && lastDigit <= '9')) {
		s = s.Mid(0, s.length() - 1);
		lastDigit = s.Last();
	}
	return s;
}
wxString Converter::FloatToFormattedString(float f, int precision) {
	return wxString::FromDouble(f, precision);
}
wxString Converter::LongToFormattedString(long l) {
	stringstream ss;
	ss << setprecision(std::numeric_limits<long>::digits10) << l;
	return ss.str();

}
wxString Converter::IntToFormattedString(int i) {
	stringstream ss;
	ss << setprecision(std::numeric_limits<int>::digits10) << i;
	return ss.str();
}
wxString Converter::BoolToFormattedString(bool b) {
	if (b)
		return Converter::GetTrueString();
	else
		return Converter::GetFalseString();
}

wxString Converter::GetTrueString() {
	return "true";
}

wxString Converter::GetFalseString() {
	return "false";
}

wxString Converter::StringToXMLString(wxString s) {
	wxString ss = s;
	ss.Replace("&", "&amp;", true);
	ss.Replace("<", "&lt;", true);
	ss.Replace(">", "&gt;", true);
	ss.Replace("'", "&apos;", true);
	ss.Replace("\"", "&quot;", true);
	return ss;
}

wxString Converter::XMLStringToString(wxString s) {
	wxString ss = s;
	ss.Replace("&amp;", "&", true);
	ss.Replace("&lt;", "<", true);
	ss.Replace("&gt;", ">", true);
	ss.Replace("&apos;", "'", true);
	ss.Replace("&quot;", "\"", true);
	return ss;
}
