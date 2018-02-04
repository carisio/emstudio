/*
 * MatchWithPMLEditor.cpp
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#include "MatchWithPMLEditor.h"

MatchWithPMLEditor::MatchWithPMLEditor() {

}

MatchWithPMLEditor::~MatchWithPMLEditor() {
}


void MatchWithPMLEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, matchWithPML.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void MatchWithPMLEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	matchWithPML = *(static_cast<MatchWithPML*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool MatchWithPMLEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	MatchWithPMLFrame dialog;
	dialog.SetMatchWithPML(matchWithPML);
	if (dialog.ShowModal() == wxID_OK) {
		matchWithPML = dialog.GetMatchWithPML();

		return true;
	}
	return false;
}

void MatchWithPMLEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &matchWithPML);
}

void MatchWithPMLEditor::Reset() {

}

wxString MatchWithPMLEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* MatchWithPMLEditor::Clone() const {
	MatchWithPMLEditor* clone = new MatchWithPMLEditor;

	return clone;
}
