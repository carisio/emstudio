/*
 * DeltaGapFDTDCore.cpp
 *
 *  Created on: 07/11/2011
 *      Author: leandrocarisio
 */

#include "DeltaGapFDTDCore.h"

#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"

#include "wx/log.h"

#include <iostream>
using namespace::std;

DeltaGapFDTDCore::DeltaGapFDTDCore() {

}

DeltaGapFDTDCore::~DeltaGapFDTDCore() {

}

ElementCoreSmartPointer DeltaGapFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new DeltaGapFDTDCore);
}

void DeltaGapFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	DeltaGapDTO* deltaGapDTO = static_cast<DeltaGapDTO*>(elementDTOSmartPtr.get());

	dto = *deltaGapDTO;
}

void DeltaGapFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	i = engine->GetGrid().GetXCell(dto.GetX());
	j = engine->GetGrid().GetYCell(dto.GetY());
	k = engine->GetGrid().GetZCell(dto.GetZ());

	int orientation = dto.GetOrientation().GetValue();
	if (orientation == X)
		deltaS = engine->GetGrid().GetDx(i);
	else if (orientation == Y)
		deltaS = engine->GetGrid().GetDy(j);
	else if (orientation == Z)
		deltaS = engine->GetGrid().GetDz(k);

//	inv_deltaS = 1.0/deltaS;

	time = Array1D<double>(engine->GetTimeSteps(),0.0);
	excitationValue = Array1D<double>(engine->GetTimeSteps(),0.0);
	vOut = Array1D<double>(engine->GetTimeSteps(),0.0);
	iOut = Array1D<double>(engine->GetTimeSteps(),0.0);
	c_times_dt = SPEED_OF_LIGHT_VACUUM * engine->GetDeltaT();
	En = 0.;
	int Nfreq = dto.GetNFrequency();

	RD1 = Array1D<double>(Nfreq,0.0);
	RD2 = Array1D<double>(Nfreq,0.0);
	VF1 = Array1D<double>(Nfreq,0.0);
	VF2 = Array1D<double>(Nfreq,0.0);
	IF1 = Array1D<double>(Nfreq,0.0);
	IF2 = Array1D<double>(Nfreq,0.0);
	Zout1 = Array1D<double>(Nfreq,0.0);
	Zout2 = Array1D<double>(Nfreq,0.0);

	omega = Array1D<double>(Nfreq,0.0);
	frequency = Array1D<double>(Nfreq,0.0);
	double FInit = dto.GetInitialFrequency();
	double FStep = dto.GetFrequencyStep();
	for (int f = 0; f < Nfreq; f++) {
		omega[f] = 2.0*PI*(FInit + f*FStep);
		frequency[f] = FInit + f*FStep;
	}

	dto.GetExcitation().Init();
}

void DeltaGapFDTDCore::DFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());;

	double sourceValue = dto.GetExcitation().GetExcitationValue(t);
	int T = engine->GetCurrentInterationNumber();
	excitationValue[T] = sourceValue;
	int orientation = dto.GetOrientation().GetValue();

	double C1, value;
//	double Rs = dto.GetResistance();

//	if (!dto.IsResistiveSource()) {
		if (orientation == X) {
			engine->SetDx(i, j, k, -sourceValue/deltaS);
			vOut[T] = sourceValue;
		} else if (orientation == Y) {
			engine->SetDy(i, j, k, -sourceValue/deltaS);
			vOut[T] = sourceValue;
		} else if (orientation == Z) {
			engine->SetDz(i, j, k, -sourceValue/deltaS);
			vOut[T] = sourceValue;
		}
