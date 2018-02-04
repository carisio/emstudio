/*
 * ToroidFDTDCore.cpp
 *
 *  Created on: 08/05/2012
 *      Author: Leandro
 */

#include "ToroidFDTDCore.h"

ToroidFDTDCore::ToroidFDTDCore() {

}

ToroidFDTDCore::~ToroidFDTDCore() {
}


ElementCoreSmartPointer ToroidFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new ToroidFDTDCore);
}

void ToroidFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
}
