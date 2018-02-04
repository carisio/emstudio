/*
 * VisualizationPanel.cpp
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */

#include "VisualizationPanel.h"

#include <iostream>
using namespace::std;

/**
 * Obs.: Após o construtor, é necessário chamar o método Create
 */
VisualizationPanel::VisualizationPanel(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_STATIC),
	  elementsInProject(elementsInProject) {

}
void VisualizationPanel::Create() {
	openGLVisualization = new OpenGLVisualization(this);
	openGLStateMachine = CreateOpenGLStateMachine(openGLVisualization, elementsInProject);
	openGLVisualization->SetOpenGLStateMachine(openGLStateMachine);

	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(VisualizationPanel::Resize));
}
OpenGLStateMachine* VisualizationPanel::GetOpenGLStateMachine() {
	return openGLStateMachine;
}
void VisualizationPanel::ForceRedraw() {
//	openGLVisualization->ClearBackground();
	openGLVisualization->Refresh();
	openGLVisualization->Update();
}
OpenGLStateMachine* VisualizationPanel::CreateOpenGLStateMachine(OpenGLVisualization* canvas, ElementManagerSmartPointer elementsInProject) {
	return new OpenGLStateMachine(canvas, elementsInProject);
}

VisualizationPanel::~VisualizationPanel() {
	/* O openGLVisualization já é apagado automaticamente pelo wxPanel */
	delete openGLStateMachine;
}

void VisualizationPanel::Resize(wxSizeEvent& event) {
//	cout << "-------------" << endl;
	wxSize newSize = this->GetClientSize();
	openGLVisualization->SetSize(newSize);
//	cout << "VisualizationPanel::Resize : " << this << "\t" << newSize.x << " \t " << newSize.y << endl;
//	cout << "-------------" << endl;
}

void VisualizationPanel::SetCameraMode(int mode) {
    openGLVisualization->SetCameraMode(mode);
}

void VisualizationPanel::EnableCameraRotate() {
	openGLVisualization->SetMouseMoveFuncion(ROTATE);
}
void VisualizationPanel::EnableCameraMove() {
	openGLVisualization->SetMouseMoveFuncion(MOVE);
}
void VisualizationPanel::EnableCameraZoom() {
	openGLVisualization->SetMouseMoveFuncion(ZOOM);
}
