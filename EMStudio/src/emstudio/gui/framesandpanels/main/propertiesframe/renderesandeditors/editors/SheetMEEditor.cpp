/*
 * SheetMEEditor.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "SheetMEEditor.h"

SheetMEEditor::SheetMEEditor() {

}

SheetMEEditor::~SheetMEEditor() {
}

void SheetMEEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, sheet.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void SheetMEEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	sheet = *(static_cast<SheetME*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool SheetMEEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	SheetMEFrame dialog;
	dialog.SetSheetME(sheet);
	if (dialog.ShowModal() == wxID_OK) {
		sheet = dialog.GetSheetME();

		return true;
	}
	return false;
}

void SheetMEEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &sheet);
}

void SheetMEEditor::Reset() {

}

wxString SheetMEEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* SheetMEEditor::Clone() const {
	SheetMEEditor* clone = new SheetMEEditor;

	return clone;
}
