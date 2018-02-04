/*
 * ThinWireFDTDCore.h
 *
 *  Created on: 07/11/2011
 *      Author: leandrocarisio
 */

#ifndef THINWIREFDTDCORE_H_
#define THINWIREFDTDCORE_H_

#include "FDTDElementCore.h"
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "emstudio/dto/fdtdapp/ThinWireDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"

using namespace TNT;

class ThinWireFDTDCore : public FDTDElementCore {
private:
	ThinWireDTO dto;

	int XCell, YCell, ZCell, LengthCell;

	double c_times_dt;
	Array1D<double> HLeft;
	Array1D<double> HRight;
	Array1D<double> HFront;
	Array1D<double> HBottom;
public:
	ThinWireFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual bool IsElementConsistent();

	virtual ~ThinWireFDTDCore();
};

#endif /* THINWIREFDTDCORE_H_ */
