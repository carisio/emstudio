/*
 * FieldAtPointFDTDCore.cpp
 *
 *  Created on: 02/03/2012
 *      Author: Administrador
 */

#include "FieldAtPointFDTDCore.h"

#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"
#include "emstudio/core/results/FieldAtPathResult.h"


FieldAtPointFDTDCore::FieldAtPointFDTDCore() {
}

FieldAtPointFDTDCore::~FieldAtPointFDTDCore() {
}


ElementCoreSmartPointer FieldAtPointFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new FieldAtPointFDTDCore);
}

void FieldAtPointFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	FieldAtPointDTO* fieldAtPointDTO = static_cast<FieldAtPointDTO*>(elementDTOSmartPtr.get());

	dto = *fieldAtPointDTO;

}

void FieldAtPointFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	i = engine->GetGrid().GetXCell(dto.GetX());
	j = engine->GetGrid().GetYCell(dto.GetY());
	k = engine->GetGrid().GetZCell(dto.GetZ());

	cout << "FieldAtPointFDTDCore iniciando" << endl;
	cout << "i = " << i << endl;
	cout << "j = " << j << endl;
	cout << "k = " << k << endl;

	NFreq = dto.GetNFrequency();

	RD1 = Array1D<double>(NFreq,0.0);
	RD2 = Array1D<double>(NFreq,0.0);

	omega = Array1D<double>(NFreq,0.0);
	frequency = Array1D<double>(NFreq,0.0);

	ExR = Array1D<double>(NFreq,0.0);
	ExI = Array1D<double>(NFreq,0.0);
	EyR = Array1D<double>(NFreq,0.0);
	EyI = Array1D<double>(NFreq,0.0);
	EzR = Array1D<double>(NFreq,0.0);
	EzI = Array1D<double>(NFreq,0.0);
	HxR = Array1D<double>(NFreq,0.0);
	HxI = Array1D<double>(NFreq,0.0);
	HyR = Array1D<double>(NFreq,0.0);
	HyI = Array1D<double>(NFreq,0.0);
	HzR = Array1D<double>(NFreq,0.0);
	HzI = Array1D<double>(NFreq,0.0);
	Mag_E = Array1D<double>(NFreq,0.0);
	Mag_Ex = Array1D<double>(NFreq,0.0);
	Mag_Ey = Array1D<double>(NFreq,0.0);
	Mag_Ez = Array1D<double>(NFreq,0.0);
	Phase_Ex = Array1D<double>(NFreq,0.0);
	Phase_Ey = Array1D<double>(NFreq,0.0);
	Phase_Ez = Array1D<double>(NFreq,0.0);
	Mag_H = Array1D<double>(NFreq,0.0);
	Mag_Hx = Array1D<double>(NFreq,0.0);
	Mag_Hy = Array1D<double>(NFreq,0.0);
	Mag_Hz = Array1D<double>(NFreq,0.0);
	Phase_Hx = Array1D<double>(NFreq,0.0);
	Phase_Hy = Array1D<double>(NFreq,0.0);
	Phase_Hz = Array1D<double>(NFreq,0.0);

	double FInit = dto.GetInitialFrequency();
	double FStep = dto.GetFrequencyStep();
	for (int f = 0; f < NFreq; f++) {
		omega[f] = 2.0*PI*(FInit + f*FStep);
		frequency[f] = FInit + f*FStep;
	}

	time = Array1D<double>(engine->GetTimeSteps(),0.0);

	if (dto.IsShowTimeResponse()) {
		showTimeResponse = true;
		ExT = Array1D<double>(engine->GetTimeSteps(),0.0);
		EyT = Array1D<double>(engine->GetTimeSteps(),0.0);
		EzT = Array1D<double>(engine->GetTimeSteps(),0.0);
		HxT = Array1D<double>(engine->GetTimeSteps(),0.0);
		HyT = Array1D<double>(engine->GetTimeSteps(),0.0);
		HzT = Array1D<double>(engine->GetTimeSteps(),0.0);
		timeE = Array1D<double>(engine->GetTimeSteps(),0.0);
		timeH = Array1D<double>(engine->GetTimeSteps(),0.0);
	} else {
		showTimeResponse = false;
	}
}

void FieldAtPointFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

//	cout << "FieldAtPoint. engine->GetEy(i,j,k) = " << engine->GetEz(i,j,k) << endl;
//	cout << "NFreq = " << NFreq << endl;
	for (int f = 0; f < NFreq; f++) {
		RD1[f] = cos(omega[f]*t);
		RD2[f] = sin(omega[f]*t);
		ExR[f] += engine->GetEx(i,j,k)*RD1[f];
		ExI[f] += engine->GetEx(i,j,k)*RD2[f];
		EyR[f] += engine->GetEy(i,j,k)*RD1[f];
		EyI[f] += engine->GetEy(i,j,k)*RD2[f];
		EzR[f] += engine->GetEz(i,j,k)*RD1[f];
		EzI[f] += engine->GetEz(i,j,k)*RD2[f];
	}

	if (showTimeResponse) {
		double iterationNumber = engine->GetCurrentInterationNumber();
		timeE[iterationNumber] = t;

		ExT[iterationNumber] = engine->GetEx(i,j,k);
		EyT[iterationNumber] = engine->GetEy(i,j,k);
		EzT[iterationNumber] = engine->GetEz(i,j,k);
	}
