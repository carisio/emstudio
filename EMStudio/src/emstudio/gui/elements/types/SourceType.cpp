/*
 * Source.cpp
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#include "SourceType.h"
#include "emstudio/util/resources/UtilResource.h"

SourceType::SourceType() {

}

SourceType::~SourceType() {

}

wxString SourceType::GetName() {
	return "Source";
}

wxIcon SourceType::GetIcon() {
	return UtilResource::GetIcon("sources");
}

ElementTypeSmartPointer SourceType::NewElementType() {
	return ElementTypeSmartPointer(new SourceType());
}
int SourceType::GetSortIndex() {
	return 2;
}
