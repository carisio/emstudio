/*
 * GroundParametersEditor.cpp
 *
 *  Created on: 18/03/2015
 *      Author: Leandro
 */

#include <emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/GroundParametersEditor.h>

namespace mom {

GroundParametersEditor::GroundParametersEditor() {
	// TODO Auto-generated constructor stub

}

GroundParametersEditor::~GroundParametersEditor() {
	// TODO Auto-generated destructor stub
}

void GroundParametersEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, groundParameters.GetUserFriendlyStringRepresentation(), wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void GroundParametersEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	groundParameters = *(static_cast<GroundParameters*>(table->GetValueAsBaseType(row, col)));

	grid->SetGridCursor(row,col);
}

bool GroundParametersEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	GroundParametersFrame dialog;
	dialog.SetGroundParameters(groundParameters);
	if (dialog.ShowModal() == wxID_OK) {
		groundParameters = dialog.GetGroundParameters();

		return true;
	}
	return false;
}

void GroundParametersEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	table->SetValueAsBaseType(row, col, &groundParameters);
}

void GroundParametersEditor::Reset() {

}

wxString GroundParametersEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* GroundParametersEditor::Clone() const {
	GroundParametersEditor* clone = new GroundParametersEditor;

	return clone;
}

} /* namespace mom */
