/*
 * ColourWrapperEditor.cpp
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#include "ColourWrapperEditor.h"
#include "wx/colordlg.h"
#include "wx/utils.h"

ColourWrapperEditor::ColourWrapperEditor()
	: value(), isEditionFinished(false) {

}

ColourWrapperEditor::~ColourWrapperEditor() {

}

void ColourWrapperEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, "", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void ColourWrapperEditor::BeginEdit(int row, int col, wxGrid *grid) {
	isEditionFinished = false;

	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	value = *(static_cast<ColourWrapper*>(table->GetValueAsBaseType(row, col)));
	wxTextCtrl* control = (static_cast<wxTextCtrl*>(GetControl()));

	control->SetBackgroundColour(value.GetValue());

	wxColourData data;
	data.SetChooseFull(true);
	wxColourDialog dialog(control, &data);
	if (dialog.ShowModal() == wxID_OK) {
		wxColourData retData = dialog.GetColourData();
		wxColour col = retData.GetColour();

		value.SetValue(col);
	}
	isEditionFinished = true;
	grid->SetGridCursor(row,col);
}

bool ColourWrapperEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	if (!isEditionFinished)
		return false;

	return true;
}

void ColourWrapperEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	// Valor já foi setado na variável value. Basta transferir para o objeto.
	table->SetValueAsBaseType(row, col, &value);
}

void ColourWrapperEditor::Reset() {

}

wxString ColourWrapperEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* ColourWrapperEditor::Clone() const {
	ColourWrapperEditor* clone = new ColourWrapperEditor;

	return clone;
}

wxColour ColourWrapperEditor::GetNegative(wxColour c) {
	char r = c.Red();
	char g = c.Green();
	char b = c.Blue();
	return wxColour(255-r, 255-g, 255-b);
}
