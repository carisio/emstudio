/*
 * PlaneWavePBCFDTDCore.h
 *
 *  Created on: 27/03/2013
 *      Author: Leandro
 */

#ifndef PLANEWAVEPBCFDTDCORE_H_
#define PLANEWAVEPBCFDTDCORE_H_

#include <complex>
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "FDTDElementCore.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/core/ElementCore.h"
#include "emstudio/util/tnt/tnt.h"
#include "emstudio/util/file/FileManager.h"
#include "emstudio/util/vector/Rvector3.h"
#include "wx/wx.h"
#include "emstudio/dto/fdtdapp/PlaneWaveDTO.h"

class PlaneWavePBCFDTDCore : public FDTDElementCore {
private:
	PlaneWaveDTO dto;

	bool pbcXaxis;
	bool pbcZaxis;

	double En, dx, dy, dz, dt, cdt;
	int Nx, Ny, Nz, ia, ib, ja, jb, ka, kb;
	double Ez_low_m1, Ez_low_m2, Ez_high_m1, Ez_high_m2;

   Array1D<double> Ez_inc;
   Array1D<double> Hx_inc;
public:
	PlaneWavePBCFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual void SimulationWillStart();
	virtual void DFieldsChanged(double t);
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool IsElementConsistent();

	virtual ~PlaneWavePBCFDTDCore();
};

#endif /* PLANEWAVEPBCFDTDCORE_H_ */
