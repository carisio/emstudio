/*
 * FieldAtPathFDTDCore.cpp
 *
 *  Created on: 21/03/2012
 *      Author: Leandro
 */

#include "FieldAtPathFDTDCore.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"
#include "emstudio/core/results/FieldAtPathResult.h"
#include "wx/log.h"

FieldAtPathFDTDCore::FieldAtPathFDTDCore() {

}

FieldAtPathFDTDCore::~FieldAtPathFDTDCore() {
}


ElementCoreSmartPointer FieldAtPathFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new FieldAtPathFDTDCore);
}

void FieldAtPathFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	FieldAtPathDTO* fieldAtPathDTO = static_cast<FieldAtPathDTO*>(elementDTOSmartPtr.get());

	dto = *fieldAtPathDTO;

}

void FieldAtPathFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	i1 = i2 = engine->GetGrid().GetXCell(dto.GetX());
	j1 = j2 = engine->GetGrid().GetYCell(dto.GetY());
	k1 = k2 = engine->GetGrid().GetZCell(dto.GetZ());

	if (dto.GetOrientation().GetValue() == X) {
		i2 = engine->GetGrid().GetXCell(dto.GetX()+dto.GetLength());
		samples = i2-i1+1;
	} else if (dto.GetOrientation().GetValue() == Y) {
		j2 = engine->GetGrid().GetYCell(dto.GetY()+dto.GetLength());
		samples = j2-j1+1;
	} else if (dto.GetOrientation().GetValue() == Z) {
		k2 = engine->GetGrid().GetZCell(dto.GetZ()+dto.GetLength());
		samples = k2-k1+1;
	}

	NFreq = dto.GetNFrequency();

	RD1 = Array1D<double>(NFreq,0.0);
	RD2 = Array1D<double>(NFreq,0.0);

	omega = Array1D<double>(NFreq,0.0);
	frequency = Array1D<double>(NFreq,0.0);

	ExR = Array2D<double>(NFreq,samples,0.0);
	ExI = Array2D<double>(NFreq,samples,0.0);
	EyR = Array2D<double>(NFreq,samples,0.0);
	EyI = Array2D<double>(NFreq,samples,0.0);
	EzR = Array2D<double>(NFreq,samples,0.0);
	EzI = Array2D<double>(NFreq,samples,0.0);
	HxR = Array2D<double>(NFreq,samples,0.0);
	HxI = Array2D<double>(NFreq,samples,0.0);
	HyR = Array2D<double>(NFreq,samples,0.0);
	HyI = Array2D<double>(NFreq,samples,0.0);
	HzR = Array2D<double>(NFreq,samples,0.0);
	HzI = Array2D<double>(NFreq,samples,0.0);
	Mag_E = Array2D<double>(NFreq,samples,0.0);
	Mag_Ex = Array2D<double>(NFreq,samples,0.0);
	Mag_Ey = Array2D<double>(NFreq,samples,0.0);
	Mag_Ez = Array2D<double>(NFreq,samples,0.0);
	Phase_Ex = Array2D<double>(NFreq,samples,0.0);
	Phase_Ey = Array2D<double>(NFreq,samples,0.0);
	Phase_Ez = Array2D<double>(NFreq,samples,0.0);
	Mag_H = Array2D<double>(NFreq,samples,0.0);
	Mag_Hx = Array2D<double>(NFreq,samples,0.0);
	Mag_Hy = Array2D<double>(NFreq,samples,0.0);
	Mag_Hz = Array2D<double>(NFreq,samples,0.0);
	Phase_Hx = Array2D<double>(NFreq,samples,0.0);
	Phase_Hy = Array2D<double>(NFreq,samples,0.0);
	Phase_Hz = Array2D<double>(NFreq,samples,0.0);


	double FInit = dto.GetInitialFrequency();
	double FStep = dto.GetFrequencyStep();
	for (int f = 0; f < NFreq; f++) {
		omega[f] = 2.0*PI*(FInit + f*FStep);
		frequency[f] = FInit + f*FStep;
	}

	time = Array1D<double>(engine->GetTimeSteps(),0.0);
	cout << "i1 = " << i1 << ", i2 = " << i2 << ", NxTOTAL = " << engine->GetGrid().GetNxTOTAL() << endl;
	cout << "j1 = " << j1 << ", j2 = " << j2 << ", NyTOTAL = " << engine->GetGrid().GetNyTOTAL() << endl;
	cout << "k1 = " << k1 << ", k2 = " << k2 << ", NzTOTAL = " << engine->GetGrid().GetNzTOTAL() << endl;
}

void FieldAtPathFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int l = 0;

	for (int i = i1; i <= i2; i++) {
		for (int j = j1; j <= j2; j++) {
			for (int k = k1; k <= k2; k++) {
				if (dto.GetOrientation().GetValue() == Z) {
					l = k-k1;
				}
				else if (dto.GetOrientation().GetValue() == Y) {
					l = j-j1;
				}
				else if (dto.GetOrientation().GetValue() == X) {
					l = i-i1;
				}
				for (int f = 0; f < NFreq; f++) {
					RD1[f] = cos(omega[f]*t);
					RD2[f] = sin(omega[f]*t);

					ExR[f][l] += engine->GetEx(i,j,k)*RD1[f];
					ExI[f][l] += engine->GetEx(i,j,k)*RD2[f];
					EyR[f][l] += engine->GetEy(i,j,k)*RD1[f];
					EyI[f][l] += engine->GetEy(i,j,k)*RD2[f];
					EzR[f][l] += engine->GetEz(i,j,k)*RD1[f];
					EzI[f][l] += engine->GetEz(i,j,k)*RD2[f];
				}
			}
		}
	}


}

void FieldAtPathFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	int l = 0;

	for (int i = i1; i <= i2; i++) {
		for (int j = j1; j <= j2; j++) {
			for (int k = k1; k <= k2; k++) {
				if (dto.GetOrientation().GetValue() == Z) {
					l = k-k1;
				}
				else if (dto.GetOrientation().GetValue() == Y) {
					l = j-j1;
				}
				else if (dto.GetOrientation().GetValue() == X) {
					l = i-i1;
				}
				for (int f = 0; f < NFreq; f++) {
					RD1[f] = cos(omega[f]*t);
					RD2[f] = sin(omega[f]*t);

					HxR[f][l] += engine->GetHx(i,j,k)*RD1[f];//Proj->Hx[i][j][k]*RD1[f];
					HxI[f][l] += engine->GetHx(i,j,k)*RD2[f];//Proj->Hx[i][j][k]*RD2[f];
					HyR[f][l] += engine->GetHy(i,j,k)*RD1[f];//Proj->Hy[i][j][k]*RD1[f];
					HyI[f][l] += engine->GetHy(i,j,k)*RD2[f];//Proj->Hy[i][j][k]*RD2[f];
					HzR[f][l] += engine->GetHz(i,j,k)*RD1[f];//Proj->Hz[i][j][k]*RD1[f];
					HzI[f][l] += engine->GetHz(i,j,k)*RD2[f];//Proj->Hz[i][j][k]*RD2[f];
				}
			}
		}
	}

}

void FieldAtPathFDTDCore::SimulationWillFinish() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	complex<double>Field1;
	complex<double>Field2;
	complex<double>Field3;
	complex<double>Field4;
	complex<double>Field5;
	complex<double>Field6;

	int TimeSteps = engine->GetTimeSteps();

	for (int f = 0; f < NFreq; f++) {
		for (int l = 0; l < samples; l++) {
			Field1 = complex<double>(ExR[f][l]/TimeSteps,-ExI[f][l]/TimeSteps);
			Field2 = complex<double>(EyR[f][l]/TimeSteps,-EyI[f][l]/TimeSteps);
			Field3 = complex<double>(EzR[f][l]/TimeSteps,-EzI[f][l]/TimeSteps);
			Field4 = complex<double>(HxR[f][l]/TimeSteps,-HxI[f][l]/TimeSteps);
			Field5 = complex<double>(HyR[f][l]/TimeSteps,-HyI[f][l]/TimeSteps);
			Field6 = complex<double>(HzR[f][l]/TimeSteps,-HzI[f][l]/TimeSteps);

			Mag_Ex[f][l] = abs(Field1);
			Mag_Ey[f][l] = abs(Field2);
			Mag_Ez[f][l] = abs(Field3);
			Mag_E[f][l] = sqrt(abs(Field1)*abs(Field1)+abs(Field2)*abs(Field2)+abs(Field3)*abs(Field3));

			Mag_Hx[f][l] = abs(Field4);
			Mag_Hy[f][l] = abs(Field5);
			Mag_Hz[f][l] = abs(Field6);
			Mag_H[f][l] = sqrt(abs(Field4)*abs(Field4)+abs(Field5)*abs(Field5)+abs(Field6)*abs(Field6));

			Phase_Ex[f][l] = -atan2(ExR[f][l], ExI[f][l]);
			Phase_Ey[f][l] = -atan2(EyR[f][l], EyI[f][l]);
			Phase_Ez[f][l] = -atan2(EzR[f][l], EzI[f][l]);

			Phase_Hx[f][l] = -atan2(HxR[f][l], HxI[f][l]);
			Phase_Hy[f][l] = -atan2(HyR[f][l], HyI[f][l]);
			Phase_Hz[f][l] = -atan2(HzR[f][l], HzI[f][l]);
		}
	}
}

