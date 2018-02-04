/*
 * UtilDialog.h
 *
 *  Created on: 28/09/2011
 *      Author: Leandro
 */

#ifndef UTILDIALOG_H_
#define UTILDIALOG_H_

#include "wx/wx.h"
#include "wx/msgdlg.h"

class UtilDialog {
public:
	UtilDialog();
	virtual ~UtilDialog();

	static int ShowYesNoMessage(wxString title, wxString msg);
	static int ShowYesNoMessage(wxString title, wxString msg, wxString yesLabel, wxString noLabel);
	static int ShowYesNoCancelMessage(wxString title, wxString msg);
	static int ShowYesNoCancelMessage(wxString title, wxString msg, wxString yesLabel, wxString noLabel);
	static void ShowErrorMessage(wxString msg, wxString title = wxT("Error"));
	static void ShowInfoMessage(wxString msg, wxString title = wxT("Info"));

};

#endif /* UTILDIALOG_H_ */
