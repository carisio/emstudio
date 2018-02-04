/*
 * UnitFrame.cpp
 *
 *  Created on: 23/09/2011
 *      Author: leandrocarisio
 */

#include "UnitFrame.h"

UnitFrame::UnitFrame(wxWindow* parent, UnitsSmartPointer u, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX/*|wxRESIZE_BORDER*/),
	  units(u) {

	CreateAndInsertControls();

}

UnitFrame::~UnitFrame() {
}
void UnitFrame::CreateAndInsertControls() {
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gridSizer = new wxFlexGridSizer(3, 2, 0, 0);
	gridSizer->AddGrowableCol(1);

	wxStaticText* textSpace = new wxStaticText(this, wxID_STATIC, wxT("Space"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	comboSpace = new wxComboBox(this, wxID_ANY,	units->GetUserDefinedSpaceUnit().first, wxDefaultPosition, wxDefaultSize, units->GetLabels(units->GetAvailableSpaceUnits()), wxCB_READONLY);
	gridSizer->Add(textSpace, 0, wxALL | wxALIGN_LEFT, 5);
	gridSizer->Add(comboSpace, 0, wxALL | wxEXPAND | wxALIGN_LEFT, 5);

	wxStaticText* textTime = new wxStaticText(this, wxID_STATIC, wxT("Time"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	comboTime = new wxComboBox(this, wxID_ANY,	units->GetUserDefinedTimeUnit().first, wxDefaultPosition, wxDefaultSize, units->GetLabels(units->GetAvailableTimeUnits()), wxCB_READONLY);
	gridSizer->Add(textTime, 0, wxALL | wxALIGN_LEFT, 5);
	gridSizer->Add(comboTime, 0, wxALL | wxEXPAND | wxALIGN_LEFT, 5);

	wxStaticText* textFrequency = new wxStaticText(this, wxID_STATIC, wxT("Frequency"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	comboFrequency = new wxComboBox(this, wxID_ANY,	units->GetUserDefinedFrequencyUnit().first, wxDefaultPosition, wxDefaultSize, units->GetLabels(units->GetAvailableFrequencyUnits()), wxCB_READONLY);
	gridSizer->Add(textFrequency, 0, wxALL | wxALIGN_LEFT, 5);
	gridSizer->Add(comboFrequency, 0, wxALL | wxEXPAND | wxALIGN_LEFT, 5);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	topSizer->Add(gridSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}

bool UnitFrame::TransferDataFromWindow() {
	units->SetUserDefinedSpaceUnit(comboSpace->GetStringSelection());
	units->SetUserDefinedTimeUnit(comboTime->GetStringSelection());
	units->SetUserDefinedFrequencyUnit(comboFrequency->GetStringSelection());

	return true;
}
