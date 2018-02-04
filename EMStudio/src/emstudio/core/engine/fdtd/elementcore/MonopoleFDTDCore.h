/*
 * MonopoleFDTDCore.h
 *
 *  Created on: 21/12/2011
 *      Author: leandrocarisio
 */

#ifndef MONOPOLEFDTDCORE_H_
#define MONOPOLEFDTDCORE_H_

#include <complex>
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "FDTDElementCore.h"
#include "emstudio/core/ElementCore.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"
#include "emstudio/util/file/FileManager.h"
#include "wx/wx.h"
#include "emstudio/dto/fdtdapp/MonopoleDTO.h"

class MonopoleFDTDCore : public FDTDElementCore {
private:
	MonopoleDTO dto;

	// Índices nas extremedidas do dipolo e na excitação
	int iExcitation, jExcitation, kExcitation;
	int i1, j1, k1;
	int i2, j2, k2;
	int l1, l2;
	double deltaSExcitation;

	Array1D<double> HLeft;
	Array1D<double> HRight;
	Array1D<double> HFront;
	Array1D<double> HBottom;

	Array1D<double> V;
	Array1D<double> I;

	double c_times_dt;

	Array1D<double> excitationValue;
	Array1D<double> VOut;
	Array1D<double> IOut;
//	Array1D<double> VRef;
//	Array1D<double> VInc;

	Array1D<double> time;
	Array1D<double> frequency;

	Array1D<double> omega;
	Array1D<double> RD1;
	Array1D<double> RD2;
	Array1D<double> VF1;
	Array1D<double> VF2;
//	Array1D<double> VR1;
//	Array1D<double> VR2;
//	Array1D<double> VI1;
//	Array1D<double> VI2;
	Array1D<double> IF1;
	Array1D<double> IF2;
	Array1D<double> Zout1;
	Array1D<double> Zout2;
	Array1D<double> VSWR;
	Array1D<double> S11;

//	double V1, V2;
	double velocity_factor;

	Array2D<double> PreviousVLower;	//lower storage values for the 2nd-order ABC used in the 1-D grid (1st dimension: upward on the auxiliary grid, 2nd dimension: backward in time)
	double Sc_1D_lower;

public:
	MonopoleFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void DFieldsChanged(double t);
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual bool IsElementConsistent();

	virtual ~MonopoleFDTDCore();
};

#endif /* MONOPOLEFDTDCORE_H_ */