//	cout << "FieldAtPointFDTDCore terminou" << endl;
}

void FieldAtPointFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	for (int f = 0; f < NFreq; f++) {
		RD1[f] = cos(omega[f]*t);
		RD2[f] = sin(omega[f]*t);

		HxR[f] += engine->GetHx(i,j,k)*RD1[f];
		HxI[f] += engine->GetHx(i,j,k)*RD2[f];
		HyR[f] += engine->GetHy(i,j,k)*RD1[f];
		HyI[f] += engine->GetHy(i,j,k)*RD2[f];
		HzR[f] += engine->GetHz(i,j,k)*RD1[f];
		HzI[f] += engine->GetHz(i,j,k)*RD2[f];
	}

	if (showTimeResponse) {
		double iterationNumber = engine->GetCurrentInterationNumber();
		timeH[iterationNumber] = t;

		HxT[iterationNumber] = engine->GetHx(i,j,k);
		HyT[iterationNumber] = engine->GetHy(i,j,k);
		HzT[iterationNumber] = engine->GetHz(i,j,k);
	}

}

void FieldAtPointFDTDCore::SimulationWillFinish() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	complex<double>Field1;
	complex<double>Field2;
	complex<double>Field3;
	complex<double>Field4;
	complex<double>Field5;
	complex<double>Field6;

	int TimeSteps = engine->GetTimeSteps();

	for (int f = 0; f < NFreq; f++) {
		Field1 = complex<double>(ExR[f]/TimeSteps,ExI[f]/TimeSteps);
		Field2 = complex<double>(EyR[f]/TimeSteps,EyI[f]/TimeSteps);
		Field3 = complex<double>(EzR[f]/TimeSteps,EzI[f]/TimeSteps);
		Field4 = complex<double>(HxR[f]/TimeSteps,HxI[f]/TimeSteps);
		Field5 = complex<double>(HyR[f]/TimeSteps,HyI[f]/TimeSteps);
		Field6 = complex<double>(HzR[f]/TimeSteps,HzI[f]/TimeSteps);

		Mag_Ex[f] = abs(Field1);
		Mag_Ey[f] = abs(Field2);
		Mag_Ez[f] = abs(Field3);
		Mag_E[f] = sqrt(abs(Field1)*abs(Field1)+abs(Field2)*abs(Field2)+abs(Field3)*abs(Field3));

		Mag_Hx[f] = abs(Field4)/ETA0;
		Mag_Hy[f] = abs(Field5)/ETA0;
		Mag_Hz[f] = abs(Field6)/ETA0;
		Mag_H[f] = sqrt(abs(Field4)*abs(Field4)+abs(Field5)*abs(Field5)+abs(Field6)*abs(Field6));

		Phase_Ex[f] = -atan2(ExR[f], ExI[f]);
		Phase_Ey[f] = -atan2(EyR[f], EyI[f]);
		Phase_Ez[f] = -atan2(EzR[f], EzI[f]);

		Phase_Hx[f] = -atan2(HxR[f], HxI[f]);
		Phase_Hy[f] = -atan2(HyR[f], HyI[f]);
		Phase_Hz[f] = -atan2(HzR[f], HzI[f]);
	}
}
bool FieldAtPointFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetX();
	ymin = dto.GetY();
	zmin = dto.GetZ();
	xmax = dto.GetX();
	ymax = dto.GetY();
	zmax = dto.GetZ();
	return true;
}
bool FieldAtPointFDTDCore::HasResults() {
	return true;
}

