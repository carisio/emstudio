/*
 * LongWrapperEditor.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "LongWrapperEditor.h"
#include "wx/valnum.h"

LongWrapperEditor::LongWrapperEditor()
	: value() {

}

LongWrapperEditor::~LongWrapperEditor() {

}


void LongWrapperEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	wxIntegerValidator<long> validator(0, wxNUM_VAL_ZERO_AS_BLANK);
	SetControl(new wxTextCtrl(parent, id, value.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxNO_BORDER | wxTE_RICH2,validator));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void LongWrapperEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	value = *(static_cast<LongWrapper*>(table->GetValueAsBaseType(row, col)));
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	controle->SetValue(value.GetUserFriendlyStringRepresentation());
	controle->SetInsertionPointEnd();
	controle->SetSelection(-1, -1);
	controle->SetFocus();
}

bool LongWrapperEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	return !(Converter::LongToFormattedString(value.GetValue()) == controle->GetValue());
}

void LongWrapperEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	value.SetValue(Converter::FormattedStringToLong(controle->GetValue()));
	table->SetValueAsBaseType(row, col, &value);
}

void LongWrapperEditor::Reset() {
	wxTextCtrl* control = (static_cast<wxTextCtrl*>(GetControl()));
	control->SetValue(Converter::LongToFormattedString(value.GetValue()));
}

wxString LongWrapperEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* LongWrapperEditor::Clone() const {
	LongWrapperEditor* clone = new LongWrapperEditor;

	return clone;
}
