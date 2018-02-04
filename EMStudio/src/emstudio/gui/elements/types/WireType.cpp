/*
 * WireType.cpp
 *
 *  Created on: 15/07/2014
 *      Author: leandrocarisio
 */

#include "WireType.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

WireType::WireType() {
}

WireType::~WireType() {
}

wxString WireType::GetName() {
	return "Wires";
}

wxIcon WireType::GetIcon() {
	return UtilResource::GetIcon("objects3d");
}

ElementTypeSmartPointer WireType::NewElementType() {
	return ElementTypeSmartPointer(new WireType());
}
int WireType::GetSortIndex() {
	return 3;
}
} /* namespace mom */