bool FieldAtPathFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	int orientation = dto.GetOrientation().GetValue();
	xmin = dto.GetX();
	ymin = dto.GetY();
	zmin = dto.GetZ();
	xmax = dto.GetX();
	ymax = dto.GetY();
	zmax = dto.GetZ();

	if (orientation == X) {
		xmax += dto.GetLength();
	} else if (orientation == Y) {
		ymax += dto.GetLength();
	} else if (orientation == Z) {
		zmax += dto.GetLength();
	}
	return true;
}

bool FieldAtPathFDTDCore::HasResults() {
	return true;
}

ElementResults FieldAtPathFDTDCore::GetElementsResults() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid grid = engine->GetGrid();
	int NFreq = dto.GetNFrequency();

	/* Rótulos e fatores de normalização de frequência e espaço */
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;
	wxString normalized_space_label = engine->GetUnits()->GetUserDefinedSpaceUnit().first;
	double normalized_space_factor = engine->GetUnits()->GetUserDefinedSpaceUnit().second;

	/* Rótulo da coluna de posição*/
	wxString positionTitle = "Position";
	if (dto.GetOrientation().GetValue() == X) {
		positionTitle.Append(" - x axis (").Append(normalized_space_label).Append(")");
	} else if (dto.GetOrientation().GetValue() == Y) {
		positionTitle.Append(" - y axis (").Append(normalized_space_label).Append(")");
	} else if (dto.GetOrientation().GetValue() == Z) {
		positionTitle.Append(" - z axis (").Append(normalized_space_label).Append(")");
	}

	/* Dados da coluna de posição */
	GenericTable::ColumnDataRepresentation positionField;
	for (int len = 0; len < samples; len++) {
		if (dto.GetOrientation().GetValue() == X) {
			positionField.push_back(grid.GetAccumulatedDx(i1+len)/normalized_space_factor);
		} else if (dto.GetOrientation().GetValue() == Y) {
			positionField.push_back(grid.GetAccumulatedDy(j1+len)/normalized_space_factor);
		} else if (dto.GetOrientation().GetValue() == Z) {
			positionField.push_back(grid.GetAccumulatedDz(k1+len)/normalized_space_factor);
		}
	}	

	/* Itera nas frequências e cria uma tabela para cada frequência */
	list<ResultSmartPointer> result;
	for (int f = 0; f < NFreq; f++) {
		GenericTable::ColumnDataRepresentation colExMag;
		GenericTable::ColumnDataRepresentation colEyMag;
		GenericTable::ColumnDataRepresentation colEzMag;
		GenericTable::ColumnDataRepresentation colHxMag;
		GenericTable::ColumnDataRepresentation colHyMag;
		GenericTable::ColumnDataRepresentation colHzMag;
		GenericTable::ColumnDataRepresentation colExPhase;
		GenericTable::ColumnDataRepresentation colEyPhase;
		GenericTable::ColumnDataRepresentation colEzPhase;
		GenericTable::ColumnDataRepresentation colHxPhase;
		GenericTable::ColumnDataRepresentation colHyPhase;
		GenericTable::ColumnDataRepresentation colHzPhase;
		for (int l = 0; l < samples; l++) {
			// Primeira coluna é a frequencia
			colExMag.push_back(Mag_Ex[f][l]);
			colEyMag.push_back(Mag_Ey[f][l]);
			colEzMag.push_back(Mag_Ez[f][l]);
			colHxMag.push_back(Mag_Hx[f][l]);
			colHyMag.push_back(Mag_Hy[f][l]);
			colHzMag.push_back(Mag_Hz[f][l]);
			colExPhase.push_back(Phase_Ex[f][l]);
			colEyPhase.push_back(Phase_Ey[f][l]);
			colEzPhase.push_back(Phase_Ez[f][l]);
			colHxPhase.push_back(Phase_Hx[f][l]);
			colHyPhase.push_back(Phase_Hy[f][l]);
			colHzPhase.push_back(Phase_Hz[f][l]);
		}

		/* Carrega o nome do resultado */
		wxString resultNamePerFrequency = "f = ";
		resultNamePerFrequency.Append(Converter::DoubleToFormattedString(frequency[f]/normalized_frequency_factor, 2)).
				Append(" ").
				Append(normalized_frequency_label);

		FieldAtPathResult* fapr = new FieldAtPathResult(resultNamePerFrequency);
		fapr->SetField(positionField, positionTitle, colExMag, colEyMag, colEzMag, colHxMag, colHyMag, colHzMag,
				colExPhase, colEyPhase, colEzPhase, colHxPhase, colHyPhase, colHzPhase);

		/* Adiciona o resultado na lista */
		result.push_back(ResultSmartPointer(fapr));
	}

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);

