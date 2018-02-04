/*
 * GenericSheetEditor.cpp
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetEditor.h"

GenericSheetEditor::GenericSheetEditor() {

}

GenericSheetEditor::~GenericSheetEditor() {
}

void GenericSheetEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	cout << "INICIO GenericSheetEditor::Create" << endl;
	SetControl(new wxTextCtrl(parent, id, sheet.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
	cout << "FIM GenericSheetEditor::Create" << endl;
}

void GenericSheetEditor::BeginEdit(int row, int col, wxGrid *grid) {
	cout << "INICIO GenericSheetEditor::BeginEdit" << endl;
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	sheet = *(static_cast<GenericSheet*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
	cout << "FIM GenericSheetEditor::BeginEdit" << endl;
}

bool GenericSheetEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	cout << "FIM GenericSheetEditor::EndEdit" << endl;
	GenericSheetFrame dialog;
	dialog.SetGenericSheet(sheet);
	if (dialog.ShowModal() == wxID_OK) {
		sheet = dialog.GetGenericSheet();

		return true;
	}
	return false;
	cout << "FIM GenericSheetEditor::EndEdit" << endl;
}

void GenericSheetEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &sheet);
}

void GenericSheetEditor::Reset() {

}

wxString GenericSheetEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* GenericSheetEditor::Clone() const {
	GenericSheetEditor* clone = new GenericSheetEditor;

	return clone;
}
