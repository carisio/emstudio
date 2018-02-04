/*
 * HowToShowResults.cpp
 *
 *  Created on: 30/01/2012
 *      Author: Leandro
 */

#include "HowToShowResults.h"

HowToShowResults::HowToShowResults() {

}

HowToShowResults::~HowToShowResults() {
}

ResultSmartPointer HowToShowResults::GetResult() {
	return result;
}

void HowToShowResults::SetResult(ResultSmartPointer result) {
	this->result = result;
}
