/*
 * SphereFDTDCore.cpp
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#include "SphereFDTDCore.h"

SphereFDTDCore::SphereFDTDCore() {

}

SphereFDTDCore::~SphereFDTDCore() {

}

ElementCoreSmartPointer SphereFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new SphereFDTDCore);
}

void SphereFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	SphereDTO* sphereDTO = static_cast<SphereDTO*>(elementDTOSmartPtr.get());

	dto = *sphereDTO;

}
