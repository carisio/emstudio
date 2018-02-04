/*
 * ABCEditor.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "ABCEditor.h"

ABCEditor::ABCEditor() {

}

ABCEditor::~ABCEditor() {

}


void ABCEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, abc.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void ABCEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	abc = *(static_cast<AbsorvingBoundaryCondition*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool ABCEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	ABCFrame dialog;
	dialog.SetABC(abc);
	if (dialog.ShowModal() == wxID_OK) {
		abc = dialog.GetABC();

		return true;
	}
	return false;
}

void ABCEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &abc);
}

void ABCEditor::Reset() {

}

wxString ABCEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* ABCEditor::Clone() const {
	ABCEditor* clone = new ABCEditor;

	return clone;
}
