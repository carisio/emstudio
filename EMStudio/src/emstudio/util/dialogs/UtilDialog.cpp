/*
 * UtilDialog.cpp
 *
 *  Created on: 28/09/2011
 *      Author: Leandro
 */

#include "UtilDialog.h"

UtilDialog::UtilDialog() {

}

UtilDialog::~UtilDialog() {

}

void UtilDialog::ShowErrorMessage(wxString msg, wxString title) {
	wxMessageDialog msgError(NULL, msg, title, wxICON_ERROR|wxOK);
	msgError.ShowModal();
}

void UtilDialog::ShowInfoMessage(wxString msg, wxString title) {
	wxMessageDialog msgError(NULL, msg, title, wxICON_INFORMATION|wxOK);
	msgError.ShowModal();
}

int UtilDialog::ShowYesNoCancelMessage(wxString title, wxString msg, wxString yesLabel, wxString noLabel) {
	 wxMessageDialog msgDialog(NULL, msg, title, wxYES_DEFAULT|wxYES_NO|wxCANCEL|wxICON_QUESTION);
	 msgDialog.SetYesNoLabels(yesLabel, noLabel);
	 return msgDialog.ShowModal();
}
int UtilDialog::ShowYesNoCancelMessage(wxString title, wxString msg) {
	 return wxMessageBox(msg, title, wxYES_DEFAULT|wxYES_NO|wxCANCEL|wxICON_QUESTION);
//	 return msgDialog.ShowModal();
}
int UtilDialog::ShowYesNoMessage(wxString title, wxString msg, wxString yesLabel, wxString noLabel) {
	wxMessageDialog msgDialog(NULL, msg, title, wxYES_DEFAULT|wxYES_NO|wxICON_QUESTION);
	msgDialog.SetYesNoLabels(yesLabel, noLabel);
	return msgDialog.ShowModal();
}
int UtilDialog::ShowYesNoMessage(wxString title, wxString msg) {
	wxMessageDialog msgDialog(NULL, msg, title, wxYES_DEFAULT|wxYES_NO|wxICON_QUESTION);
	return msgDialog.ShowModal();
}
