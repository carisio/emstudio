/*
 * RadiationPatternMoMCore.cpp
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#include "RadiationPatternMoMCore.h"
#include "emstudio/core/engine/mom/MoMEngine.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/RadiationPatternResult.h"
#include "emstudio/core/results/SegmentInformationResult.h"
#include "emstudio/util/converters/Converter.h"

namespace mom {

RadiationPatternMoMCore::RadiationPatternMoMCore()
	: elementResults("", ""){

}

RadiationPatternMoMCore::~RadiationPatternMoMCore() {
}



ElementCoreSmartPointer RadiationPatternMoMCore::NewElementCore() {
	return ElementCoreSmartPointer(new RadiationPatternMoMCore);
}

void RadiationPatternMoMCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	RadiationPatternDTO* currentsDTO = static_cast<RadiationPatternDTO*>(elementDTOSmartPtr.get());

	dto = *currentsDTO;
}

MoMElementCoreType RadiationPatternMoMCore::GetType() {
	return EXECUTION_CARDS;
}
void RadiationPatternMoMCore::SetExecutionCard() {
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());
	int nfreq = dto.GetNFrequency();
	double frequencyStep = dto.GetFrequencyStep();
	double initialFrequency = dto.GetInitialFrequency();

	/****************************************************************/
	/* MONTA A ESTRUTURA PARA OS RESULTADOS. NO CASO DO RP, OS      */
	/* RESULTADOS JÁ DEVEM SER COLETADOS A MEDIDA QUE ESTÃO SENDO   */
	/* GERADOS                                                      */
	/****************************************************************/
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;
	/* A primeira coluna tem o ângulo em graus em que é feito o cálculo do diagrama de radiação */
	GenericTable::ColumnDataRepresentation degreeColumnPhi;
	for (int d = 0; d < 360; d++) {
		degreeColumnPhi.push_back(d);
	}
	GenericTable::ColumnDataRepresentation degreeColumnTheta;
	for (int d = 0; d < ((engine->GetMoMDTO().HasMedium1() || engine->GetMoMDTO().GetNumberOfRadials() > 0) ? 90 : 360); d++) {
		degreeColumnTheta.push_back(d);
	}
	/* O nome da primeira coluna é o ângulo. Das outras, é a frequencia em que o diagrama de radiação foi calculado */
	vector<wxString> columnsName;
	columnsName.push_back("Angle (degree)");
	for (int f = 0; f < nfreq; f++) {
		/* OBS.: OS RESULTADOS SÃO INFORMADOS NA CAMADA CORE EM MHZ */
		double frequency = (initialFrequency + f*frequencyStep) * 1e6;
		wxString str = Converter::DoubleToFormattedString(frequency/normalized_frequency_factor, 1);
		columnsName.push_back(str.Append(" ").Append(normalized_frequency_label));
	}

	/* Cria as tabelas. São 3, uma para cada plano. */
	GenericTable dataXYPlane;
	GenericTable dataYZPlane;
	GenericTable dataZXPlane;
	// Adiciona o rótulo das colunas
	dataXYPlane.SetColumnsLabel(columnsName);
	dataYZPlane.SetColumnsLabel(columnsName);
	dataZXPlane.SetColumnsLabel(columnsName);
	// Para cada tabela, adiciona a coluna contendo os ângulos
	dataXYPlane.AddColumn(degreeColumnPhi);
	dataYZPlane.AddColumn(degreeColumnTheta);
	dataZXPlane.AddColumn(degreeColumnTheta);
	// Adiciona as colunas para os 3 planos
	for (int f = 0; f < nfreq; f++) {
		dataXYPlane.AddColumn(GenericTable::ColumnDataRepresentation());
		dataYZPlane.AddColumn(GenericTable::ColumnDataRepresentation());
		dataZXPlane.AddColumn(GenericTable::ColumnDataRepresentation());
	}


	/****************************************************************/
	/* MANDA CALCULAR O RESULTADO E JÁ ADICIONA OS DADOS NO         */
	/* ELEMENTRESULT                                                */
	/****************************************************************/
	int mode = 0;

	if (engine->GetMoMDTO().HasMedium1() && !engine->GetMoMDTO().GetMedium1().IsPec()) {
		mode = 1;
	}
	if (engine->GetMoMDTO().GetNumberOfRadials() > 0) {
		mode = 4;
	}
	if (engine->GetMoMDTO().HasMedium2()) {
		if (engine->GetMoMDTO().IsLinearCliff()) {
			if (engine->GetMoMDTO().GetNumberOfRadials() > 0) {
				mode = 5;
			} else {
				mode = 2;
			}
		} else if (engine->GetMoMDTO().IsCircularCliff()) {
			if (engine->GetMoMDTO().GetNumberOfRadials() > 0) {
				mode = 6;
			} else {
				mode = 3;
			}
		}
	}
