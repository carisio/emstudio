/*
 * HowToShowResultsManager.h
 *
 *  Created on: 30/01/2012
 *      Author: Leandro
 */

#ifndef HOWTOSHOWRESULTSMANAGER_H_
#define HOWTOSHOWRESULTSMANAGER_H_

#include "wx/wx.h"

#include "HowToShowResults.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/gui/elements/ElementManager.h"
#include <map>
using namespace::std;


class HowToShowResultsManager;
typedef std::tr1::shared_ptr<HowToShowResultsManager> HowToShowResultsManagerSmartPointer;


class HowToShowResultsManager {
public:
	typedef map<wxString, HowToShowResultsSmartPointer> HowToShowResultsMap;
private:
	HowToShowResultsMap howToShowResultsMap;
public:
	HowToShowResultsManager(ElementManagerSmartPointer elementsInProject);
	virtual ~HowToShowResultsManager();

	void Register(wxString resultClassName, HowToShowResultsSmartPointer htsrsp);
	HowToShowResultsMap& GetHowToShowResultsMap();
};

#endif /* HOWTOSHOWRESULTSMANAGER_H_ */
