/*
 * VisualizationPanel.h
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */

#ifndef VISUALIZATIONPANEL_H_
#define VISUALIZATIONPANEL_H_

#include "wx/wx.h"
#include "OpenGLStateMachine.h"
#include "OpenGLVisualization.h"
#include "emstudio/gui/elements/ElementManager.h"


class VisualizationPanel : public wxPanel {
private:
	ElementManagerSmartPointer elementsInProject;
	OpenGLVisualization* openGLVisualization;
	OpenGLStateMachine* openGLStateMachine;

	void Resize(wxSizeEvent& event);
public:
	VisualizationPanel(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject);
	void Create();

	virtual OpenGLStateMachine* CreateOpenGLStateMachine(OpenGLVisualization* canvas, ElementManagerSmartPointer elementsInProject);

	OpenGLStateMachine* GetOpenGLStateMachine();

	void ForceRedraw();
	void SetCameraMode(int mode);
	void EnableCameraRotate();
	void EnableCameraMove();
	void EnableCameraZoom();
	virtual ~VisualizationPanel();
};

#endif /* VISUALIZATIONPANEL_H_ */
