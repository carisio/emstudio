/*
 * UtilControls.h
 *
 *  Created on: 11/03/2013
 *      Author: leandrocarisio
 */

#ifndef UTILCONTROLS_H_
#define UTILCONTROLS_H_

#include "wx/wx.h"
#include "wx/valnum.h"
#include "wx/event.h"

class UtilControls {
public:
	UtilControls();
	virtual ~UtilControls();

	static wxTextCtrl* NewTextCtrlForMathExpression(wxWindow* parent = NULL, wxWindowID id = wxID_ANY,
			wxString value = wxEmptyString, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize,
			long style = wxTE_PROCESS_ENTER | wxTE_RICH2);

	static wxTextCtrl* NewTextCtrlWithDoubleValidator(wxWindow* parent = NULL, wxWindowID id = wxID_ANY,
			wxString value = wxEmptyString, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize,
			long style = wxTE_PROCESS_ENTER | wxTE_RICH2);

	static wxTextCtrl* NewTextCtrlWithIntValidator(wxWindow* parent = NULL, wxWindowID id = wxID_ANY,
			wxString value = wxEmptyString, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize,
			long style = wxTE_PROCESS_ENTER | wxTE_RICH2);

	static wxTextCtrl* NewTextCtrlWithIntIntervalValidator(wxWindow* parent = NULL, int min = 0, int max = 100, wxWindowID id = wxID_ANY,
				wxString value = wxEmptyString, wxPoint position = wxDefaultPosition, wxSize size = wxDefaultSize,
				long style = wxTE_PROCESS_ENTER | wxTE_RICH2);
};

#endif /* UTILCONTROLS_H_ */
