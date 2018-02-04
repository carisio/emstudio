/*
 * Point3DMEEditor.cpp
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#include "Point3DMEEditor.h"

Point3DMEEditor::Point3DMEEditor() {

}

Point3DMEEditor::~Point3DMEEditor() {
}


void Point3DMEEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, point.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void Point3DMEEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	point = *(static_cast<Point3DME*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool Point3DMEEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	Point3DMEFrame dialog;
	dialog.SetPoint3DME(point);
	if (dialog.ShowModal() == wxID_OK) {
		point = dialog.GetPoint3DME();

		return true;
	}
	return false;
}

void Point3DMEEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &point);
}

void Point3DMEEditor::Reset() {

}

wxString Point3DMEEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* Point3DMEEditor::Clone() const {
	Point3DMEEditor* clone = new Point3DMEEditor;

	return clone;
}