//	cout << "Mode = " << mode << endl;
//	cout << "Pegando status " << endl;
	InformSimulationStatusSmartPointer status = engine->GetInformSimulationStatusSmartPointer();
	cout << status.get() << "\t" << (status.get() != 0) << endl;
//	cout << "Calculando totalPercentagePerPlane" << endl;
	int nExecCards = engine->GetNumberOfExecutionCards();
//	cout << nExecCards << endl;
	int totalPercentagePerPlane = 100/(nExecCards+1)/3;
//	cout << totalPercentagePerPlane << endl;
	int n_theta;
	int n_phi;
	double theta_0;
	double phi_0;
	double theta_step = 1;
	double phi_step = 1;
	// Calcula o ganho no plano XY
	theta_0 = 90;
	phi_0 = 0;
	n_theta = 1;
	n_phi = 360;
	engine->InformStatus("Computing radiation pattern (XY plane)");
	cout << "engine->GetNecContext()->fr_card(0, " << nfreq << ", " << initialFrequency << ", " << frequencyStep << ");" << endl;
	engine->GetNecContext()->fr_card(0, nfreq, initialFrequency, frequencyStep);
	cout << "engine->GetNecContext()->rp_card(" << mode << ", " << n_theta << ", " << n_phi << ", 1, 0, 0, 0, " << theta_0 << ", " << phi_0 << ", " << theta_step << ", " << phi_step << ", 0, 0);" << endl;
	engine->GetNecContext()->rp_card(mode, n_theta, n_phi, 1, 0, 0, 0, theta_0, phi_0, theta_step, phi_step, 0, 0, status, status->GetPercentage(), totalPercentagePerPlane);
	necCommand = "";
	necCommand.Append("FR 0 ").Append(Converter::IntToFormattedString(nfreq)).Append(" 0 0 ").
			Append(Converter::DoubleToFormattedString(initialFrequency)).Append(" ").
			Append(Converter::DoubleToFormattedString(frequencyStep)).Append("\n");
	necCommand.Append("RP ").Append(Converter::IntToFormattedString(mode)).Append(" ").
			Append(Converter::IntToFormattedString(n_theta)).Append(" ").
			Append(Converter::IntToFormattedString(n_phi)).Append(" 1000 ").
			Append(Converter::DoubleToFormattedString(theta_0)).Append(" ").
			Append(Converter::DoubleToFormattedString(phi_0)).Append(" ").
			Append(Converter::DoubleToFormattedString(theta_step)).Append(" ").
			Append(Converter::DoubleToFormattedString(phi_step)).Append(" 0 0\n");
	if (status->SimulationWasCanceled())
		return;
	for (int f = 0; f < nfreq; f++) {
		nec_radiation_pattern* diagrama = engine->GetNecContext()->get_radiation_pattern(f);
		for (int p = 0; p < n_phi; p++) {
//			cout << nfreq << "\t" << p << "\t" << diagrama->get_power_gain_tot(0, p) << endl;
			// Usa f+1 porque a primeira coluna contém as informações sobre o ângulo em que o diagrama foi calculado.
			dataXYPlane.AppendInColumn(f+1, diagrama->get_power_gain_tot(0, p));
		}
	}
	// Calcula o ganho no plano YZ
	theta_0 = 0;
	phi_0 = 90;
	n_theta = (engine->GetMoMDTO().HasMedium1() || engine->GetMoMDTO().GetNumberOfRadials() > 0) ? 90 : 360;
	n_phi = 1;
