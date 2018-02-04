/*
 * RectangularTubeGeometryMEEditor.cpp
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#include "RectangularTubeGeometryMEEditor.h"

RectangularTubeGeometryMEEditor::RectangularTubeGeometryMEEditor() {

}

RectangularTubeGeometryMEEditor::~RectangularTubeGeometryMEEditor() {
}

void RectangularTubeGeometryMEEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, geometry.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void RectangularTubeGeometryMEEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	geometry = *(static_cast<RectangularTubeGeometryME*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool RectangularTubeGeometryMEEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	RectangularTubeGeometryMEFrame dialog;
	dialog.SetRectangularTubeGeometryME(geometry);
	if (dialog.ShowModal() == wxID_OK) {
		geometry = dialog.GetRectangularTubeGeometryME();

		return true;
	}
	return false;
}

void RectangularTubeGeometryMEEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &geometry);
}

void RectangularTubeGeometryMEEditor::Reset() {

}

wxString RectangularTubeGeometryMEEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* RectangularTubeGeometryMEEditor::Clone() const {
	RectangularTubeGeometryMEEditor* clone = new RectangularTubeGeometryMEEditor;

	return clone;
}
