/*
 * UtilControls.cpp
 *
 *  Created on: 11/03/2013
 *      Author: leandrocarisio
 */

#include "UtilControls.h"



UtilControls::UtilControls() {

}

UtilControls::~UtilControls() {

}
/*
 * No caso do text control para expressões, não há nenhum validador.
 */
wxTextCtrl* UtilControls::NewTextCtrlForMathExpression(wxWindow* parent, wxWindowID id, wxString value, wxPoint position, wxSize size, long style) {
	return new wxTextCtrl(parent, id, value, position, size, style);
}

wxTextCtrl* UtilControls::NewTextCtrlWithDoubleValidator(wxWindow* parent, wxWindowID id, wxString value, wxPoint position, wxSize size, long style) {
	wxFloatingPointValidator<double> validatorDoubleTextControl(10, 0, wxNUM_VAL_NO_TRAILING_ZEROES);
	return new wxTextCtrl(parent, id, value, position, size, style, validatorDoubleTextControl);
}

wxTextCtrl* UtilControls::NewTextCtrlWithIntValidator(wxWindow* parent, wxWindowID id, wxString value, wxPoint position, wxSize size, long style) {
	wxIntegerValidator<int> validator(0, wxNUM_VAL_ZERO_AS_BLANK);
	return new wxTextCtrl(parent, id, value, position, size, style, validator);
}

wxTextCtrl* UtilControls::NewTextCtrlWithIntIntervalValidator(wxWindow* parent, int min, int max, wxWindowID id, wxString value, wxPoint position, wxSize size, long style) {
	wxIntegerValidator<int> validator(0, wxNUM_VAL_ZERO_AS_BLANK);
	validator.SetMin(min); validator.SetMax(max);
	return new wxTextCtrl(parent, id, value, position, size, style, validator);
}
