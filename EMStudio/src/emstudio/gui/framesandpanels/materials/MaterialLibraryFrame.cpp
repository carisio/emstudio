/*
 * MaterialLibraryFrame.cpp
 *
 *  Created on: 28/09/2011
 *      Author: leandrocarisio
 */

#include "MaterialLibraryFrame.h"

MaterialLibraryFrame::MaterialLibraryFrame(wxWindow* parent, MaterialLibrarySmartPointer ml, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX), library(ml) {
	CreateAndInsertControls();
}

void MaterialLibraryFrame::CreateAndInsertControls() {
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	wxArrayString list = library->GetMaterialDescriptionList();
	materialList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, list, wxLB_SINGLE);
	topSizer->Add(materialList, 0, wxEXPAND, 5);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* buttonNew = new wxButton(this, wxID_ANY, "New");
	wxButton* buttonEdit = new wxButton(this, wxID_ANY, "Edit");
	wxButton* buttonDelete = new wxButton(this, wxID_ANY, "Delete");
	wxButton* buttonExport = new wxButton(this, wxID_ANY, "Export");
	wxButton* buttonImport = new wxButton(this, wxID_ANY, "Import");
	Connect(buttonNew->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MaterialLibraryFrame::NewMaterial));
	Connect(buttonEdit->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MaterialLibraryFrame::EditMaterial));
	Connect(buttonDelete->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MaterialLibraryFrame::DeleteMaterial));
	Connect(buttonExport->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MaterialLibraryFrame::ExportMaterial));
	Connect(buttonImport->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MaterialLibraryFrame::ImportMaterial));

	buttonSizer->Add(buttonNew, 0, wxALIGN_CENTER, 5);
	buttonSizer->Add(buttonEdit, 0, wxALIGN_CENTER, 5);
	buttonSizer->Add(buttonDelete, 0, wxALIGN_CENTER, 5);
	buttonSizer->Add(buttonExport, 0, wxALIGN_CENTER, 5);
	buttonSizer->Add(buttonImport, 0, wxALIGN_CENTER, 5);
	topSizer->Add(buttonSizer, 0, wxEXPAND, 5);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void MaterialLibraryFrame::RebuildListBox() {
	wxArrayString list = library->GetMaterialDescriptionList();
	materialList->Clear();
	if (list.Count() != 0) {
		materialList->Append(list);
	}
	Fit();
}
void MaterialLibraryFrame::NewMaterial(wxCommandEvent& event) {
	NewMaterialFrame* nmf = new NewMaterialFrame(this);
	nmf->ShowModal();

	if (nmf->GetReturnCode() == wxID_OK) {
		library->Register(nmf->GetMaterial());
		RebuildListBox();
		nmf->Destroy();
	} else if (nmf->GetReturnCode() == wxID_CANCEL) {
		nmf->Destroy();
	}
}
void MaterialLibraryFrame::EditMaterial(wxCommandEvent& event) {
	if (materialList->GetSelection() == wxNOT_FOUND)
		return;
	wxString description = materialList->GetString(materialList->GetSelection());
	Material m = library->GetMaterial(description);
	NewMaterialFrame* nmf = new NewMaterialFrame(this, m, wxID_ANY, "Edit Material");
	nmf->ShowModal();
	if (nmf->GetReturnCode() == wxID_OK) {
		library->ChangeMaterial(description, nmf->GetMaterial());
		RebuildListBox();
		nmf->Destroy();
	} else if (nmf->GetReturnCode() == wxID_CANCEL) {
		nmf->Destroy();
	}
}
void MaterialLibraryFrame::DeleteMaterial(wxCommandEvent& event) {
	if (materialList->GetSelection() == wxNOT_FOUND)
		return;

	wxString description = materialList->GetString(materialList->GetSelection());
	library->DeleteMaterial(description);
	RebuildListBox();
}
// TODO: ESSE BLOCO DE CÓDIGO ESTÁ REPLICADO TB NO MAINFRAME.
// VER A POSSIBILIDADE DE UNIFORMIZAR
void MaterialLibraryFrame::ExportMaterial(wxCommandEvent& event) {
	int result = UtilDialog::ShowYesNoCancelMessage("Export", "Export to...", "Material Library", "External file");

	wxString fileName = FileManager::FILE_NOT_CHOOSEN;
	if (result == wxID_NO) {
		wxString fileName = FileManager::ShowFileDialog(this, wxT("Save"), wxT("Material files (*.mat)|*.mat"), wxFD_SAVE);
	} else if (result == wxID_YES) {
		fileName = FileManager::GetMaterialLibraryFileName();
	}

	if (fileName != FileManager::FILE_NOT_CHOOSEN) {
		if (!(FileManager::SaveMaterialLibrary(fileName, *library))) {
			wxString msg = "Unable to save file ";
			msg.Append(fileName);
			UtilDialog::ShowErrorMessage(msg);
		}
	}

}
void MaterialLibraryFrame::ImportMaterial(wxCommandEvent& event) {
	wxString fileName = FileManager::ShowFileDialog(this, wxT("Open"), wxT("Material files (*.mat)|*.mat"), wxFD_OPEN);

	if (fileName != FileManager::FILE_NOT_CHOOSEN) {
		if (! (FileManager::OpenMaterialLibrary(fileName, library))) {
			wxString msg = "Unable to open file ";
			msg.Append(fileName);
			UtilDialog::ShowErrorMessage(msg);
		} else {
			RebuildListBox();
		}
	}
}
MaterialLibraryFrame::~MaterialLibraryFrame() {
}
