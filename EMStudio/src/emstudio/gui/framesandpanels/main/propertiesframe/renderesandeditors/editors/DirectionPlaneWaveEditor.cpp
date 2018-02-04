/*
 * DirectionPlaneWaveEditor.cpp
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWaveEditor.h"

DirectionPlaneWaveEditor::DirectionPlaneWaveEditor() {

}

DirectionPlaneWaveEditor::~DirectionPlaneWaveEditor() {

}

void DirectionPlaneWaveEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	cout << "INICIO DirectionPlaneWaveEditor::Create" << endl;
	SetControl(new wxTextCtrl(parent, id, direction.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
	cout << "FIM DirectionPlaneWaveEditor::Create" << endl;
}

void DirectionPlaneWaveEditor::BeginEdit(int row, int col, wxGrid *grid) {
	cout << "INICIO DirectionPlaneWaveEditor::BeginEdit" << endl;
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	direction = *(static_cast<DirectionPlaneWave*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
	cout << "FIM DirectionPlaneWaveEditor::BeginEdit" << endl;
}

bool DirectionPlaneWaveEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	cout << "FIM DirectionPlaneWaveEditor::EndEdit" << endl;
	DirectionPlaneWaveFrame dialog;
	dialog.SetDirection(direction);
	if (dialog.ShowModal() == wxID_OK) {
		direction = dialog.GetDirection();

		return true;
	}
	return false;
	cout << "FIM DirectionPlaneWaveEditor::EndEdit" << endl;
}

void DirectionPlaneWaveEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &direction);
}

void DirectionPlaneWaveEditor::Reset() {

}

wxString DirectionPlaneWaveEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* DirectionPlaneWaveEditor::Clone() const {
	DirectionPlaneWaveEditor* clone = new DirectionPlaneWaveEditor;

	return clone;
}
