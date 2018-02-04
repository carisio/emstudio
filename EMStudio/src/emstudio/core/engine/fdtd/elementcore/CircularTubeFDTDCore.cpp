/*
 * CircularTubeFDTDCore.cpp
 *
 *  Created on: 07/05/2012
 *      Author: Leandro
 */

#include "CircularTubeFDTDCore.h"

CircularTubeFDTDCore::CircularTubeFDTDCore() {

}

CircularTubeFDTDCore::~CircularTubeFDTDCore() {
}


ElementCoreSmartPointer CircularTubeFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new CircularTubeFDTDCore);
}

void CircularTubeFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
}
