/*
 * MethodType.cpp
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#include "MethodType.h"
#include "emstudio/util/resources/UtilResource.h"

MethodType::MethodType() {
}

MethodType::~MethodType() {
}

wxString MethodType::GetName() {
	return "Method";
}

wxIcon MethodType::GetIcon() {
	return UtilResource::GetIcon("methods");
}

ElementTypeSmartPointer MethodType::NewElementType() {
	return ElementTypeSmartPointer(new MethodType());
}
int MethodType::GetSortIndex() {
	return 1;
}
