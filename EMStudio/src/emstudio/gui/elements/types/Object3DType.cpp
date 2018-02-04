/*
 * ObjectType.cpp
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#include "Object3DType.h"
#include "emstudio/util/resources/UtilResource.h"

Object3DType::Object3DType() {

}

Object3DType::~Object3DType() {

}

wxString Object3DType::GetName() {
	return "3D Object";
}

wxIcon Object3DType::GetIcon() {
	return UtilResource::GetIcon("objects3d");
}

ElementTypeSmartPointer Object3DType::NewElementType() {
	return ElementTypeSmartPointer(new Object3DType());
}
int Object3DType::GetSortIndex() {
	return 4;
}
