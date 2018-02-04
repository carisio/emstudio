/*
 * RectangularSheetFDTDCore.h
 *
 *  Created on: 21/12/2011
 *      Author: leandrocarisio
 */

#ifndef PECSHEETFDTDCORE_H_
#define PECSHEETFDTDCORE_H_

#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "FDTDElementCore.h"
#include "emstudio/dto/fdtdapp/RectangularPECSheetDTO.h"
#include "emstudio/gui/basetypes/Plane.h"

class RectangularPECSheetFDTDCore : public FDTDElementCore {
private:
	RectangularPECSheetDTO dto;
	int imin, imax, jmin, jmax, kmin, kmax;
public:
	RectangularPECSheetFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsElementConsistent();

	virtual ~RectangularPECSheetFDTDCore();
};

#endif /* PECSHEETFDTDCORE_H_ */
