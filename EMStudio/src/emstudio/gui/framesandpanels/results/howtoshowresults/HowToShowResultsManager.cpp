/*
 * HowToShowResultsManager.cpp
 *
 *  Created on: 30/01/2012
 *      Author: Leandro
 */

#include "HowToShowResultsManager.h"
#include "HowToShowResults.h"
#include "HowToShowResultsManager.h"
#include "HowToShowTableResult.h"
#include "HowToShowFieldAtPathResult.h"
#include "HowToShowRadiationPatternResult.h"
#include "HowToShowFieldAtPlaneResult.h"
#include "HowToShowSegmentInformationResult.h"
#include "HowToShowSimpleTextResult.h"

#include "emstudio/core/results/RadiationPatternResult.h"
#include "emstudio/core/results/FieldAtPlaneResult.h"
#include "emstudio/core/results/FieldAtPathResult.h"
#include "emstudio/core/results/SegmentInformationResult.h"
#include "emstudio/core/results/SimpleTextResult.h"

HowToShowResultsManager::HowToShowResultsManager(ElementManagerSmartPointer elementsInProject)
	: howToShowResultsMap() {
	Register((SimpleTextResult()).GetResultClassName(), HowToShowResultsSmartPointer(new HowToShowSimpleTextResult));
	Register((TableResult()).GetResultClassName(), HowToShowResultsSmartPointer(new HowToShowTableResult));
	Register((RadiationPatternResult()).GetResultClassName(), HowToShowResultsSmartPointer(new HowToShowRadiationPatternResult));
	Register((FieldAtPathResult()).GetResultClassName(), HowToShowResultsSmartPointer(new HowToShowFieldAtPathResult));
	Register((FieldAtPlaneResult()).GetResultClassName(), HowToShowResultsSmartPointer(new HowToShowFieldAtPlaneResult(elementsInProject)));
	Register((mom::SegmentInformationResult()).GetResultClassName(), HowToShowResultsSmartPointer(new mom::HowToShowSegmentInformationResult(elementsInProject)));
}

HowToShowResultsManager::~HowToShowResultsManager() {

}

void HowToShowResultsManager::Register(wxString resultClassName, HowToShowResultsSmartPointer htsrsp) {
	howToShowResultsMap[resultClassName] = htsrsp;
}
HowToShowResultsManager::HowToShowResultsMap& HowToShowResultsManager::GetHowToShowResultsMap() {
	return howToShowResultsMap;
}
