/*
 * CylinderFDTDCore.cpp
 *
 *  Created on: 03/03/2012
 *      Author: Leandro
 */

#include "CylinderFDTDCore.h"
#include "emstudio/util/constants/Constants.h"

CylinderFDTDCore::CylinderFDTDCore() {

}

CylinderFDTDCore::~CylinderFDTDCore() {

}

ElementCoreSmartPointer CylinderFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new CylinderFDTDCore);
}

void CylinderFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	CylinderDTO* cylinderDTO = static_cast<CylinderDTO*>(elementDTOSmartPtr.get());

	dto = *cylinderDTO;

}
