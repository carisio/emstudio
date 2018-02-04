/*
 * DeltaGapFDTDCore.h
 *
 *  Created on: 07/11/2011
 *      Author: leandrocarisio
 */

#ifndef DELTAGAPFDTDCORE_H_
#define DELTAGAPFDTDCORE_H_

#include <complex>
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "FDTDElementCore.h"
#include "emstudio/core/ElementCore.h"
#include "FDTDElementCore.h"
#include "emstudio/dto/fdtdapp/DeltaGapDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"
#include "emstudio/util/file/FileManager.h"
#include "wx/wx.h"

using namespace TNT;

class DeltaGapFDTDCore : public FDTDElementCore {
private:
	DeltaGapDTO dto;

	int i, j, k;
	double deltaS;
	//double inv_deltaS;
	double c_times_dt, En;

	Array1D<double> time;
	Array1D<double> excitationValue;
	Array1D<double> vOut;
	Array1D<double> iOut;

	Array1D<double> RD1;
	Array1D<double> RD2;
	Array1D<double> frequency;
	Array1D<double> omega;
	Array1D<double> VF1;
	Array1D<double> VF2;
	Array1D<double> IF1;
	Array1D<double> IF2;

	Array1D<double>Zout1;
	Array1D<double>Zout2;

public:
	DeltaGapFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void DFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual ~DeltaGapFDTDCore();
};

#endif /* DELTAGAPFDTDCORE_H_ */
