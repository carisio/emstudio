/*
 * FieldAtPlaneFDTDCore.h
 *
 *  Created on: 13/03/2013
 *      Author: leandrocarisio
 */

#ifndef FIELDATPLANEFDTDCORE_H_
#define FIELDATPLANEFDTDCORE_H_

#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "FDTDElementCore.h"
#include "emstudio/core/ElementCore.h"
#include "emstudio/dto/fdtdapp/FieldAtPlaneDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"

class FieldAtPlaneFDTDCore : public FDTDElementCore {
private:
	FieldAtPlaneDTO dto;

	// Coordenadas do plano onde o usuário quer ver o filme
	int imin, imax, jmin, jmax, kmin, kmax;

	/* Qual campo é para mostrar? */
	bool showEx;
	bool showEy;
	bool showEz;
	bool showHx;
	bool showHy;
	bool showHz;

	/* Uma amostra a cada sampleAtEach timesteps */
	int sampleAtEach;
	int currentSample;

	int dim1, dim2, dim3;
	Array3D<double> Ex;
	Array3D<double> Ey;
	Array3D<double> Ez;
	Array3D<double> Hx;
	Array3D<double> Hy;
	Array3D<double> Hz;

	Array1D<double> positionDimension1;
	Array1D<double> positionDimension2;
	Array1D<double> timeVector;
public:
	FieldAtPlaneFDTDCore();
	virtual ~FieldAtPlaneFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();
	virtual bool IsElementConsistent();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
};

#endif /* FIELDATPLANEFDTDCORE_H_ */
