/*
 * MicrostripFDTDCore.h
 *
 *  Created on: 08/02/2012
 *      Author: Leandro
 */

#ifndef MICROSTRIPFDTDCORE_H_
#define MICROSTRIPFDTDCORE_H_

#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/dto/fdtdapp/MicrostripDTO.h"
#include "emstudio/dto/fdtdapp/BoxDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"
#include "FDTDElementCore.h"

class RectangularPECSheetFDTDCore;

class MicrostripFDTDCore : public FDTDElementCore {
private:
	MicrostripDTO dto;

	ElementCoreSmartPointer pecUnderSubstrateCore;
	ElementCoreSmartPointer lineCore;

	// Largura da fita em x
	int i1, i2;
	// Pontos de alimentação em y
	int j1, j2;
	// Altura do box
	int k1, k2;

	// Portas
	Array2D<double> VPorts;
	vector<pair<int, int> > portsXYindex;
	Array2D<double> VPortsF1;
	Array2D<double> VPortsF2;

	Array1D<double> time;
	Array1D<double> excitationValue;

	Array1D<double> V, Voff;
	Array1D<double> I, Ioff;

	Array1D<double> VOut;
	Array1D<double> IOut;
	Array1D<double> VInc;
	Array1D<double> VRef;

	double Z0;
	double c_times_dt;

	double dx;
	double dy;
	double dz;
	double dl;

	Array1D<double> frequency;
	Array1D<double> omega;
	Array1D<double> RD1;
	Array1D<double> RD2;
	Array1D<double> VF1;
	Array1D<double> VF2;
	Array1D<double> IF1;
	Array1D<double> IF2;
	Array1D<double> VI1;
	Array1D<double> VI2;
	Array1D<double> VR1;
	Array1D<double> VR2;

	Array1D<double> Zout1;
	Array1D<double> Zout2;
	Array1D<double> VSWR;
	Array1D<double> S11;

	double Sc_1D_lower;
	//lower storage values for the 2nd-order ABC used in the 1-D grid
	//(1st dimension: upward on the auxiliary grid, 2nd dimension: backward in time)
	Array2D<double> PreviousVLower;
	Array2D<double> PreviousVoffLower;
	Array2D<double> PreviousVoffUpper;

public:
	MicrostripFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void DFieldsChanged(double t);
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsElementConsistent();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual ~MicrostripFDTDCore();
};

#endif /* MICROSTRIPFDTDCORE_H_ */