//	} else {
//		if (orientation == X) {
//			C1 = c_times_dt*deltaS/(2*Rs*engine->GetGrid().GetDy(j)*engine->GetGrid().GetDz(k));
//			value = (1-C1)/(1+C1)*En + (c_times_dt/(1+C1)/ETA0)*((engine->GetHz(i, j, k) -
//					engine->GetHz(i,j-1,k))/engine->GetGrid().GetDy(j) -
//					(engine->GetHy(i,j,k) - engine->GetHy(i,j,k-1))/engine->GetGrid().GetDz(k)) +
//					(2*C1/deltaS/(1+C1))*sourceValue;
//			engine->SetDx(i, j, k, value);
//			En = value;
//			vOut[T] = -value*deltaS;
//		}
//		else if (orientation == Y) {
//			C1 = c_times_dt*deltaS/(2*Rs*engine->GetGrid().GetDx(i)*engine->GetGrid().GetDz(k));
//			value = (1-C1)/(1+C1)*En + (c_times_dt/(1+C1)/ETA0)*((engine->GetHx(i, j, k) -
//					engine->GetHx(i,j,k-1))/engine->GetGrid().GetDz(k) -
//					(engine->GetHz(i,j,k) - engine->GetHz(i-1,j,k))/engine->GetGrid().GetDx(i)) +
//					(2*C1/deltaS/(1+C1))*sourceValue;
//			engine->SetDy(i, j, k, value);
//			En = value;
//			vOut[T] = -value*deltaS;
//		} else if (orientation == Z) {
//			C1 = c_times_dt*deltaS/(2*Rs*engine->GetGrid().GetDx(i)*engine->GetGrid().GetDy(j));
//			value = (1-C1)/(1+C1)*En + (c_times_dt/(1+C1)/ETA0)*((engine->GetHy(i, j, k) -
//					engine->GetHy(i-1,j,k))/engine->GetGrid().GetDx(i) -
//					(engine->GetHx(i,j,k) - engine->GetHx(i,j-1,k))/engine->GetGrid().GetDy(j)) +
//					(2*C1/deltaS/(1+C1))*sourceValue;
//			engine->SetDz(i, j, k, value);
//			En = value;
//			vOut[T] = -value*deltaS;
//		}
//	}

	time[T] = t;

	int NFreq = dto.GetNFrequency();
	for (int f = 0; f < NFreq; f++)	{
		RD1[f] = cos(omega[f]*t);
		RD2[f] = sin(omega[f]*t);
		VF1[f] += vOut[T]*RD1[f];
		VF2[f] += vOut[T]*RD2[f];
	}

}

void DeltaGapFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());;
	int orientation = dto.GetOrientation().GetValue();

	double I = 0;
	if (orientation == Z) {
		I =  (engine->GetHx(i, j-1, k) -
			engine->GetHx(i, j, k))*engine->GetGrid().GetDx(i) +
			(engine->GetHy(i, j, k) -
			engine->GetHy(i-1, j, k))*engine->GetGrid().GetDy(j);
	} else if (orientation == X) {
		I =  (engine->GetHz(i, j, k) -
			engine->GetHz(i, j-1, k))*engine->GetGrid().GetDz(k) +
			(engine->GetHy(i, j, k-1) -
			engine->GetHy(i, j, k))*engine->GetGrid().GetDy(j);
	} else if (orientation == Y) {
		I =  (engine->GetHx(i, j, k) -
			engine->GetHx(i, j, k-1))*engine->GetGrid().GetDx(i) +
			(engine->GetHz(i-1, j, k) -
			engine->GetHz(i, j, k))*engine->GetGrid().GetDz(k);
	}

	int T = engine->GetCurrentInterationNumber();
	int NFreq = dto.GetNFrequency();
	iOut[T] = I/ETA0;
	for (int f = 0; f < NFreq; f++)
	{
	  RD1[f] = cos(omega[f]*t);
	  RD2[f] = sin(omega[f]*t);
	  IF1[f] += iOut[T]*RD1[f];
	  IF2[f] += iOut[T]*RD2[f];
	}
}

void DeltaGapFDTDCore::SimulationWillFinish() {
//	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	complex<double> Vf;
	complex<double> If;
	complex<double> Zf;

	int NFreq = dto.GetNFrequency();
	wxString conteudoZOut1 = "";
	wxString conteudoZOut2 = "";
	for (int f = 0; f < NFreq; f++) {
		Vf = complex<double>(VF1[f],-VF2[f]);
		If = complex<double>(IF1[f],-IF2[f]);
		if (If == complex<double>(0,0)) If = complex<double>(1e-30,0);
		Zf = Vf/If;
		Zout1[f] = real(Zf);
		Zout2[f] = imag(Zf);

	}
}

