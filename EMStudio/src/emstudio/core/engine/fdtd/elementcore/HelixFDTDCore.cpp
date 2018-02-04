/*
 * HelixFDTDCore.cpp
 *
 *  Created on: 07/05/2012
 *      Author: Leandro
 */

#include "HelixFDTDCore.h"

HelixFDTDCore::HelixFDTDCore() {

}

HelixFDTDCore::~HelixFDTDCore() {
}

ElementCoreSmartPointer HelixFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new HelixFDTDCore);
}

void HelixFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
}
