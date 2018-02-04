/*
 * PlaneWaveFDTDCore.cpp
 *
 *  Created on: 11/12/2011
 *      Author: Leandro
 */

#include "PlaneWaveFDTDCore.h"
#include "PlaneWaveTFSFFDTDCore.h"
#include "PlaneWavePBCFDTDCore.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"

#include <iostream>
using namespace::std;

PlaneWaveFDTDCore::PlaneWaveFDTDCore() {

}

PlaneWaveFDTDCore::~PlaneWaveFDTDCore() {
}

ElementCoreSmartPointer PlaneWaveFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new PlaneWaveFDTDCore);
}

void PlaneWaveFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	PlaneWaveDTO* planeWaveDTO = static_cast<PlaneWaveDTO*>(elementDTOSmartPtr.get());
	dto = *planeWaveDTO;

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	bool usePBC = engine->GetFDTDDTO().GetABC().IsPeriodic(xNeg) || engine->GetFDTDDTO().GetABC().IsPeriodic(zNeg);

	if (usePBC) {
		planeWaveImpl = ElementCoreSmartPointer(new PlaneWavePBCFDTDCore);
	} else {
		planeWaveImpl = ElementCoreSmartPointer(new PlaneWaveTFSFFDTDCore);
	}
	planeWaveImpl->SetEngine(GetEngine());
	planeWaveImpl->Configure(elementDTOSmartPtr);
}
bool PlaneWaveFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(planeWaveImpl.get());
	return fdtdElementCorePtr->FillDimensions(xmin, ymin, zmin, xmax, ymax, zmax);
}

void PlaneWaveFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(planeWaveImpl.get());
	fdtdElementCorePtr->SimulationWillStart();

	time = Array1D<double>(engine->GetTimeSteps(),0.0);
	excitationValue = Array1D<double>(engine->GetTimeSteps(),0.0);
}

void PlaneWaveFDTDCore::DFieldsChanged(double t) {
	FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(planeWaveImpl.get());
	fdtdElementCorePtr->DFieldsChanged(t);

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double S;
	int T = engine->GetCurrentInterationNumber();
	S = dto.GetExcitation().GetExcitationValue(t);
	excitationValue[T] = S;
	time[T] = t;
}
void PlaneWaveFDTDCore::ElectricFieldsChanged(double t) {
	FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(planeWaveImpl.get());
	fdtdElementCorePtr->ElectricFieldsChanged(t);
}
void PlaneWaveFDTDCore::MagneticFieldsChanged(double t) {
	FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(planeWaveImpl.get());
	fdtdElementCorePtr->MagneticFieldsChanged(t);
}


void PlaneWaveFDTDCore::SimulationWillFinish() {
	FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(planeWaveImpl.get());
	fdtdElementCorePtr->SimulationWillFinish();
}

bool PlaneWaveFDTDCore::IsElementConsistent() {
	return planeWaveImpl->IsElementConsistent();
}

bool PlaneWaveFDTDCore::HasResults() {
	return true;
}

ElementResults PlaneWaveFDTDCore::GetElementsResults() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int steps = engine->GetTimeSteps();

	/* Pega o rótulo para as variáveis de tempo e frequência, e seu multiplicador */
	wxString normalized_time_label = engine->GetUnits()->GetUserDefinedTimeUnit().first;
	double normalized_time_factor = engine->GetUnits()->GetUserDefinedTimeUnit().second;

	/* Colunas */
	GenericTable::ColumnDataRepresentation excitationData;
	GenericTable::ColumnDataRepresentation timeData;

	/* Monta a tabela */
	for (int T = 0; T < steps; T++) {
		timeData.push_back(time[T]/normalized_time_factor);
		excitationData.push_back(excitationValue[T]);
	}

	/* Cria as tabelas e adiciona os dados */
	GenericTable excitationTable;

	excitationTable.AddColumn(timeData);
	excitationTable.AddColumn(excitationData);

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(true);

	/* Adiciona o rótulo das colunas das tabelas */
	wxString timeColumnLabel("Time (");
	timeColumnLabel.Append(normalized_time_label).Append(")");

	vector<wxString> excitationColumnsLabel;
	excitationColumnsLabel.push_back(timeColumnLabel);
	excitationColumnsLabel.push_back("Excitation value");
	excitationTable.SetColumnsLabel(excitationColumnsLabel);

	list<ResultSmartPointer> result;
	result.push_back(ResultSmartPointer(new TableResult("Excitation", excitationTable, canBeInterpretedAsChart)));

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}
