/*
 * FieldAtPathFDTDCore.h
 *
 *  Created on: 21/03/2012
 *      Author: Leandro
 */

#ifndef FIELDATPATHFDTDCORE_H_
#define FIELDATPATHFDTDCORE_H_

#include <complex>
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/core/ElementCore.h"
#include "FDTDElementCore.h"
#include "emstudio/dto/fdtdapp/FieldAtPathDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"

class FieldAtPathFDTDCore : public FDTDElementCore {
private:
	FieldAtPathDTO dto;

	// Coordenadas de início e fim da linha
	int i1, j1, k1;
	int i2, j2, k2;
	// Número de amostras (cada amostra representa o campo em uma célula);
	int samples;

	int NFreq;
	double FIni, FStep;

	Array1D<double>RD1;
	Array1D<double>RD2;

	Array1D<double>omega;
	Array1D<double>frequency;
	Array1D<double>time;

	Array2D<double>Mag_Ex;
	Array2D<double>Mag_Ey;
	Array2D<double>Mag_Ez;
	Array2D<double>Mag_E;
	Array2D<double>Phase_Ex;
	Array2D<double>Phase_Ey;
	Array2D<double>Phase_Ez;
	Array2D<double>Mag_Hx;
	Array2D<double>Mag_Hy;
	Array2D<double>Mag_Hz;
	Array2D<double>Mag_H;
	Array2D<double>Phase_Hx;
	Array2D<double>Phase_Hy;
	Array2D<double>Phase_Hz;

	Array2D<double>ExR;
	Array2D<double>ExI;
	Array2D<double>EyR;
	Array2D<double>EyI;
	Array2D<double>EzR;
	Array2D<double>EzI;
	Array2D<double>HxR;
	Array2D<double>HxI;
	Array2D<double>HyR;
	Array2D<double>HyI;
	Array2D<double>HzR;
	Array2D<double>HzI;

	list<ResultSmartPointer> GetResultFromField(wxString resultName, wxString col1Label, wxString col2Label, wxString col3Label,
			Array2D<double>& col1, Array2D<double>& col2, Array2D<double>& col3);
public:
	FieldAtPathFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual ~FieldAtPathFDTDCore();
};

#endif /* FIELDATPATHFDTDCORE_H_ */
