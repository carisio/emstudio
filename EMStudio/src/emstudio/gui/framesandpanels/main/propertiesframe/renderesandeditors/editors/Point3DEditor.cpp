/*
 * Point3DEditor.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "Point3DEditor.h"

Point3DEditor::Point3DEditor() {

}

Point3DEditor::~Point3DEditor() {
}

void Point3DEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, point.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void Point3DEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	point = *(static_cast<Point3D*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool Point3DEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	Point3DFrame dialog;
	dialog.SetPoint3D(point);
	if (dialog.ShowModal() == wxID_OK) {
		point = dialog.GetPoint3D();

		return true;
	}
	return false;
}

void Point3DEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &point);
}

void Point3DEditor::Reset() {

}

wxString Point3DEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* Point3DEditor::Clone() const {
	Point3DEditor* clone = new Point3DEditor;

	return clone;
}
