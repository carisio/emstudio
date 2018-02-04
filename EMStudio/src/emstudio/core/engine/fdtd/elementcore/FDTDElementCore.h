/*
 * FDTDElementCore.h
 *
 *  Created on: 08/11/2011
 *      Author: leandrocarisio
 */

#ifndef FDTDELEMENTCORE_H_
#define FDTDELEMENTCORE_H_

#include "emstudio/core/ElementCore.h"

//class FDTDEngine;

class FDTDElementCore : public ElementCore {
public:
	FDTDElementCore();

	virtual ElementCoreSmartPointer NewElementCore() = 0;
	virtual void DoConfigure(ElementDTOSmartPointer dto) = 0;

	virtual void SimulationWillStart();
	virtual void SimulationWillFinish();
	virtual void DFieldsChanged(double t);
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	void FillDimensionsWithFacets(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual ~FDTDElementCore();
};

#endif /* FDTDELEMENTCORE_H_ */
