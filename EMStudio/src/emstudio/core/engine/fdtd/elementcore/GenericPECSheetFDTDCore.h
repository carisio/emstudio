/*
 * GenericPECSheetFDTDCore.h
 *
 *  Created on: 16/04/2013
 *      Author: Leandro
 */

#ifndef GENERICPECSHEETFDTDCORE_H_
#define GENERICPECSHEETFDTDCORE_H_

#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "FDTDElementCore.h"
#include "emstudio/dto/fdtdapp/GenericPECSheetDTO.h"
#include <vector>
using namespace::std;

class GenericPECSheetFDTDCore : public FDTDElementCore {
private:
	GenericPECSheetDTO dto;

	/* Índices onde a PEC está inserida */
	int cutAtIndex;
	vector<pair<int, int> > gridIndexEx;
	vector<pair<int, int> > gridIndexEy;
	vector<pair<int, int> > gridIndexEz;

	void AddPointToVector(vector<pair<int, int> >& vec, int coord1, int coord2);

	/* Valores externos em que a PEC está inserida. Essas variáveis são utilizadas apenas para preencher o gridIndex mais rápido, sem ter que pesquisar to_do o grid */
	double coord1Min, coord2Min, coord1Max, coord2Max;

	/* Embora o nome da função está escrito x, y, pode ser utilizado para qualquer par */
	bool IsInside(double x, double y);
	void CrossLine(double x, double y, double v1_x, double v1_y, double v2_x, double v2_y, bool& cross, bool& atTheLine);
	void SortMinMax(double& min, double& max);
public:
	GenericPECSheetFDTDCore();
	virtual ~GenericPECSheetFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr);

	virtual void SimulationWillStart();
	virtual void ElectricFieldsChanged(double t);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsElementConsistent();
};

#endif /* GENERICPECSHEETFDTDCORE_H_ */
