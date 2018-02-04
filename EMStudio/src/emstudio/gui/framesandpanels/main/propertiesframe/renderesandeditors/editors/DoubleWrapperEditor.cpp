/*
 * DoubleWrapperEditor.cpp
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#include "DoubleWrapperEditor.h"
#include "wx/valnum.h"

DoubleWrapperEditor::DoubleWrapperEditor()
	: value() {
}

DoubleWrapperEditor::~DoubleWrapperEditor() {
}

void DoubleWrapperEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	wxFloatingPointValidator<double> validator(10, 0, wxNUM_VAL_ZERO_AS_BLANK);
	SetControl(new wxTextCtrl(parent, id, value.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxNO_BORDER | wxTE_RICH2,validator));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void DoubleWrapperEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	value = *(static_cast<DoubleWrapper*>(table->GetValueAsBaseType(row, col)));
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	controle->SetValue(Converter::DoubleToFormattedString_MaxPrecision(value.GetValue()));
	controle->SetInsertionPointEnd();
	controle->SetSelection(-1, -1);
	controle->SetFocus();
}

bool DoubleWrapperEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	return !(Converter::FloatToFormattedString(value.GetValue()) == controle->GetValue());
}

void DoubleWrapperEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	wxTextCtrl* controle = (static_cast<wxTextCtrl*>(GetControl()));

	value.SetValue(Converter::FormattedStringToDouble(controle->GetValue()));
	table->SetValueAsBaseType(row, col, &value);
}

void DoubleWrapperEditor::Reset() {
	wxTextCtrl* control = (static_cast<wxTextCtrl*>(GetControl()));
	control->SetValue(Converter::FloatToFormattedString(value.GetValue()));
}

wxString DoubleWrapperEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* DoubleWrapperEditor::Clone() const {
	DoubleWrapperEditor* clone = new DoubleWrapperEditor;

	return clone;
}

