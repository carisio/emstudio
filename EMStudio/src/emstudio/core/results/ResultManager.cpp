/*
 * ResultManager.cpp
 *
 *  Created on: 26/03/2012
 *      Author: leandrocarisio
 */

#include "ResultManager.h"

ResultManager::ResultManager() {

}

ResultManager::~ResultManager() {
}

void ResultManager::AddResult(ResultSmartPointer r) {
	resultList.push_back(r);
}
ResultSmartPointer ResultManager::NewResult(wxString resultClassName) {
	ResultSmartPointer r;

	std::list<ResultSmartPointer>::iterator it = resultList.begin();
	std::list<ResultSmartPointer>::iterator itEnd = resultList.end();

	while (it != itEnd) {
		if ( (*it)->GetResultClassName() == resultClassName ) {
			r = (*it)->NewResult();
			break;
		}

		it++;
	}

	return r;
}
