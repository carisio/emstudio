/*
 * ChargeDensities.cpp
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#include "ChargeDensities.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

ChargeDensities::ChargeDensities() : ElementsWithSegments(ElementTypeSmartPointer(new ProbeType())) {
}

ChargeDensities::~ChargeDensities() {

}

ElementGUISmartPointer ChargeDensities::NewElementGUI() {
	return ElementGUISmartPointer(new ChargeDensities());
}

wxString ChargeDensities::GetRegisteredName() {
	return "Charge Densities";
}

wxIcon ChargeDensities::GetIcon() {
	return UtilResource::GetIcon("thinwire");
}

ElementDTOSmartPointer ChargeDensities::NewElementDTO() {
	ChargeDensitiesDTO* result = new ChargeDensitiesDTO;
	return ElementDTOSmartPointer(result);
}
bool ChargeDensities::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	return valid;
}

void ChargeDensities::DoMove(Point3DME p) {
}
}