//	cout << "Calculou 1" << endl;
	engine->InformStatus("Computing radiation pattern (YZ plane)");
	cout << "engine->GetNecContext()->fr_card(0, " << nfreq << ", " << initialFrequency << ", " << frequencyStep << ");" << endl;
	cout << "engine->GetNecContext()->rp_card(" << mode << ", " << n_theta << ", " << n_phi << ", 1, 0, 0, 0, " << theta_0 << ", " << phi_0 << ", " << theta_step << ", " << phi_step << ", 0, 0);" << endl;
	engine->GetNecContext()->fr_card(0, nfreq, initialFrequency, frequencyStep);
	engine->GetNecContext()->rp_card(mode, n_theta, n_phi, 1, 0, 0, 0, theta_0, phi_0, theta_step, phi_step, 0, 0, status, status->GetPercentage(), totalPercentagePerPlane);
	necCommand.Append("FR 0 ").Append(Converter::IntToFormattedString(nfreq)).Append(" 0 0 ").
			Append(Converter::DoubleToFormattedString(initialFrequency)).Append(" ").
			Append(Converter::DoubleToFormattedString(frequencyStep)).Append("\n");
	necCommand.Append("RP ").Append(Converter::IntToFormattedString(mode)).Append(" ").
			Append(Converter::IntToFormattedString(n_theta)).Append(" ").
			Append(Converter::IntToFormattedString(n_phi)).Append(" 1000 ").
			Append(Converter::DoubleToFormattedString(theta_0)).Append(" ").
			Append(Converter::DoubleToFormattedString(phi_0)).Append(" ").
			Append(Converter::DoubleToFormattedString(theta_step)).Append(" ").
			Append(Converter::DoubleToFormattedString(phi_step)).Append(" 0 0\n");
	if (status->SimulationWasCanceled())
		return;
	for (int f = 0; f < nfreq; f++) {
		nec_radiation_pattern* diagrama = engine->GetNecContext()->get_radiation_pattern(nfreq + f);
		for (int t = 0; t < n_theta; t++) {
			dataYZPlane.AppendInColumn(f+1, diagrama->get_power_gain_tot(t, 0));
		}
	}

	// Calcula o ganho no plano XZ
	theta_0 = 0;
	phi_0 = 0;
	n_theta = (engine->GetMoMDTO().HasMedium1() || engine->GetMoMDTO().GetNumberOfRadials() > 0) ? 90 : 360;
	n_phi = 1;
//	engine->InformStatus("Computing radiation pattern (XZ plane)");
	cout << "engine->GetNecContext()->fr_card(0, " << nfreq << ", " << initialFrequency << ", " << frequencyStep << ");" << endl;
	cout << "engine->GetNecContext()->rp_card(" << mode << ", " << n_theta << ", " << n_phi << ", 1, 0, 0, 0, " << theta_0 << ", " << phi_0 << ", " << theta_step << ", " << phi_step << ", 0, 0);" << endl;
	engine->GetNecContext()->fr_card(0, nfreq, initialFrequency, frequencyStep);
	engine->GetNecContext()->rp_card(mode, n_theta, n_phi, 1, 0, 0, 0, theta_0, phi_0, theta_step, phi_step, 0, 0, status, status->GetPercentage(), totalPercentagePerPlane);
	necCommand.Append("FR 0 ").Append(Converter::IntToFormattedString(nfreq)).Append(" 0 0 ").
			Append(Converter::DoubleToFormattedString(initialFrequency)).Append(" ").
			Append(Converter::DoubleToFormattedString(frequencyStep)).Append("\n");
	necCommand.Append("RP ").Append(Converter::IntToFormattedString(mode)).Append(" ").
			Append(Converter::IntToFormattedString(n_theta)).Append(" ").
			Append(Converter::IntToFormattedString(n_phi)).Append(" 1000 ").
			Append(Converter::DoubleToFormattedString(theta_0)).Append(" ").
			Append(Converter::DoubleToFormattedString(phi_0)).Append(" ").
			Append(Converter::DoubleToFormattedString(theta_step)).Append(" ").
			Append(Converter::DoubleToFormattedString(phi_step)).Append(" 0 0\n");
	if (status->SimulationWasCanceled())
		return;
	for (int f = 0; f < nfreq; f++) {
		nec_radiation_pattern* diagrama = engine->GetNecContext()->get_radiation_pattern(2*nfreq + f);
		for (int t = 0; t < n_theta; t++) {
			dataZXPlane.AppendInColumn(f+1, diagrama->get_power_gain_tot(t, 0));
		}
	}

	/* Cada linha é mostrada para um*/
	list<ResultSmartPointer> result;

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(true);

	Plane xy, yz, zx; xy.SetValue(XY); yz.SetValue(YZ); zx.SetValue(XZ);
	result.push_back(ResultSmartPointer(new RadiationPatternResult("XY Plane", dataXYPlane, canBeInterpretedAsChart, xy)));
	result.push_back(ResultSmartPointer(new RadiationPatternResult("YZ Plane", dataYZPlane, canBeInterpretedAsChart, yz)));
	result.push_back(ResultSmartPointer(new RadiationPatternResult("ZX Plane", dataZXPlane, canBeInterpretedAsChart, zx)));

	elementResults = ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}

bool RadiationPatternMoMCore::HasResults() {
	return true;
}
wxString RadiationPatternMoMCore::GetNECCommand() {
	return necCommand;
}
ElementResults RadiationPatternMoMCore::GetElementsResults() {
	return elementResults;
}

} /* namespace mom */
