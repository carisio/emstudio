/*
 * CylinderFDTDCore.h
 *
 *  Created on: 03/03/2012
 *      Author: Leandro
 */

#ifndef CYLINDERFDTDCORE_H_
#define CYLINDERFDTDCORE_H_

#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/dto/fdtdapp/CylinderDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "FDTDElementCore.h"

class CylinderFDTDCore : public FDTDElementCore {
private:
	CylinderDTO dto;

public:
	CylinderFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual ~CylinderFDTDCore();
};

#endif /* CYLINDERFDTDCORE_H_ */
