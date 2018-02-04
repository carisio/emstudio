/*
 * ProbeType.cpp
 *
 *  Created on: 05/02/2012
 *      Author: Leandro
 */

#include "ProbeType.h"
#include "emstudio/util/resources/UtilResource.h"

ProbeType::ProbeType() {

}

ProbeType::~ProbeType() {
}

wxString ProbeType::GetName() {
	return "Probe";
}

wxIcon ProbeType::GetIcon() {
	return UtilResource::GetIcon("probes");
}

ElementTypeSmartPointer ProbeType::NewElementType() {
	return ElementTypeSmartPointer(new ProbeType());
}
int ProbeType::GetSortIndex() {
	return 5;
}
