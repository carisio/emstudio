/*
 * MicrostripXYPortMEEditor.cpp
 *
 *  Created on: 06/12/2013
 *      Author: leandrocarisio
 */

#include "MicrostripXYPortsMEEditor.h"

MicrostripXYPortsMEEditor::MicrostripXYPortsMEEditor() {

}

MicrostripXYPortsMEEditor::~MicrostripXYPortsMEEditor() {
}


void MicrostripXYPortsMEEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, ports.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void MicrostripXYPortsMEEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	ports = *(static_cast<MicrostripXYPortsME*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool MicrostripXYPortsMEEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	MicrostripXYPortsMEFrame dialog;
	dialog.SetMicrostripXYPortsME(ports);
	if (dialog.ShowModal() == wxID_OK) {
		ports = dialog.GetMicrostripXYPortsME();

		return true;
	}
	return false;
}

void MicrostripXYPortsMEEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &ports);
}

void MicrostripXYPortsMEEditor::Reset() {

}

wxString MicrostripXYPortsMEEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* MicrostripXYPortsMEEditor::Clone() const {
	MicrostripXYPortsMEEditor* clone = new MicrostripXYPortsMEEditor;

	return clone;
}
