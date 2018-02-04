/*
 * MatchWithPMLFrame.cpp
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#include "MatchWithPMLFrame.h"

MatchWithPMLFrame::MatchWithPMLFrame(wxWindow* parent, MatchWithPML m, wxWindowID id, const wxString& title) : wxDialog(parent, id, title), matchWithPML(m) {
	CreateEmptyControlsAndInsert();
	UpdateControlsState();
}

MatchWithPMLFrame::~MatchWithPMLFrame() {
}

bool MatchWithPMLFrame::TransferDataFromWindow() {
	matchWithPML.SetMatchedWithPML(xNeg, chkNegX->GetValue());
	matchWithPML.SetMatchedWithPML(yNeg, chkNegY->GetValue());
	matchWithPML.SetMatchedWithPML(zNeg, chkNegZ->GetValue());
	matchWithPML.SetMatchedWithPML(xPos, chkPosX->GetValue());
	matchWithPML.SetMatchedWithPML(yPos, chkPosY->GetValue());
	matchWithPML.SetMatchedWithPML(zPos, chkPosZ->GetValue());

	return true;
}

MatchWithPML MatchWithPMLFrame::GetMatchWithPML() {
	return matchWithPML;
}

void MatchWithPMLFrame::SetMatchWithPML(MatchWithPML m) {
	matchWithPML.Copy(&m);
	UpdateControlsState();
}

void MatchWithPMLFrame::CreateEmptyControlsAndInsert() {
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(3, 2, 0, 0);
	topGridSizer->AddGrowableCol(0);
	topGridSizer->AddGrowableCol(1);

	chkNegX = new wxCheckBox(this, wxID_ANY, "-X", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
	chkNegY = new wxCheckBox(this, wxID_ANY, "-Y", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
	chkNegZ = new wxCheckBox(this, wxID_ANY, "-Z", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
	chkPosX = new wxCheckBox(this, wxID_ANY, "+X", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
	chkPosY = new wxCheckBox(this, wxID_ANY, "+Y", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
	chkPosZ = new wxCheckBox(this, wxID_ANY, "+Z", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);

	topGridSizer->Add(chkNegX, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(chkPosX, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(chkNegY, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(chkPosY, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(chkNegZ, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(chkPosZ, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	UpdateControlsState();

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	topSizer->Add(topGridSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}


void MatchWithPMLFrame::UpdateControlsState() {
	chkNegX->SetValue(matchWithPML.IsMatchedWithPML(xNeg));
	chkNegY->SetValue(matchWithPML.IsMatchedWithPML(yNeg));
	chkNegZ->SetValue(matchWithPML.IsMatchedWithPML(zNeg));
	chkPosX->SetValue(matchWithPML.IsMatchedWithPML(xPos));
	chkPosY->SetValue(matchWithPML.IsMatchedWithPML(yPos));
	chkPosZ->SetValue(matchWithPML.IsMatchedWithPML(zPos));

	Fit();
}
