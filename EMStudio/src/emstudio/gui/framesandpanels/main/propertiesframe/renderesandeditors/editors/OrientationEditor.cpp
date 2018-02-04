/*
 * OrientationEditor.cpp
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#include "OrientationEditor.h"

OrientationEditor::OrientationEditor()
	: FixedComboBoxEditor(Orientation::GetPossibleOrientations()) {

}

OrientationEditor::~OrientationEditor() {

}

FixedComboBoxEditor* OrientationEditor::DoClone() const {
	return new OrientationEditor();
}

//void OrientationEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
//	wxComboBox* cbox = new wxComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, Orientation::GetPossibleOrientations(), wxCB_READONLY | wxBORDER_NONE);
//	SetControl(cbox);
//	wxGridCellEditor::Create(parent, id, evtHandler);
//}
//
//void OrientationEditor::BeginEdit(int row, int col, wxGrid *grid) {
//	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
//	value = *(static_cast<Orientation*>(table->GetValueAsBaseType(row, col)));
//	wxComboBox* controle = (static_cast<wxComboBox*>(GetControl()));
//
//	controle->SetStringSelection(value.GetUserFriendlyStringRepresentation());
//}
//
//bool OrientationEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
//	wxComboBox* controle = (static_cast<wxComboBox*>(GetControl()));
//
//	return !(value.GetUserFriendlyStringRepresentation() == controle->GetStringSelection());
//}
//
//void OrientationEditor::ApplyEdit (int row, int col, wxGrid *grid) {
//	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
//	wxComboBox* controle = (static_cast<wxComboBox*>(GetControl()));
//
//	value.SetUserFriendlyStringRepresentation(controle->GetStringSelection());
//	table->SetValueAsBaseType(row, col, &value);
//}
//
//void OrientationEditor::Reset() {
//	wxComboBox* control = (static_cast<wxComboBox*>(GetControl()));
//	control->SetValue(value.GetUserFriendlyStringRepresentation());
//}
//
//wxString OrientationEditor::GetValue() const {
//	return "MEMBER FUNCTION NOT USED";
//}



