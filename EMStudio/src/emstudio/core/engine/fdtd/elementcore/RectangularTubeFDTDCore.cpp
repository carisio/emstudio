/*
 * RectangularTubeFDTDCore.cpp
 *
 *  Created on: 07/05/2012
 *      Author: Leandro
 */

#include "RectangularTubeFDTDCore.h"

RectangularTubeFDTDCore::RectangularTubeFDTDCore() {

}

RectangularTubeFDTDCore::~RectangularTubeFDTDCore() {
}

ElementCoreSmartPointer RectangularTubeFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new RectangularTubeFDTDCore);
}

void RectangularTubeFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
}
