/*
 * RadiationPatternFDTDCore.h
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#ifndef RADIATIONPATTERNFDTDCORE_H_
#define RADIATIONPATTERNFDTDCORE_H_

#include "FDTDElementCore.h"
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/dto/fdtdapp/RadiationPatternDTO.h"
#include "emstudio/util/tnt/tnt.h"
#include "emstudio/util/constants/Constants.h"
#include <complex>

class RadiationPatternFDTDCore : public FDTDElementCore {
private:
	RadiationPatternDTO dto;

	int NFreq;

	int Ri1, Rj1, Rk1;
	int Ri2, Rj2, Rk2;
	int Numi, Numj, Numk;

	Array2D<double> PLANOXY;
	Array2D<double> PLANOYZ;
	Array2D<double> PLANOZX;

	Array3D<double> ExIJt1;
	Array3D<double> ExIJt2;
	Array3D<double> EyIJt1;
	Array3D<double> EyIJt2;
	Array3D<double> HxIJt1;
	Array3D<double> HxIJt2;
	Array3D<double> HyIJt1;
	Array3D<double> HyIJt2;
	Array3D<double> ExIJb1;
	Array3D<double> ExIJb2;
	Array3D<double> EyIJb1;
	Array3D<double> EyIJb2;
	Array3D<double> HxIJb1;
	Array3D<double> HxIJb2;
	Array3D<double> HyIJb1;
	Array3D<double> HyIJb2;

	Array3D<double> ExIKt1;
	Array3D<double> ExIKt2;
	Array3D<double> EzIKt1;
	Array3D<double> EzIKt2;
	Array3D<double> HxIKt1;
	Array3D<double> HxIKt2;
	Array3D<double> HzIKt1;
	Array3D<double> HzIKt2;
	Array3D<double> ExIKb1;
	Array3D<double> ExIKb2;
	Array3D<double> EzIKb1;
	Array3D<double> EzIKb2;
	Array3D<double> HxIKb1;
	Array3D<double> HxIKb2;
	Array3D<double> HzIKb1;
	Array3D<double> HzIKb2;

	Array3D<double> EyJKt1;
	Array3D<double> EyJKt2;
	Array3D<double> EzJKt1;
	Array3D<double> EzJKt2;
	Array3D<double> HyJKt1;
	Array3D<double> HyJKt2;
	Array3D<double> HzJKt1;
	Array3D<double> HzJKt2;
	Array3D<double> EyJKb1;
	Array3D<double> EyJKb2;
	Array3D<double> EzJKb1;
	Array3D<double> EzJKb2;
	Array3D<double> HyJKb1;
	Array3D<double> HyJKb2;
	Array3D<double> HzJKb1;
	Array3D<double> HzJKb2;

	Array1D<double> RD1;
	Array1D<double> RD2;

	Array1D<double> omega;
	Array1D<double> frequency;
	Array1D<double> kapa;
	Array1D<double> Cosine;
	Array1D<double> Sine;

	std::complex<double> NTheta;
	std::complex<double> NPhi;
	std::complex<double> LTheta;
	std::complex<double> LPhi;

	void EFldIJ();
	void EFldIK();
	void EFldJK();
	void HFldIJ();
	void HFldIK();
	void HFldJK();

	double CalculateNLphasors(int f, int Theta, int Phi);
public:
	RadiationPatternFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();
	virtual bool IsElementConsistent();

	virtual ~RadiationPatternFDTDCore();
};

#endif /* RADIATIONPATTERNFDTDCORE_H_ */
