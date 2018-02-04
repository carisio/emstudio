/*
 * ExcitationMEEditor.cpp
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#include "ExcitationMEEditor.h"

ExcitationMEEditor::ExcitationMEEditor()
	: excitation() {
}

ExcitationMEEditor::~ExcitationMEEditor() {
}


void ExcitationMEEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, excitation.GetType(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void ExcitationMEEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	excitation = *(static_cast<ExcitationME*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool ExcitationMEEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	ExcitationMEFrame dialog;
	dialog.SetExcitationME(excitation);
	if (dialog.ShowModal() == wxID_OK) {
		excitation = dialog.GetExcitationME();

		return true;
	}
	return false;
}

void ExcitationMEEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &excitation);
}

void ExcitationMEEditor::Reset() {

}

wxString ExcitationMEEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* ExcitationMEEditor::Clone() const {
	ExcitationMEEditor* clone = new ExcitationMEEditor;

	return clone;
}
