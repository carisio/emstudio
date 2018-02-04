/*
 * FileEditor.cpp
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#include "FileEditor.h"
#include "emstudio/util/dialogs/UtilDialog.h"
#include "emstudio/util/file/FileManager.h"

FileEditor::FileEditor()
	: isEditionFinished(false) {

}

FileEditor::~FileEditor() {
}


void FileEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
	SetControl(new wxTextCtrl(parent, id, "", wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_CENTRE));

	wxGridCellEditor::Create(parent, id, evtHandler);
}

void FileEditor::BeginEdit(int row, int col, wxGrid *grid) {
	isEditionFinished = false;

	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());

	file = *(static_cast<File*>(table->GetValueAsBaseType(row, col)));
	wxTextCtrl* control = (static_cast<wxTextCtrl*>(GetControl()));

	control->SetValue(file.GetFileName());

	wxString fileName = FileManager::ShowFileDialog(control, "Open file", file.GetWildcard(), wxFD_OPEN);

	if (fileName != FileManager::FILE_NOT_CHOOSEN) {
		wxString contents;
		if (! (FileManager::OpenFile(fileName, contents))) {
			wxString msg = "Unable to open file ";
			msg.Append(fileName);
			UtilDialog::ShowErrorMessage(msg);

			fileName = "";
		} if (!(file.ProcessFile(fileName))) {
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

bool FileEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
	if (!isEditionFinished)
		return false;

	return true;
}

void FileEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	// Valor já foi setado na variável value. Basta transferir para o objeto.
	table->SetValueAsBaseType(row, col, &file);
}

void FileEditor::Reset() {

}

wxString FileEditor::GetValue() const {
	return "MEMBER FUNCTION NOT USED";
}

wxGridCellEditor* FileEditor::Clone() const {
	FileEditor* clone = new FileEditor;

	return clone;
}
