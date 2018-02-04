/*
 * HowToShowResults.h
 *
 *  Created on: 30/01/2012
 *      Author: Leandro
 */

#ifndef HOWTOSHOWRESULTS_H_
#define HOWTOSHOWRESULTS_H_

#include "wx/wx.h"
#include "emstudio/core/results/Result.h"

#include <tr1/memory>

class HowToShowResults;

typedef std::tr1::shared_ptr<HowToShowResults> HowToShowResultsSmartPointer;

class HowToShowResults {
private:
	ResultSmartPointer result;

public:
	HowToShowResults();
	virtual ~HowToShowResults();

	ResultSmartPointer GetResult();
	void SetResult(ResultSmartPointer result);

	virtual int GetNumberOfTabs() = 0;
	virtual wxString GetTabName(int tabIndex) = 0;
	virtual wxWindow* GetWindow(int tabIndex, wxWindow* parent) = 0;
};

#endif /* HOWTOSHOWRESULTS_H_ */
