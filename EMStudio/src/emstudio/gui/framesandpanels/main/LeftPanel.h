/*
 * LeftPanel.h
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */

#ifndef LEFTPANEL_H_
#define LEFTPANEL_H_

#include "wx/wx.h"
#include "wx/splitter.h"
#include "wx/treectrl.h"

#include "emstudio/gui/elements/ElementGUI.h"
#include "emstudio/gui/elements/ElementType.h"
#include "emstudio/gui/elements/ElementManager.h"

#include "propertiesframe/PropertiesFrame.h"
#include "propertiesframe/renderesandeditors/RenderersAndEditorsManager.h"

#include "visualizationpanel/VisualizationPanel.h"

#include "emstudio/util/dialogs/UtilDialog.h"
#include "emstudio/gui/basetypes/Point3DME.h"

#include "InformProjectHasChangedCommand.h"

#include <list>
#include <tr1/memory>
using namespace::std;

class AvailableItemsTree;
class ProjectTree;
class InformProjectHasChangedCommand;
/*
 * LeftPanel class. A container to represent available and used items.
 */
class LeftPanel : public wxPanel {
private:
	wxSplitterWindow* horizontalSplitter;
	AvailableItemsTree* availableItemsTree;
	ProjectTree* projectTree;
public:
	LeftPanel(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsAvailables, ElementManagerSmartPointer elementsInProject, RenderersAndEditorsManagerSmartPointer renderersAndEditorsManager, VisualizationPanel* visualization,  std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand);
	virtual ~LeftPanel();
	void RebuildProjectTree();
	void Resize(wxSizeEvent& event);

	void CloneSelectedElement();
	void DeleteSelectedElement();
};

/*
 * A tree with the available items
 */
class ItemsTree;

class AvailableItemsTree : public wxTreeCtrl {
private:
	ElementManagerSmartPointer elementManager;
	ProjectTree* projectTree;
	ItemsTree* root;
    wxImageList *icons;
public:
	AvailableItemsTree(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer em, ProjectTree * prjTree);
	virtual ~AvailableItemsTree();
	void BuildTree();
	void DoubleClick(wxTreeEvent& event);
};

/*
 * A tree with items used in project
 */
class ProjectTree : public wxTreeCtrl {
private:
	std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand;
	ElementManagerSmartPointer elementManager;
	RenderersAndEditorsManagerSmartPointer renderersAndEditorsManager;
	wxImageList *icons;
	ItemsTree* root;

	PropertiesFrame* propertiesFrame;
	VisualizationPanel* visualizationPanel;

	wxMenu popUpMenu;
	static int ID_EDIT_ELEMENT;
	static int ID_MOVE_ELEMENT;
	static int ID_DELETE_ELEMENT;
	static int ID_CLONE_ELEMENT;

	void RightClick(wxTreeEvent& event);
	void DoubleClick(wxTreeEvent& event);
	void KeyDown(wxTreeEvent& event);

	// Eventos do popup
	ItemsTree *itemSelectedInPopupMenu;
	void CloneElement(wxCommandEvent& event);
	void EditElement(wxCommandEvent& event);
	void MoveElement(wxCommandEvent& event);
	void DeleteElement(wxCommandEvent& event);
	// Fim eventos do popup

	void BuildTreeAndInformProjectHasChanged();

	void DeleteItemTree(ItemsTree *item);
	void CloneItemTree(ItemsTree *item);
	void EditItemTree(ItemsTree* item);
	void MoveItemTree(ItemsTree* item, Point3DME point);
public:
	ProjectTree(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject, std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand, RenderersAndEditorsManagerSmartPointer renderersAndEditors, VisualizationPanel* visualizationPanel);
	virtual ~ProjectTree();
	void BuildTree();
	void AddElement(ElementGUISmartPointer element);
	void CloneSelectedElement();
	void DeleteSelectedElement();
	bool EditElement(ElementGUISmartPointer element);
};

class ItemsTree : public wxTreeItemData {
private:
	ElementGUISmartPointer element;
	wxString name;
	bool leaf;
public:
	ItemsTree(ElementGUISmartPointer element);
	ItemsTree(wxString name);
	~ItemsTree();

	ElementGUISmartPointer GetElement() const;
    wxString GetName() const;
    bool IsLeaf() const;
};
#endif /* LEFTPANEL_H_ */
