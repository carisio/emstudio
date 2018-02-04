/*
 * ElementsWithSegmentsDTO.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "ElementsWithSegmentsDTO.h"

namespace mom {

ElementsWithSegmentsDTO::ElementsWithSegmentsDTO() {

}

ElementsWithSegmentsDTO::~ElementsWithSegmentsDTO() {
}

void ElementsWithSegmentsDTO::Unnormalize(Units units) {
	if (HasSegments()) {
		double space = units.GetUserDefinedSpaceUnit().second;

		Segments::iterator it = segments.begin();
		Segments::iterator itEnd = segments.end();

		while (it != itEnd) {
			it->MultiplyByConstant(space);
			it++;
		}
	}
	DoUnnormalize(units);
}
void ElementsWithSegmentsDTO::DoUnnormalize(Units units) {

}

bool ElementsWithSegmentsDTO::HasSegments() {
	return segments.size() > 0;
}
void ElementsWithSegmentsDTO::SetSegments(Segments s) {
	segments = s;
}
Segments ElementsWithSegmentsDTO::GetSegments() {
	return segments;
}

} /* namespace mom */
