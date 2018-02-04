/*
 * ResultFrame.h
 *
 *  Created on: 13/01/2012
 *      Author: leandrocarisio
 */

#ifndef RESULTFRAME_H_
#define RESULTFRAME_H_

#include "wx/wx.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/gui/elements/ElementManager.h"
#include "ResultsContainerPanel.h"
#include "howtoshowresults/HowToShowResultsManager.h"

class ResultFrame : public wxDialog {
private:
	ResultTree& resultTree;
	ResultsContainerPanel* mainPanel;
public:
	ResultFrame(wxWindow* parent, ResultTree& results, ElementManagerSmartPointer availableElements, HowToShowResultsManagerSmartPointer howToShowResultsManagerPtr);

	void Resize(wxSizeEvent& event);

	virtual ~ResultFrame();
};

#endif /* RESULTFRAME_H_ */
