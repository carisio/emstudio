/*
 * MaterialEditor.cpp
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#include "MaterialEditor.h"

MaterialEditor::MaterialEditor(MaterialLibrarySmartPointer library)
	: wxGridCellChoiceEditor(library->GetMaterialDescriptionList()), library(library) {

}

MaterialEditor::~MaterialEditor() {

}
//
//void MaterialEditor::Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler) {
//	wxComboBox* cbox = new wxComboBox(parent, wxID_ANY, value.GetDescription(), wxDefaultPosition, wxDefaultSize, library->GetMaterialDescriptionList(), wxCB_READONLY | wxBORDER_NONE);
//	SetControl(cbox);
//	wxGridCellEditor::Create(parent, id, evtHandler);
//}
//
void MaterialEditor::BeginEdit(int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	Material value = *(static_cast<Material*>(table->GetValueAsBaseType(row, col)));

	/* Verifica se o material carregado está contido na biblioteca. Se não estiver, insere na biblioteca em memória */
	library->Sync(&value, false);
//	if (! (library->Contains(value.GetDescription()))) {
//		library->Register(value);
//	}

	/* Monta o combo e seleciona */
	wxComboBox* controle = (static_cast<wxComboBox*>(GetControl()));
	controle->Clear();
	controle->Append(library->GetMaterialDescriptionList());
	controle->SetStringSelection(value.GetDescription());
	controle->SetFocus();
}
//
//bool MaterialEditor::EndEdit (int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval) {
//	wxComboBox* controle = (static_cast<wxComboBox*>(GetControl()));
//
//	return !(value.GetDescription() == controle->GetStringSelection());
//}
//
void MaterialEditor::ApplyEdit (int row, int col, wxGrid *grid) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	wxComboBox* controle = (static_cast<wxComboBox*>(GetControl()));

	Material temp = library->GetMaterial(controle->GetStringSelection());
	table->SetValueAsBaseType(row, col, &temp);
}
//
//void MaterialEditor::Reset() {
//	wxComboBox* control = (static_cast<wxComboBox*>(GetControl()));
//	control->SetValue(value.GetDescription());
//}
//
//wxString MaterialEditor::GetValue() const {
//	return "MEMBER FUNCTION NOT USED";
//}
//
wxGridCellEditor* MaterialEditor::Clone() const {
	MaterialEditor* clone = new MaterialEditor(library);

	return clone;
}

