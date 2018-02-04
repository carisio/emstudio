/*
 * ResultsContainerPanel.h
 *
 *  Created on: 13/01/2012
 *      Author: leandrocarisio
 */

#ifndef RESULTSCONTAINERPANEL_H_
#define RESULTSCONTAINERPANEL_H_

#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/splitter.h"
#include "emstudio/core/results/Result.h"
#include "ResultTreeCtrl.h"
#include "emstudio/gui/elements/ElementManager.h"
#include "howtoshowresults/HowToShowResultsManager.h"
#include "howtoshowresults/HowToShowResults.h"

class ResultsContainerPanel : public wxPanel {
private:
	ResultTree& resultTree;
	wxNotebook* resultVisualizationPanel;
	ResultTreeCtrl* resultTreeGUI;
	wxSplitterWindow* splitter;

	HowToShowResultsManagerSmartPointer howToShowResultsManagerPtr;

	double leftSizeRelation;
public:
	ResultsContainerPanel(wxWindow* parent, ResultTree& tree, ElementManagerSmartPointer availableElement, HowToShowResultsManagerSmartPointer howToShowResultsManager, double leftSizeRelation = 0.25);
	virtual ~ResultsContainerPanel();

	void UpdateResultVisualizationPanel(ResultSmartPointer resultSmartPtr);
	void BuildResultsTree();
	void Resize(wxSizeEvent& event);

};

#endif /* RESULTSCONTAINERPANEL_H_ */
