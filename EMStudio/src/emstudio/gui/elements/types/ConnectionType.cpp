/*
 * ConnectionType.cpp
 *
 *  Created on: 15/07/2014
 *      Author: leandrocarisio
 */

#include "ConnectionType.h"
#include "emstudio/util/resources/UtilResource.h"

namespace mom {

ConnectionType::ConnectionType() {

}

ConnectionType::~ConnectionType() {
}

wxString ConnectionType::GetName() {
	return "Connection";
}

wxIcon ConnectionType::GetIcon() {
	return UtilResource::GetIcon("objects3d");
}

ElementTypeSmartPointer ConnectionType::NewElementType() {
	return ElementTypeSmartPointer(new ConnectionType());
}
int ConnectionType::GetSortIndex() {
	return 4;
}
} /* namespace mom */