bool DeltaGapFDTDCore::HasResults() {
	return true;
}

bool DeltaGapFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetX();
	ymin = dto.GetY();
	zmin = dto.GetZ();
	xmax = dto.GetX();
	ymax = dto.GetY();
	zmax = dto.GetZ();

	return true;
}
ElementResults DeltaGapFDTDCore::GetElementsResults() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int steps = engine->GetTimeSteps();
	int NFreq = dto.GetNFrequency();

	/* Pega o rótulo para as variáveis de tempo e frequência, e seu multiplicador */
	wxString normalized_time_label = engine->GetUnits()->GetUserDefinedTimeUnit().first;
	double normalized_time_factor = engine->GetUnits()->GetUserDefinedTimeUnit().second;
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;


	/* Rótulo das linhas */
	GenericTable::ColumnDataRepresentation timeData;
	GenericTable::ColumnDataRepresentation frequencyData;
	GenericTable::ColumnDataRepresentation vData;
	GenericTable::ColumnDataRepresentation iData;
	GenericTable::ColumnDataRepresentation zrData;
	GenericTable::ColumnDataRepresentation ziData;
	GenericTable::ColumnDataRepresentation excitationData;

	/* Monta a tabela */
	for (int T = 0; T < steps; T++) {
		timeData.push_back(time[T]/normalized_time_factor);
		vData.push_back(vOut[T]);
		iData.push_back(iOut[T]*1000);
		excitationData.push_back(excitationValue[T]);
	}

	for (int f = 0; f < NFreq; f++) {
		frequencyData.push_back(frequency[f]/normalized_frequency_factor);
		zrData.push_back(Zout1[f]);
		ziData.push_back(Zout2[f]);
	}
	/* Cria as tabelas e adiciona os dados */
	GenericTable vTable;
	GenericTable iTable;
	GenericTable zTable;
	GenericTable excitationTable;

	vTable.AddColumn(timeData);
	vTable.AddColumn(vData);

	iTable.AddColumn(timeData);
	iTable.AddColumn(iData);

	zTable.AddColumn(frequencyData);
	zTable.AddColumn(zrData);
	zTable.AddColumn(ziData);

	excitationTable.AddColumn(timeData);
	excitationTable.AddColumn(excitationData);

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(true);

	/* Rótulo das colunas da tabela */
	wxString timeColumnLabel("Time (");
	timeColumnLabel.Append(normalized_time_label).Append(")");
	wxString frequencyColumnLabel("Frequency (");
	frequencyColumnLabel.Append(normalized_frequency_label).Append(")");

	vector<wxString> outputVoltageColunsLabel;
	outputVoltageColunsLabel.push_back(timeColumnLabel);
	outputVoltageColunsLabel.push_back("Voltage (V)");
	vTable.SetColumnsLabel(outputVoltageColunsLabel);

	vector<wxString> outputCurrentColunsLabel;
	outputCurrentColunsLabel.push_back(timeColumnLabel);
	outputCurrentColunsLabel.push_back("Current (mA)");
	iTable.SetColumnsLabel(outputCurrentColunsLabel);

	vector<wxString> impedanceColunsLabel;
	impedanceColunsLabel.push_back(frequencyColumnLabel);
	impedanceColunsLabel.push_back("Impedance - real (ohms)");
	impedanceColunsLabel.push_back("Impedance - imaginary (ohms)");
	zTable.SetColumnsLabel(impedanceColunsLabel);

	vector<wxString> excitationColumnsLabel;
	excitationColumnsLabel.push_back(timeColumnLabel);
	excitationColumnsLabel.push_back("Excitation value");
	excitationTable.SetColumnsLabel(excitationColumnsLabel);

	list<ResultSmartPointer> result;
	result.push_back(ResultSmartPointer(new TableResult("Output voltage", vTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Output current", iTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Impedance", zTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Excitation", excitationTable, canBeInterpretedAsChart)));

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}
