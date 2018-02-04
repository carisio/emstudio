/*
 * ResultTreeCtrl.h
 *
 *  Created on: 13/01/2012
 *      Author: leandrocarisio
 */

#ifndef RESULTTREECTRL_H_
#define RESULTTREECTRL_H_

#include "wx/wx.h"
#include "wx/menu.h"
#include "wx/treectrl.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/gui/elements/ElementManager.h"

class ResultItemsTree;

class ResultTreeCtrl : public wxTreeCtrl {
private:
	wxMenu* popupMenu;
	ResultSmartPointer resultToExport;

	ResultTree& resultsTree;
	ResultItemsTree* root;
    wxImageList *icons;
    ElementManagerSmartPointer availableElements;

    void InsertElementsResultsNode(list<ElementResults>::iterator elementsResultsIterator, wxTreeItemId engineItemId_FatherNode);

    void BuildTree();

    void ResultSelected(wxTreeEvent& event);
    void OnItemRightClick(wxTreeEvent& event);
    void OnExportResultsTo(wxCommandEvent& event);
public:
    ResultTreeCtrl(wxWindow* parent, wxWindowID id, ResultTree& tree, ElementManagerSmartPointer availableElements);
	virtual ~ResultTreeCtrl();
};

class ResultItemsTree : public wxTreeItemData {
private:
	ResultSmartPointer result;
	wxString name;
	bool leaf;
public:
	ResultItemsTree(ResultSmartPointer result);
	ResultItemsTree(wxString name);
	~ResultItemsTree();

	ResultSmartPointer GetResult() const;
    wxString GetName() const;
    bool IsLeaf() const;
};

#endif /* RESULTTREECTRL_H_ */

