/*
 * ContainerPanel.h
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */

#ifndef CONTAINERPANEL_H_
#define CONTAINERPANEL_H_

#include "wx/wx.h"
#include "wx/splitter.h"
#include "LeftPanel.h"
#include "visualizationpanel/VisualizationPanel.h"
#include "propertiesframe/renderesandeditors/RenderersAndEditorsManager.h"
#include "InformProjectHasChangedCommand.h"
#include <tr1/memory>

class LeftPanel;
class InformProjectHasChangedCommand;
class ContainerPanel : public wxPanel {
private:
	VisualizationPanel* visualizationPanel;
//	BottomPanel* bottomPanel;
	LeftPanel* leftPanel;
	wxSplitterWindow* verticalSplitter;
//	wxSplitterWindow* horizontalSplitter;

	double upperSizeRelation, leftSizeRelation;
public:
	ContainerPanel(wxWindow* parent, ElementManagerSmartPointer availableElements, ElementManagerSmartPointer elementsInProject, RenderersAndEditorsManagerSmartPointer renderersAndEditorsManager, std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand, double upperSizeRelation = 0.85, double leftSizeRelation = 0.20);
	void RebuildProjectTree();
	virtual ~ContainerPanel();
	void Resize(wxSizeEvent& event);
	void AddMessage(wxString msg);

	void CloneSelectedElement();
	void DeleteSelectedElement();

	void SetCameraMode(int mode);
	void EnableCameraMove();
	void EnableCameraRotate();
	void EnableCameraZoom();
};

#endif /* CONTAINERPANEL_H_ */
