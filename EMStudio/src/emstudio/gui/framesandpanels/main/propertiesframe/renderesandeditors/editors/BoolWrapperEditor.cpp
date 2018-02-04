/*
 * BoolWrapperEditor.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "BoolWrapperEditor.h"
#include "wx/wx.h"
#include "emstudio/includes/renderesandeditors.h"

BoolWrapperEditor::BoolWrapperEditor()
	: value() {

}

BoolWrapperEditor::~BoolWrapperEditor() {

}


void BoolWrapperEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	wxGridCellBoolEditor::Create(parent, id, evtHandler);
//	SetControl(new wxCheckBox(parent, id, ""));

//	wxGridCellEditor::Create(parent, id, evtHandler);
}

void BoolWrapperEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	value = *(static_cast<BoolWrapper*>(table->GetValueAsBaseType(row, col)));
	wxCheckBox* controle = (static_cast<wxCheckBox*>(GetControl()));

	controle->SetValue(value.IsValue());
	controle->SetFocus();
}

bool BoolWrapperEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	wxCheckBox* controle = (static_cast<wxCheckBox*>(GetControl()));

	return !(value.IsValue() == controle->GetValue());
}

void BoolWrapperEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	wxCheckBox* controle = (static_cast<wxCheckBox*>(GetControl()));

	value.SetValue(controle->GetValue());
	table->SetValueAsBaseType(row, col, &value);
}

void BoolWrapperEditor::Reset() {
	wxCheckBox* control = (static_cast<wxCheckBox*>(GetControl()));
	control->SetValue(value.IsValue());
}

wxString BoolWrapperEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* BoolWrapperEditor::Clone() const {
	BoolWrapperEditor* clone = new BoolWrapperEditor;

	return clone;
}
