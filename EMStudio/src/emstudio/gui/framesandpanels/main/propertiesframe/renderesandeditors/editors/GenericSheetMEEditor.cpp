/*
 * GenericSheetMEEditor.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetMEEditor.h"

GenericSheetMEEditor::GenericSheetMEEditor() {

}

GenericSheetMEEditor::~GenericSheetMEEditor() {
}


void GenericSheetMEEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, sheet.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void GenericSheetMEEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	sheet = *(static_cast<GenericSheetME*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool GenericSheetMEEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	GenericSheetMEFrame dialog;
	dialog.SetGenericSheetME(sheet);
	if (dialog.ShowModal() == wxID_OK) {
		sheet = dialog.GetGenericSheetME();

		return true;
	}
	return false;
}

void GenericSheetMEEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &sheet);
}

void GenericSheetMEEditor::Reset() {

}

wxString GenericSheetMEEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* GenericSheetMEEditor::Clone() const {
	GenericSheetMEEditor* clone = new GenericSheetMEEditor;

	return clone;
}
