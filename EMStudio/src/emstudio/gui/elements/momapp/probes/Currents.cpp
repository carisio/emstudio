/*
 * Currents.cpp
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#include "Currents.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

Currents::Currents() : ElementsWithSegments(ElementTypeSmartPointer(new ProbeType())) {
}

Currents::~Currents() {

}

ElementGUISmartPointer Currents::NewElementGUI() {
	return ElementGUISmartPointer(new Currents());
}

wxString Currents::GetRegisteredName() {
	return "Currents";
}

wxIcon Currents::GetIcon() {
	return UtilResource::GetIcon("thinwire");
}

ElementDTOSmartPointer Currents::NewElementDTO() {
	CurrentsDTO* result = new CurrentsDTO;
	return ElementDTOSmartPointer(result);
}
bool Currents::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	return valid;
}

void Currents::DoMove(Point3DME p) {
}
}
