/*
 * DXFObjectFDTDCore.cpp
 *
 *  Created on: 09/05/2013
 *      Author: Leandro
 */

#include "DXFObjectFDTDCore.h"

DXFObjectFDTDCore::DXFObjectFDTDCore() {

}

DXFObjectFDTDCore::~DXFObjectFDTDCore() {
}

ElementCoreSmartPointer DXFObjectFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new DXFObjectFDTDCore);
}

void DXFObjectFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
}
