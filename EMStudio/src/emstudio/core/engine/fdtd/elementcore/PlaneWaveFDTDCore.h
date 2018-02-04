/*
 * PlaneWaveFDTDCore.h
 *
 *  Created on: 11/12/2011
 *      Author: Leandro
 */

#ifndef PLANEWAVEFDTDCORE_H_
#define PLANEWAVEFDTDCORE_H_

#include <complex>
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "FDTDElementCore.h"
#include "emstudio/core/ElementCore.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/tnt/tnt.h"
#include "emstudio/util/file/FileManager.h"
#include "emstudio/util/vector/Rvector3.h"
#include "wx/wx.h"
#include "emstudio/dto/fdtdapp/PlaneWaveDTO.h"

class PlaneWaveFDTDCore  : public FDTDElementCore {
private:
	PlaneWaveDTO dto;
	ElementCoreSmartPointer planeWaveImpl;

	Array1D<double> excitationValue;
	Array1D<double> time;
public:
	PlaneWaveFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual void SimulationWillStart();
	virtual void DFieldsChanged(double t);
	virtual void ElectricFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual bool IsElementConsistent();

	virtual ~PlaneWaveFDTDCore();
};

#endif /* PLANEWAVEFDTDCORE_H_ */
