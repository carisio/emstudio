/*
 * PropertiesFrame.cpp
 *
 *  Created on: 21/09/2011
 *      Author: leandrocarisio
 */

#include "PropertiesFrame.h"
#include "emstudio/util/dialogs/UtilDialog.h"

PropertiesFrame::PropertiesFrame(wxWindow* parent, PropertyableSmartPointer obj, RenderersAndEditorsManagerSmartPointer rendererAndEditors, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU/*|wxRESIZE_BORDER*/) {

	/* Cria grid */
	grid = new wxGrid(this, wxID_ANY);
	RegisterRenderersAndEditors(rendererAndEditors);
	SetObject(obj);

	/* Coloca o grid em cima */
	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(grid, 1, wxALL | wxALIGN_CENTER, 10);
//	topSizer->Add(grid, 1, wxALL | wxEXPAND, 10);

	/* Cria a parte de botões */
	wxBoxSizer *buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	/* Adiciona os botões ao sizer */
	topSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

	/* Estabelece que o sizer é a tela */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void PropertiesFrame::ConfigureGridLayout() {
	grid->SetRowLabelSize(wxGRID_AUTOSIZE);

	int n = grid->GetNumberRows();
	for (int i = 0; i < n; i++) {
		grid->SetRowSize(i, grid->GetDefaultRowSize() + 5);
		grid->DisableRowResize(i);
	}
	grid->SetColSize(0, 2*grid->GetDefaultColSize());
	grid->DisableColResize(0);
	grid->DisableColResize(1);
	grid->EnableDragGridSize(false);
	grid->EnableDragCell(false);
	this->Fit();
}
void PropertiesFrame::SetObject(PropertyableSmartPointer obj) {
	/* OriginalObject aponta para o objeto que recebeu como parâmetro */
	originalObject = obj;

	/* copiedObject é uma réplica do objeto recebido */
	copiedObject = originalObject->NewPropertyable();
	copiedObject->TransferDataFrom(originalObject);

	/* Envia o copiedObject para edição */
	grid->SetTable(new PropertiesGridTable(copiedObject), true);

	ConfigureGridLayout();
}

PropertiesFrame::~PropertiesFrame() {

}
bool PropertiesFrame::TestPropertiesValidator() {
	bool propertiesValid;

	if (copiedObject->IsPropertiesValid()) {
		propertiesValid = true;
	} else {
		UtilDialog::ShowErrorMessage(copiedObject->GetPropertiesErrorMessage(), "Validation error");
		propertiesValid = false;
	}

	return propertiesValid;
}
bool PropertiesFrame::TestAllPropertiesTogether() {
	bool allPropertiesTogetherValid = false;

	if (copiedObject->IsAllPropertiesTogetherValid()) {
		allPropertiesTogetherValid = true;
	} else {
		UtilDialog::ShowErrorMessage(copiedObject->GetAllPropertiesTogetherErrorMessage(), "Validation error");
		allPropertiesTogetherValid = false;
	}

	return allPropertiesTogetherValid;
}
bool PropertiesFrame::TransferDataFromWindow() {
	if (TestPropertiesValidator() && TestAllPropertiesTogether()) {
		originalObject->TransferDataFrom(copiedObject);
		originalObject->SetChanged(true);
		return true;
	} else {
		return false;
	}
}

void PropertiesFrame::RegisterRenderersAndEditors(RenderersAndEditorsManagerSmartPointer rendererAndEditors) {
	RenderersAndEditorsManager::RendererMap rendererMap = rendererAndEditors->GetRendererMap();
	RenderersAndEditorsManager::EditorMap   editorMap   = rendererAndEditors->GetEditorMap();

	RenderersAndEditorsManager::RendererMap::iterator rendererIterator = rendererMap.begin();
	RenderersAndEditorsManager::EditorMap::iterator   editorIterator   = editorMap.begin();

	while(rendererIterator != rendererMap.end()) {
		wxString propertyType = rendererIterator->first;
		wxGridCellRenderer* renderer = rendererIterator->second.get();
		wxGridCellEditor* editor = editorIterator->second.get();

		grid->RegisterDataType(propertyType, renderer->Clone(), editor->Clone());

		rendererIterator++;
		editorIterator++;
	}
}
