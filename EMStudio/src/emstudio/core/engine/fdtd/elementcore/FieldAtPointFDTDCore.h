/*
 * FieldAtPointFDTDCore.h
 *
 *  Created on: 02/03/2012
 *      Author: Administrador
 */

#ifndef FIELDATPOINTFDTDCORE_H_
#define FIELDATPOINTFDTDCORE_H_

#include <complex>
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "FDTDElementCore.h"
#include "emstudio/core/ElementCore.h"
#include "emstudio/dto/fdtdapp/FieldAtPointDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"

class FieldAtPointFDTDCore : public FDTDElementCore {
private:
	FieldAtPointDTO dto;

	int i, j, k;

	int NFreq;
	double FIni, FStep;

	Array1D<double>RD1;
	Array1D<double>RD2;

	Array1D<double>omega;
	Array1D<double>frequency;
	Array1D<double>time;

	Array1D<double>Mag_Ex;
	Array1D<double>Mag_Ey;
	Array1D<double>Mag_Ez;
	Array1D<double>Mag_E;
	Array1D<double>Phase_Ex;
	Array1D<double>Phase_Ey;
	Array1D<double>Phase_Ez;
	Array1D<double>Mag_Hx;
	Array1D<double>Mag_Hy;
	Array1D<double>Mag_Hz;
	Array1D<double>Mag_H;
	Array1D<double>Phase_Hx;
	Array1D<double>Phase_Hy;
	Array1D<double>Phase_Hz;

	Array1D<double>ExR;
	Array1D<double>ExI;
	Array1D<double>EyR;
	Array1D<double>EyI;
	Array1D<double>EzR;
	Array1D<double>EzI;
	Array1D<double>HxR;
	Array1D<double>HxI;
	Array1D<double>HyR;
	Array1D<double>HyI;
	Array1D<double>HzR;
	Array1D<double>HzI;

	bool showTimeResponse;
	Array1D<double>timeE;
	Array1D<double>timeH;
	Array1D<double>ExT;
	Array1D<double>EyT;
	Array1D<double>EzT;
	Array1D<double>HxT;
	Array1D<double>HyT;
	Array1D<double>HzT;

public:
	FieldAtPointFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual ~FieldAtPointFDTDCore();
};

#endif /* FIELDATPOINTFDTDCORE_H_ */
