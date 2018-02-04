/*
 * SheetEditor.cpp
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#include "SheetEditor.h"

SheetEditor::SheetEditor() {

}

SheetEditor::~SheetEditor() {
}

void SheetEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	cout << "INICIO SheetEditor::Create" << endl;
	SetControl(new wxTextCtrl(parent, id, sheet.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
	cout << "FIM SheetEditor::Create" << endl;
}

void SheetEditor::BeginEdit(int row, int col, wxGrid *grid) {
	cout << "INICIO SheetEditor::BeginEdit" << endl;
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	sheet = *(static_cast<Sheet*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
	cout << "FIM SheetEditor::BeginEdit" << endl;
}

bool SheetEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	cout << "FIM SheetEditor::EndEdit" << endl;
	SheetFrame dialog;
	dialog.SetSheet(sheet);
	if (dialog.ShowModal() == wxID_OK) {
		sheet = dialog.GetSheet();

		return true;
	}
	return false;
	cout << "FIM SheetEditor::EndEdit" << endl;
}

void SheetEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &sheet);
}

void SheetEditor::Reset() {

}

wxString SheetEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* SheetEditor::Clone() const {
	SheetEditor* clone = new SheetEditor;

	return clone;
}
