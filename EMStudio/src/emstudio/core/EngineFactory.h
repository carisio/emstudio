/*
 * EngineFactory.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef ENGINEFACTORY_H_
#define ENGINEFACTORY_H_

#include "emstudio/dto/ElementDTO.h"
#include "Engine.h"

class EngineFactory {
public:
	EngineFactory();

	static EngineSmartPointer NewEngine(ElementDTOSmartPointer dto, InformSimulationStatusSmartPointer status);

	virtual ~EngineFactory();
};

#endif /* ENGINEFACTORY_H_ */
