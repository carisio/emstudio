/*
 * Object2DType.cpp
 *
 *  Created on: 20/11/2013
 *      Author: leandrocarisio
 */

#include "Object2DType.h"
#include "emstudio/util/resources/UtilResource.h"

Object2DType::Object2DType() {

}

Object2DType::~Object2DType() {
}

wxString Object2DType::GetName() {
	return "2D Object";
}

wxIcon Object2DType::GetIcon() {
	return UtilResource::GetIcon("objects2d");
}

ElementTypeSmartPointer Object2DType::NewElementType() {
	return ElementTypeSmartPointer(new Object2DType());
}
int Object2DType::GetSortIndex() {
	return 3;
}
