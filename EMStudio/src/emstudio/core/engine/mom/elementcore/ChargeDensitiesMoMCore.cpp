/*
 * ChargeDensitiesMoMCore.cpp
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#include "ChargeDensitiesMoMCore.h"
#include "emstudio/core/engine/mom/MoMEngine.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"
#include "emstudio/core/results/SegmentInformationResult.h"

namespace mom {

ChargeDensitiesMoMCore::ChargeDensitiesMoMCore() {
}

ChargeDensitiesMoMCore::~ChargeDensitiesMoMCore() {
}

ElementCoreSmartPointer ChargeDensitiesMoMCore::NewElementCore() {
	return ElementCoreSmartPointer(new ChargeDensitiesMoMCore);
}

void ChargeDensitiesMoMCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	ChargeDensitiesDTO* chargeDensitiesDTO = static_cast<ChargeDensitiesDTO*>(elementDTOSmartPtr.get());

	dto = *chargeDensitiesDTO;
}

MoMElementCoreType ChargeDensitiesMoMCore::GetType() {
	return PROBES;
}
void ChargeDensitiesMoMCore::SetProbe() {
	// N�o precisa fazer nada, apenas buscar os resultados depois;
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());
	cout << "engine->GetNecContext()->pq_card(0,0,0,0);" << endl;
	engine->GetNecContext()->pq_card(0,0,0,0);

}

bool ChargeDensitiesMoMCore::HasResults() {
	return true;
}
wxString ChargeDensitiesMoMCore::GetNECCommand() {
	return "PQ 0\n";
}
ElementResults ChargeDensitiesMoMCore::GetElementsResults() {
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());
	int nfreq = engine->GetMoMDTO().GetNFrequency();

	std::pair<std::vector<int>, Segments> allSegmentsAndIndex = engine->GetAllSegmentsSortedBySequentialSegmentIndex();
	/* Pega o r�tulo para as vari�veis de frequ�ncia e seu multiplicador */
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;
	wxString normalized_space_label = engine->GetUnits()->GetUserDefinedSpaceUnit().first;
	double normalized_space_factor = engine->GetUnits()->GetUserDefinedSpaceUnit().second;

	GenericTable::ColumnDataRepresentation freqData;
	GenericTable::ColumnDataRepresentation tagData;
	GenericTable::ColumnDataRepresentation segmentData;
	GenericTable::ColumnDataRepresentation x1Data;
	GenericTable::ColumnDataRepresentation y1Data;
	GenericTable::ColumnDataRepresentation z1Data;
	GenericTable::ColumnDataRepresentation x2Data;
	GenericTable::ColumnDataRepresentation y2Data;
	GenericTable::ColumnDataRepresentation z2Data;
	GenericTable::ColumnDataRepresentation radiusData;
	GenericTable::ColumnDataRepresentation currentRData;
	GenericTable::ColumnDataRepresentation currentIData;

//	cout << "Chegou aqui" << endl;
	for (int i = 0; i < nfreq; i++) {
		nec_structure_currents* correntes = engine->GetNecContext()->get_structure_currents(i);
		vector<int> segmento = correntes->get_current_segment_number();
		vector<int> tag = correntes->get_current_segment_tag();
		vector<nec_float> theta = correntes->get_current_theta();
		vector<nec_float> phi = correntes->get_current_phi();
		vector<nec_complex> qDensity = correntes->get_q_density();
//		cout << "Frequ�ncia: " << correntes->get_frequency() << endl;
//		cout << "qDensity.size = " << qDensity.size() << endl;
//		cout << "segmento.size = " << segmento.size() << endl;
//		cout << "SEG\tTAG\tX\tY\tZ\tLength\tReal\tImag\tMag\tFase\n";
		for (size_t i = 0; i < segmento.size(); i++) {
			// Da forma como o programa funciona, h� um pareamento de allSegmentsAndIndex e das tags retornadas aqui
//			cout << "segmento[i] = " << segmento[i] << " \t " << "(allSegmentsAndIndex.first)[i] = " << (allSegmentsAndIndex.first)[i] << endl;
			Segment s = (allSegmentsAndIndex.second)[i];

			freqData.push_back(correntes->get_frequency()/normalized_frequency_factor);
			tagData.push_back(tag[i]);
			segmentData.push_back(segmento[i]);
			x1Data.push_back(s.GetP1().X / normalized_space_factor);
			y1Data.push_back(s.GetP1().Y / normalized_space_factor);
			z1Data.push_back(s.GetP1().Z / normalized_space_factor);
			x2Data.push_back(s.GetP2().X / normalized_space_factor);
			y2Data.push_back(s.GetP2().Y / normalized_space_factor);
			z2Data.push_back(s.GetP2().Z / normalized_space_factor);
			radiusData.push_back(s.GetRadius() / normalized_space_factor);
			currentRData.push_back(qDensity[i].real());
			currentIData.push_back(qDensity[i].imag());
		}
	}

	mom::SegmentInformationResult* sir = new mom::SegmentInformationResult("Charge density on segments");
	sir->SetData(freqData, x1Data, y1Data, z1Data, x2Data, y2Data, z2Data, radiusData, currentRData, "Charge density - real (C/m)", currentIData, "Charge density - imaginary (C/m)", normalized_frequency_label, normalized_space_label);

	list<ResultSmartPointer> result;
	result.push_back(ResultSmartPointer(sir));

	/* TESTE - S� PRA MOSTRAR TAMB�M OS N�MEROS DAS TAGS E SEGMENTOS! */
	GenericTable table;
	table.AddColumn(freqData);
	table.AddColumn(tagData);
	table.AddColumn(segmentData);
	table.AddColumn(x1Data);
	table.AddColumn(y1Data);
	table.AddColumn(z1Data);
	table.AddColumn(x2Data);
	table.AddColumn(y2Data);
	table.AddColumn(z2Data);
	table.AddColumn(radiusData);
	table.AddColumn(currentRData);
	table.AddColumn(currentIData);

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(false);

	/* Adiciona o r�tulo das colunas das tabelas */
	vector<wxString> colunsLabel;
	colunsLabel.push_back("Frequency (" + normalized_frequency_label + ")");
	colunsLabel.push_back("Tag");
	colunsLabel.push_back("Segmento");
	colunsLabel.push_back("X1 (" + normalized_space_label + ")");
	colunsLabel.push_back("Y1 (" + normalized_space_label + ")");
	colunsLabel.push_back("Z1 (" + normalized_space_label + ")");
	colunsLabel.push_back("X2 (" + normalized_space_label + ")");
	colunsLabel.push_back("Y2 (" + normalized_space_label + ")");
	colunsLabel.push_back("Z2 (" + normalized_space_label + ")");
	colunsLabel.push_back("Radius (" + normalized_space_label + ")");
	colunsLabel.push_back("Corrente real (A)");
	colunsLabel.push_back("Corrente imagin�ria (A)");
	table.SetColumnsLabel(colunsLabel);
//	result.push_back(ResultSmartPointer(new TableResult("Tabela tempor�ria com resultados", table, canBeInterpretedAsChart)));

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}

} /* namespace mom */
