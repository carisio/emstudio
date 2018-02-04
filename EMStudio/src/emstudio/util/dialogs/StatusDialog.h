/*
 * StatusDialog.h
 *
 *  Created on: 07/05/2013
 *      Author: leandrocarisio
 */

#ifndef STATUSDIALOG_H_
#define STATUSDIALOG_H_

#include "wx/wx.h"
#include "wx/dialog.h"

class StatusDialog : public wxDialog {
private:
	wxStaticText* lblStatus;
	wxStaticText* lblStatus2;
	wxTimer timer;
	int seconds;
	void OnTimerTick(wxTimerEvent& event);

public:
	StatusDialog(wxString title, bool showTimer = true);
	virtual ~StatusDialog();

	void SetStatus(wxString status);
};

#endif /* STATUSDIALOG_H_ */
