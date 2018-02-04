/*
 * FDTDElementCore.cpp
 *
 *  Created on: 08/11/2011
 *      Author: leandrocarisio
 */

#include "FDTDElementCore.h"
#include "emstudio/dto/fdtdapp/ElementsWithFacetsDTO.h"
#include "emstudio/util/facet/Facet.h"
#include "emstudio/util/vector/Rvector3.h"

FDTDElementCore::FDTDElementCore() {

}

FDTDElementCore::~FDTDElementCore() {

}

void FDTDElementCore::SimulationWillStart() {

}
void FDTDElementCore::SimulationWillFinish() {

}
void FDTDElementCore::DFieldsChanged(double t) {

}
void FDTDElementCore::ElectricFieldsChanged(double t) {

}
void FDTDElementCore::MagneticFieldsChanged(double t) {

}
/**
 * Preenche as dimens�es m�ximas e m�nimas do elemento.
 * Retorna true se for um elemento que tem dimens�es e precisa estar dentro do grid, false caso cont�rio (ex.: diagrama de radia��o).
 */
bool FDTDElementCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	bool resultado = true;
	ElementsWithFacetsDTO* emstudioDTO = (static_cast<ElementsWithFacetsDTO*>(GetDTO().get()));
	if (emstudioDTO->HasFaces()) {
		FillDimensionsWithFacets(xmin, ymin, zmin, xmax, ymax, zmax);
	} else {
		resultado = false;
	}
	return resultado;
}

void FDTDElementCore::FillDimensionsWithFacets(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	Rvector3 max;
	Rvector3 min;

	ElementsWithFacetsDTO* emstudioDTO = (static_cast<ElementsWithFacetsDTO*>(GetDTO().get()));
	vector<Facet> v = emstudioDTO->GetFacets();
	FillBoundaries(v, min, max);
	xmin = min.X; ymin = min.Y; zmin = min.Z;
	xmax = max.X; ymax = max.Y; zmax = max.Z;
	cout << "xmin = " << xmin << endl;
	cout << "ymin = " << ymin << endl;
	cout << "zmin = " << zmin << endl;
	cout << "xmax = " << xmax << endl;
	cout << "ymax = " << ymax << endl;
	cout << "zmax = " << zmax << endl;
}
