/*
 * DXFDXFFileEditor.cpp
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#include "DXFFileEditor.h"

#include "DXFFileEditor.h"
#include "emstudio/util/dialogs/UtilDialog.h"
#include "emstudio/util/file/FileManager.h"

DXFFileEditor::DXFFileEditor()
	: isEditionFinished(false) {

}

DXFFileEditor::~DXFFileEditor() {
}


void DXFFileEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, "", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void DXFFileEditor::BeginEdit(int row, int col, wxGrid *grid) {
	isEditionFinished = false;

	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	file = *(static_cast<DXFFile*>(table->GetValueAsBaseType(row, col)));
	wxTextCtrl* control = (static_cast<wxTextCtrl*>(GetControl()));

	control->SetValue(file.GetFileName());

	wxString fileName = FileManager::ShowFileDialog(control, "Open file", file.GetWildcard(), wxFD_OPEN);

	if (fileName != FileManager::FILE_NOT_CHOOSEN) {
		if (!(file.ProcessFile(fileName))) {
			wxString msg = "Unable to process file ";
			msg.Append(fileName);
			UtilDialog::ShowErrorMessage(msg);

			fileName = "";
		}
	}
	file.SetFileName(fileName);

	isEditionFinished = true;
	grid->SetGridCursor(row,col);
}

bool DXFFileEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	if (!isEditionFinished)
		return false;

	return true;
}

void DXFFileEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	// Valor já foi setado na variável value. Basta transferir para o objeto.
	table->SetValueAsBaseType(row, col, &file);
}

void DXFFileEditor::Reset() {

}

wxString DXFFileEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* DXFFileEditor::Clone() const {
	DXFFileEditor* clone = new DXFFileEditor;

	return clone;
}
