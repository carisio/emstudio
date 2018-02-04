/*
 * ContainerPanel.cpp
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */

#include "ContainerPanel.h"

ContainerPanel::ContainerPanel(wxWindow* parent, ElementManagerSmartPointer availableElements, ElementManagerSmartPointer elementsInProject, RenderersAndEditorsManagerSmartPointer renderersAndEditorsManager, std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand, double upperSizeRelation_, double leftSizeRelation_)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), upperSizeRelation(upperSizeRelation_), leftSizeRelation(leftSizeRelation_) {

//	horizontalSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_NOBORDER);
	verticalSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_NOBORDER);

//	bottomPanel = new BottomPanel(horizontalSplitter, wxID_ANY);
	visualizationPanel = new VisualizationPanel(verticalSplitter, wxID_ANY, elementsInProject);
	visualizationPanel->Create();
	leftPanel = new LeftPanel(verticalSplitter, wxID_ANY, availableElements, elementsInProject, renderersAndEditorsManager, visualizationPanel, prjHasChangedCommand);

	verticalSplitter->SplitVertically(leftPanel, visualizationPanel);
//	horizontalSplitter->SplitHorizontally(verticalSplitter,bottomPanel);

	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(ContainerPanel::Resize));
}
ContainerPanel::~ContainerPanel() {
}
void ContainerPanel::RebuildProjectTree() {
	leftPanel->RebuildProjectTree();
}
void ContainerPanel::Resize(wxSizeEvent& event) {
	wxSize size = event.GetSize();
	int width = size.GetWidth();

	verticalSplitter->SetSize(size);
	verticalSplitter->SetSashPosition(width*leftSizeRelation);
}

void ContainerPanel::AddMessage(wxString msg) {
//	bottomPanel->AddMessage(msg);
}

void ContainerPanel::CloneSelectedElement() {
	leftPanel->CloneSelectedElement();
}

void ContainerPanel::DeleteSelectedElement() {
	leftPanel->DeleteSelectedElement();
}

void ContainerPanel::SetCameraMode(int mode) {
    visualizationPanel->SetCameraMode(mode);
}
void ContainerPanel::EnableCameraMove() {
    visualizationPanel->EnableCameraMove();
}
void ContainerPanel::EnableCameraRotate() {
    visualizationPanel->EnableCameraRotate();
}
void ContainerPanel::EnableCameraZoom() {
    visualizationPanel->EnableCameraZoom();
}