//	list<ResultSmartPointer> Emag = GetResultFromField("E (Amplitude)", "Ex", "Ey", "Ez", Mag_Ex, Mag_Ey, Mag_Ez);
//	list<ResultSmartPointer> Ephase = GetResultFromField("E (Phase)", "Ex", "Ey", "Ez", Phase_Ex, Phase_Ey, Phase_Ez);
//	list<ResultSmartPointer> Hmag = GetResultFromField("H (Amplitude)", "Hx", "Hy", "Hz", Mag_Hx, Mag_Hy, Mag_Hz);
//	list<ResultSmartPointer> Hphase = GetResultFromField("H (Phase)", "Hx", "Hy", "Hz", Phase_Hx, Phase_Hy, Phase_Hz);
//
//	result.insert(result.end(), Emag.begin(), Emag.end());
//	result.insert(result.end(), Ephase.begin(), Ephase.end());
//	result.insert(result.end(), Hmag.begin(), Hmag.end());
//	result.insert(result.end(), Hphase.begin(), Hphase.end());
//
//	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}

list<ResultSmartPointer> FieldAtPathFDTDCore::GetResultFromField(wxString resultName, wxString col1Label, wxString col2Label, wxString col3Label,
		Array2D<double>& col1, Array2D<double>& col2, Array2D<double>& col3) {

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid grid = engine->GetGrid();
	int NFreq = dto.GetNFrequency();

	/* Rótulos e fatores de normalização de frequência e espaço */
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;
	wxString normalized_space_label = engine->GetUnits()->GetUserDefinedSpaceUnit().first;
	double normalized_space_factor = engine->GetUnits()->GetUserDefinedSpaceUnit().second;
	wxString positionTitle = "Position";

	if (dto.GetOrientation().GetValue() == X) {
		positionTitle.Append(" - x axis (").Append(normalized_space_label).Append(")");
	} else if (dto.GetOrientation().GetValue() == Y) {
		positionTitle.Append(" - y axis (").Append(normalized_space_label).Append(")");
	} else if (dto.GetOrientation().GetValue() == Z) {
		positionTitle.Append(" - z axis (").Append(normalized_space_label).Append(")");
	}

	/* Define o rótulo das colunas */
	vector<wxString> columnsLabel;
	columnsLabel.push_back(positionTitle);
	columnsLabel.push_back(col1Label);
	columnsLabel.push_back(col2Label);
	columnsLabel.push_back(col3Label);

	/* A primeira coluna representa a posição ao longo da linha */
	GenericTable::ColumnDataRepresentation lineData;
	for (int len = 0; len < samples; len++) {
		if (dto.GetOrientation().GetValue() == X) {
			lineData.push_back(grid.GetAccumulatedDx(i1+len)/normalized_space_factor);
		} else if (dto.GetOrientation().GetValue() == Y) {
			lineData.push_back(grid.GetAccumulatedDy(j1+len)/normalized_space_factor);
		} else if (dto.GetOrientation().GetValue() == Z) {
			lineData.push_back(grid.GetAccumulatedDz(k1+len)/normalized_space_factor);
		}
	}

	/* Itera nas frequências e cria uma tabela para cada frequência */
	list<ResultSmartPointer> results;
	for (int f = 0; f < NFreq; f++) {
		GenericTable table;
		table.SetColumnsLabel(columnsLabel);

		GenericTable::ColumnDataRepresentation col1Data;
		GenericTable::ColumnDataRepresentation col2Data;
		GenericTable::ColumnDataRepresentation col3Data;
		for (int l = 0; l < samples; l++) {
			// Primeira coluna é a frequencia
			col1Data.push_back(col1[f][l]);
			col2Data.push_back(col2[f][l]);
			col3Data.push_back(col3[f][l]);
		}
		table.AddColumn(lineData);
		table.AddColumn(col1Data);
		table.AddColumn(col2Data);
		table.AddColumn(col3Data);

		wxString resultNamePerFrequency = resultName;
		resultNamePerFrequency.Append(" - f = ").
				Append(Converter::DoubleToFormattedString(frequency[f]/normalized_frequency_factor, 2)).
				Append(" ").
				Append(normalized_frequency_label);
		BoolWrapper canBeInterpretedAsChart;
		canBeInterpretedAsChart.SetValue(true);

		results.push_back(ResultSmartPointer(new TableResult(resultNamePerFrequency, table, canBeInterpretedAsChart)));
	}

	return results;
}
