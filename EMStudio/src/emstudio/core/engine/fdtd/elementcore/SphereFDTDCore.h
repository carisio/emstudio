/*
 * SphereFDTDCore.h
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#ifndef SPHEREFDTDCORE_H_
#define SPHEREFDTDCORE_H_

#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/dto/fdtdapp/SphereDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "FDTDElementCore.h"

class SphereFDTDCore : public FDTDElementCore {
private:
	SphereDTO dto;
public:
	SphereFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual ~SphereFDTDCore();
};

#endif /* SPHEREFDTDCORE_H_ */
