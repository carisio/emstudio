/*
 * EngineFactory.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "EngineFactory.h"
#include "emstudio/dto/fdtdapp/FDTDDTO.h"
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/dto/momapp/MoMDTO.h"
#include "emstudio/core/engine/mom/MoMEngine.h"

EngineFactory::EngineFactory() {

}

EngineFactory::~EngineFactory() {

}

EngineSmartPointer EngineFactory::NewEngine(ElementDTOSmartPointer dto, InformSimulationStatusSmartPointer status) {
	FDTDDTO fdtddto;
	mom::MoMDTO momdto;

	if (dto->GetDTOClassName() == fdtddto.GetDTOClassName()) {
		return EngineSmartPointer(new FDTDEngine(dto, status));
	}
	if (dto->GetDTOClassName() == momdto.GetDTOClassName()) {
		return EngineSmartPointer(new mom::MoMEngine(dto, status));
	}
	return EngineSmartPointer();
}
