/*
 * GenericPECSheetsFDTDCore.h
 *
 *  Created on: 16/12/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICPECSHEETSFDTDCORE_H_
#define GENERICPECSHEETSFDTDCORE_H_

#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "FDTDElementCore.h"
#include "emstudio/dto/fdtdapp/GenericPECSheetsDTO.h"
#include <vector>

class GenericPECSheetsFDTDCore : public FDTDElementCore {
private:
	GenericPECSheetsDTO dto;
	std::vector<ElementCoreSmartPointer> individualSheets;
public:
	GenericPECSheetsFDTDCore();
	virtual ~GenericPECSheetsFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsElementConsistent();
};

#endif /* GENERICPECSHEETSFDTDCORE_H_ */