ElementResults FieldAtPointFDTDCore::GetElementsResults() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int NFreq = dto.GetNFrequency();
	int steps = engine->GetTimeSteps();

	/* Pega o rótulo para a variável de frequência, e seu multiplicador */
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;
	wxString frequencyName("Frequency (");
	frequencyName.Append(normalized_frequency_label).Append(")");

	double normalized_space_factor = engine->GetUnits()->GetUserDefinedSpaceUnit().second;

	/* Rótulo das linhas */
	GenericTable::ColumnDataRepresentation frequencyData;
	GenericTable::ColumnDataRepresentation ExAmp;
	GenericTable::ColumnDataRepresentation ExPhase;
	GenericTable::ColumnDataRepresentation EyAmp;
	GenericTable::ColumnDataRepresentation EyPhase;
	GenericTable::ColumnDataRepresentation EzAmp;
	GenericTable::ColumnDataRepresentation EzPhase;
	GenericTable::ColumnDataRepresentation HxAmp;
	GenericTable::ColumnDataRepresentation HxPhase;
	GenericTable::ColumnDataRepresentation HyAmp;
	GenericTable::ColumnDataRepresentation HyPhase;
	GenericTable::ColumnDataRepresentation HzAmp;
	GenericTable::ColumnDataRepresentation HzPhase;

	for (int f = 0; f < NFreq; f++) {
		frequencyData.push_back(frequency[f]/normalized_frequency_factor);
		ExAmp.push_back(Mag_Ex[f]);
		EyAmp.push_back(Mag_Ey[f]);
		EzAmp.push_back(Mag_Ez[f]);
		ExPhase.push_back(Phase_Ex[f]);
		EyPhase.push_back(Phase_Ey[f]);
		EzPhase.push_back(Phase_Ez[f]);
		HxAmp.push_back(Mag_Hx[f]);
		HyAmp.push_back(Mag_Hy[f]);
		HzAmp.push_back(Mag_Hz[f]);
		HxPhase.push_back(Phase_Hx[f]);
		HyPhase.push_back(Phase_Hy[f]);
		HzPhase.push_back(Phase_Hz[f]);
	}

	/* Carrega o nome do resultado */
	wxString resultName = "Frequency. At (";
	resultName.Append(Converter::DoubleToFormattedString(dto.GetX()/normalized_space_factor, 2)).
			Append(", ").Append(Converter::DoubleToFormattedString(dto.GetY()/normalized_space_factor, 2)).
			Append(", ").Append(Converter::DoubleToFormattedString(dto.GetZ()/normalized_space_factor, 2)).
			Append(")");

	FieldAtPathResult* fapr = new FieldAtPathResult(resultName);
	fapr->SetField(frequencyData, frequencyName, ExAmp, EyAmp, EzAmp, HxAmp, HzAmp, HzAmp,
			ExPhase, EyPhase, EzPhase, HxPhase, HzPhase, HzPhase);

	/* Adiciona o resultado na lista */
	list<ResultSmartPointer> result;
	result.push_back(ResultSmartPointer(fapr));

	if (showTimeResponse) {
		wxString normalized_time_label = engine->GetUnits()->GetUserDefinedTimeUnit().first;
		double normalized_time_factor = engine->GetUnits()->GetUserDefinedTimeUnit().second;

		GenericTable::ColumnDataRepresentation timeData;
		GenericTable::ColumnDataRepresentation exTData;
		GenericTable::ColumnDataRepresentation eyTData;
		GenericTable::ColumnDataRepresentation ezTData;
		GenericTable::ColumnDataRepresentation hxTData;
		GenericTable::ColumnDataRepresentation hyTData;
		GenericTable::ColumnDataRepresentation hzTData;

		for (int T = 0; T < steps; T++) {
			timeData.push_back(timeE[T]/normalized_time_factor);
			exTData.push_back(ExT[T]);
			eyTData.push_back(EyT[T]);
			ezTData.push_back(EzT[T]);
			hxTData.push_back(HxT[T]);
			hyTData.push_back(HyT[T]);
			hzTData.push_back(HzT[T]);
		}

		/* Cria uma tabela para campo elétrico e uma para magnético */
		GenericTable resultsE_t;
		GenericTable resultsH_t;

		/* Preenche as tabelas */
		resultsE_t.AddColumn(timeData); resultsE_t.AddColumn(exTData); resultsE_t.AddColumn(eyTData); resultsE_t.AddColumn(ezTData);
		resultsH_t.AddColumn(timeData); resultsH_t.AddColumn(hxTData); resultsH_t.AddColumn(hyTData); resultsH_t.AddColumn(hzTData);

		/* Adiciona o rótulo das colunas */
		wxString timeName("Time (");
		timeName.Append(normalized_time_label).Append(")");

		vector<wxString> labelTableE;
		vector<wxString> labelTableH;

		labelTableE.push_back(timeName); labelTableE.push_back("Ex (V/m)"); labelTableE.push_back("Ey (V/m)"); labelTableE.push_back("Ez (V/m)");
		labelTableH.push_back(timeName); labelTableH.push_back("Hx (V/m)"); labelTableH.push_back("Hy (V/m)"); labelTableH.push_back("Hz (V/m)");
		resultsE_t.SetColumnsLabel(labelTableE);
		resultsH_t.SetColumnsLabel(labelTableH);

		BoolWrapper canBeInterpretedAsChart; canBeInterpretedAsChart.SetValue(true);
		result.push_back(ResultSmartPointer(new TableResult("Time (E)", resultsE_t, canBeInterpretedAsChart)));
		result.push_back(ResultSmartPointer(new TableResult("Time (H)", resultsH_t, canBeInterpretedAsChart)));
	}

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}
