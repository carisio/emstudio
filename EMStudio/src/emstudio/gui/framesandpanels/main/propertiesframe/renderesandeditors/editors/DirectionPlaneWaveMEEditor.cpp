/*
 * DirectionPlaneWaveMEEditor.cpp
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWaveMEEditor.h"

DirectionPlaneWaveMEEditor::DirectionPlaneWaveMEEditor() {

}

DirectionPlaneWaveMEEditor::~DirectionPlaneWaveMEEditor() {
}

void DirectionPlaneWaveMEEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	cout << "INICIO DirectionPlaneWaveMEEditor::Create" << endl;
	SetControl(new wxTextCtrl(parent, id, direction.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
	cout << "FIM DirectionPlaneWaveMEEditor::Create" << endl;
}

void DirectionPlaneWaveMEEditor::BeginEdit(int row, int col, wxGrid *grid) {
	cout << "INICIO DirectionPlaneWaveMEEditor::BeginEdit" << endl;
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	direction = *(static_cast<DirectionPlaneWaveME*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
	cout << "FIM DirectionPlaneWaveMEEditor::BeginEdit" << endl;
}

bool DirectionPlaneWaveMEEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	cout << "FIM DirectionPlaneWaveMEEditor::EndEdit" << endl;
	DirectionPlaneWaveMEFrame dialog;
	dialog.SetDirection(direction);
	if (dialog.ShowModal() == wxID_OK) {
		direction = dialog.GetDirection();

		return true;
	}
	return false;
	cout << "FIM DirectionPlaneWaveMEEditor::EndEdit" << endl;
}

void DirectionPlaneWaveMEEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &direction);
}

void DirectionPlaneWaveMEEditor::Reset() {

}

wxString DirectionPlaneWaveMEEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* DirectionPlaneWaveMEEditor::Clone() const {
	DirectionPlaneWaveMEEditor* clone = new DirectionPlaneWaveMEEditor;

	return clone;
}
