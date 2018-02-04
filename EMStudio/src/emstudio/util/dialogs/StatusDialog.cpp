/*
 * StatusDialog.cpp
 *
 *  Created on: 07/05/2013
 *      Author: leandrocarisio
 */

#include "StatusDialog.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/sizer.h"
#include <iostream>
using namespace::std;

StatusDialog::StatusDialog(wxString title, bool showTimer)
	: wxDialog(0, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU/*|wxRESIZE_BORDER*/) ,
	  seconds(0) {
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	lblStatus = new wxStaticText(this, wxID_STATIC, wxT(".................................."), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblStatus2 = new wxStaticText(this, wxID_STATIC,  wxT("This process might take several seconds. Please wait."), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

	if (showTimer) {
		timer.SetOwner(this);
		Connect(timer.GetId(), wxEVT_TIMER, wxTimerEventHandler(StatusDialog::OnTimerTick), NULL, this);
		timer.Start(10, false);
	}
	sizer->Add(lblStatus, 0, wxALL | wxALIGN_LEFT | wxEXPAND , 5);
	sizer->Add(lblStatus2, 0, wxALL | wxALIGN_LEFT | wxEXPAND , 5);

	SetSizer(sizer);
	sizer->Fit(this);
	sizer->SetSizeHints(this);
	Show();
}

StatusDialog::~StatusDialog() {

}

void StatusDialog::SetStatus(wxString status) {
	lblStatus->SetLabel(status);
	lblStatus2->SetLabel(lblStatus2->GetLabel());
	GetSizer()->Layout();
}

void StatusDialog::OnTimerTick(wxTimerEvent& event) {
//	seconds++;
//	wxString t = Converter::IntToFormattedString(seconds);
//	t.Append(" seconds");
//	lblStatus2->SetLabel(t);
//	lblStatus2->Refresh(true);
//	lblStatus2->Update();
	cout << "OnTimerTick = " << seconds << endl;
}
