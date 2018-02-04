/*
 * HowToShowSimpleTextResult.h
 *
 *  Created on: 30/09/2015
 *      Author: Leandro
 */

#ifndef EMSTUDIO_GUI_FRAMESANDPANELS_RESULTS_HOWTOSHOWRESULTS_HOWTOSHOWSIMPLETEXTRESULT_H_
#define EMSTUDIO_GUI_FRAMESANDPANELS_RESULTS_HOWTOSHOWRESULTS_HOWTOSHOWSIMPLETEXTRESULT_H_

#include "HowToShowResults.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/core/results/SimpleTextResult.h"

#include "wx/wx.h"


class HowToShowSimpleTextResult : public HowToShowResults {
public:
	HowToShowSimpleTextResult();
	virtual ~HowToShowSimpleTextResult();

	virtual int GetNumberOfTabs();
	virtual wxString GetTabName(int tabIndex);
	virtual wxWindow* GetWindow(int tabIndex, wxWindow* parent);
};

#endif /* EMSTUDIO_GUI_FRAMESANDPANELS_RESULTS_HOWTOSHOWRESULTS_HOWTOSHOWSIMPLETEXTRESULT_H_ */
