/*
 * IntWrapperEditor.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "IntWrapperEditor.h"
#include "wx/valnum.h"

IntWrapperEditor::IntWrapperEditor()
	: value() {
}

IntWrapperEditor::~IntWrapperEditor() {

}

void IntWrapperEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	wxIntegerValidator<int> validator(0, wxNUM_VAL_ZERO_AS_BLANK);
	SetControl(new wxTextCtrl(parent, id, value.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxNO_BORDER | wxTE_RICH2,validator));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void IntWrapperEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	value = *(static_cast<IntWrapper*>(table->GetValueAsBaseType(row, col)));
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	controle->SetValue(value.GetUserFriendlyStringRepresentation());
	controle->SetInsertionPointEnd();
	controle->SetSelection(-1, -1);
	controle->SetFocus();
}

bool IntWrapperEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	return !(Converter::IntToFormattedString(value.GetValue()) == controle->GetValue());
}

void IntWrapperEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	value.SetValue(Converter::FormattedStringToInt(controle->GetValue()));
	table->SetValueAsBaseType(row, col, &value);
}

void IntWrapperEditor::Reset() {
	wxTextCtrl* control = (static_cast<wxTextCtrl*>(GetControl()));
	control->SetValue(Converter::IntToFormattedString(value.GetValue()));
}

wxString IntWrapperEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* IntWrapperEditor::Clone() const {
	IntWrapperEditor* clone = new IntWrapperEditor;

	return clone;
}
