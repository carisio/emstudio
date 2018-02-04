/*
 * BoxCore.h
 *
 *  Created on: 07/02/2012
 *      Author: Leandro
 */

#ifndef BOXCORE_H_
#define BOXCORE_H_

#include "FDTDElementCore.h"
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/dto/fdtdapp/BoxDTO.h"
#include "emstudio/util/constants/Constants.h"

class BoxFDTDCore : public FDTDElementCore {
private:
	BoxDTO dto;

public:
	BoxFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsElementConsistent();

	virtual ~BoxFDTDCore();
};

#endif /* BOXCORE_H_ */
