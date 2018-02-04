/*
 * FloatWrapperEditor.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "FloatWrapperEditor.h"
#include "wx/valnum.h"

FloatWrapperEditor::FloatWrapperEditor()
	: value() {

}

FloatWrapperEditor::~FloatWrapperEditor() {

}


void FloatWrapperEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	wxFloatingPointValidator<float> validator(10, 0, wxNUM_VAL_ZERO_AS_BLANK);
	SetControl(new wxTextCtrl(parent, id, value.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxNO_BORDER | wxTE_RICH2,validator));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void FloatWrapperEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	value = *(static_cast<FloatWrapper*>(table->GetValueAsBaseType(row, col)));
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	controle->SetValue(value.GetUserFriendlyStringRepresentation());
	controle->SetInsertionPointEnd();
	controle->SetSelection(-1, -1);
	controle->SetFocus();
}

bool FloatWrapperEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	return !(Converter::FloatToFormattedString(value.GetValue()) == controle->GetValue());
}

void FloatWrapperEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	value.SetValue(Converter::FormattedStringToFloat(controle->GetValue()));
	table->SetValueAsBaseType(row, col, &value);
}

void FloatWrapperEditor::Reset() {
	wxTextCtrl* control = (static_cast<wxTextCtrl*>(GetControl()));
	control->SetValue(Converter::FloatToFormattedString(value.GetValue()));
}

wxString FloatWrapperEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* FloatWrapperEditor::Clone() const {
	FloatWrapperEditor* clone = new FloatWrapperEditor;

	return clone;
}
