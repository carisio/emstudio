/*
 * TransmissionLineMoMCore.cpp
 *
 *  Created on: 06/06/2014
 *      Author: leandrocarisio
 */

#include "TransmissionLineMoMCore.h"
#include "emstudio/core/engine/mom/MoMEngine.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"
#include "emstudio/util/converters/Converter.h"

namespace mom {

TransmissionLineMoMCore::TransmissionLineMoMCore() {
}

TransmissionLineMoMCore::~TransmissionLineMoMCore() {
}

ElementCoreSmartPointer TransmissionLineMoMCore::NewElementCore() {
	return ElementCoreSmartPointer(new TransmissionLineMoMCore);
}

void TransmissionLineMoMCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	TransmissionLineDTO* transmissionLineDTO = static_cast<TransmissionLineDTO*>(elementDTOSmartPtr.get());

	dto = *transmissionLineDTO;
}

MoMElementCoreType TransmissionLineMoMCore::GetType() {
	return CONNECTIONS;
}
void TransmissionLineMoMCore::SetConnection() {
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());

	int tagNumberPort1, tagNumberPort2;
	int segmentNumberPort1, segmentNumberPort2;
	int mthSegmentPort1, mthSegmentPort2;

	bool r1 = engine->FindClosestSegment(dto.GetPort1().X, dto.GetPort1().Y, dto.GetPort1().Z, tagNumberPort1, mthSegmentPort1, segmentNumberPort1);
	bool r2 = engine->FindClosestSegment(dto.GetPort2().X, dto.GetPort2().Y, dto.GetPort2().Z, tagNumberPort2, mthSegmentPort2, segmentNumberPort2);

	engine->GetNecContext()->tl_card(tagNumberPort1, mthSegmentPort1, tagNumberPort2, mthSegmentPort2, dto.GetImpedance(), dto.GetLength(),
			dto.GetAdmittanceRealPort1(), dto.GetAdmittanceImagPort1(), dto.GetAdmittanceRealPort2(), dto.GetAdmittanceImagPort2());
	necCommand = "TL ";
	necCommand.Append(Converter::IntToFormattedString(tagNumberPort1)).Append(" ").
			Append(Converter::IntToFormattedString(mthSegmentPort1)).Append(" ").
			Append(Converter::IntToFormattedString(tagNumberPort2)).Append(" ").
			Append(Converter::IntToFormattedString(mthSegmentPort2)).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetImpedance())).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetLength())).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetAdmittanceRealPort1())).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetAdmittanceImagPort1())).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetAdmittanceRealPort2())).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetAdmittanceImagPort2())).Append("\n");
	cout << "engine->GetNecContext()->tl_card(" << tagNumberPort1 << "," << mthSegmentPort1 << "," << tagNumberPort2 << "," << mthSegmentPort2<< "," << dto.GetImpedance() << "," << dto.GetLength() << "," <<
			dto.GetAdmittanceRealPort1() << "," << dto.GetAdmittanceImagPort1() << "," << dto.GetAdmittanceRealPort2() << "," << dto.GetAdmittanceImagPort2() << ");" << endl;
}
wxString TransmissionLineMoMCore::GetNECCommand() {
	return necCommand;
}
bool TransmissionLineMoMCore::HasResults() {
	cout << "TransmissionLineMoMCore::HasResults" << endl;
	return true;
}
ElementResults TransmissionLineMoMCore::GetElementsResults() {
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());
	int nfreq = engine->GetMoMDTO().GetNFrequency();

	/* Guarda os dados a que essa fonte se refere */
	int tagNumberPort1, tagNumberPort2;
	int segmentNumberPort1, segmentNumberPort2;
	int mthSegmentPort1, mthSegmentPort2;
	engine->FindClosestSegment(dto.GetPort1().X, dto.GetPort1().Y, dto.GetPort1().Z, tagNumberPort1, mthSegmentPort1, segmentNumberPort1);
	engine->FindClosestSegment(dto.GetPort2().X, dto.GetPort2().Y, dto.GetPort2().Z, tagNumberPort2, mthSegmentPort2, segmentNumberPort2);

	/* Pega o rótulo para as variáveis de frequência e seu multiplicador */
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;

	GenericTable::ColumnDataRepresentation frequencyData;
	GenericTable::ColumnDataRepresentation vrData;
	GenericTable::ColumnDataRepresentation viData;
	GenericTable::ColumnDataRepresentation zrData;
	GenericTable::ColumnDataRepresentation ziData;
	GenericTable::ColumnDataRepresentation currentrData;
	GenericTable::ColumnDataRepresentation currentiData;
	GenericTable::ColumnDataRepresentation yrData;
	GenericTable::ColumnDataRepresentation yiData;
	GenericTable::ColumnDataRepresentation powerData;

//	cout << "normalized_frequency_factor = " << normalized_frequency_factor << endl;
	for (int i = 0; i < nfreq; i++) {
		nec_structure_excitation* structureExcitation = engine->GetNecContext()->get_structure_excitation(i);
		frequencyData.push_back(structureExcitation->get_frequency()/normalized_frequency_factor); // Obs.: O NEC retorna os dados em Hz, apesar da entrada ser em MHz

		vector<int> tag = structureExcitation->get_tag();
		vector<int> segment = structureExcitation->get_segment();
		for (size_t j = 0; j < tag.size(); j++) {
//			cout << "pesquisando info da tag = " << tag[j] << " e segmento = " << segment[j] << " para freq = " << (structureExcitation->get_frequency()) << endl;
			// Procura nos resultados o elemento correto
			if (tag[j] == tagNumberPort2 && segment[j] == segmentNumberPort2) {
//				cout << "Achou dados para essa tag (" << tagNumberPort2 << ") e segmento (" << segmentNumberPort2 << ")" << endl;
				vector<nec_complex> impedance = structureExcitation->get_impedance();
				vector<nec_complex> voltage = structureExcitation->get_voltage();
				vector<nec_complex> current = structureExcitation->get_current();
				vector<nec_float> power = structureExcitation->get_power();
				nec_complex y = 1.0/(impedance[j]);
				zrData.push_back(impedance[j].real());
				ziData.push_back(impedance[j].imag());
				currentrData.push_back(current[j].real());
				currentiData.push_back(current[j].imag());
				yrData.push_back(y.real());
				yiData.push_back(y.imag());
				vrData.push_back(voltage[j].real());
				viData.push_back(voltage[j].imag());
				powerData.push_back(power[j]);
			}
		}
	}

	/* Cria as tabelas e adiciona os dados */
	GenericTable zTable;
	zTable.AddColumn(frequencyData);
	zTable.AddColumn(zrData);
	zTable.AddColumn(ziData);
	GenericTable iTable;
	iTable.AddColumn(frequencyData);
	iTable.AddColumn(currentrData);
	iTable.AddColumn(currentiData);
	GenericTable vTable;
	vTable.AddColumn(frequencyData);
	vTable.AddColumn(vrData);
	vTable.AddColumn(viData);
	GenericTable yTable;
	yTable.AddColumn(frequencyData);
	yTable.AddColumn(yrData);
	yTable.AddColumn(yiData);
	GenericTable powerTable;
	powerTable.AddColumn(frequencyData);
	powerTable.AddColumn(powerData);

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(true);

	/* Adiciona o rótulo das colunas das tabelas */
	wxString frequencyColumnLabel("Frequency (");
	frequencyColumnLabel.Append(normalized_frequency_label).Append(")");

	vector<wxString> impedanceColunsLabel;
	impedanceColunsLabel.push_back(frequencyColumnLabel);
	impedanceColunsLabel.push_back("Impedance - real (ohms)");
	impedanceColunsLabel.push_back("Impedance - imaginary (ohms)");
	zTable.SetColumnsLabel(impedanceColunsLabel);

	vector<wxString> currentColunsLabel;
	currentColunsLabel.push_back(frequencyColumnLabel);
	currentColunsLabel.push_back("Current - real (A)");
	currentColunsLabel.push_back("Current - imaginary (A)");
	iTable.SetColumnsLabel(currentColunsLabel);

	vector<wxString> voltageColunsLabel;
	voltageColunsLabel.push_back(frequencyColumnLabel);
	voltageColunsLabel.push_back("Voltage - real (V)");
	voltageColunsLabel.push_back("Voltage - imaginary (V)");
	vTable.SetColumnsLabel(voltageColunsLabel);

	vector<wxString> admittanceColunsLabel;
	admittanceColunsLabel.push_back(frequencyColumnLabel);
	admittanceColunsLabel.push_back("Admittance - real (mhos)");
	admittanceColunsLabel.push_back("Admittance - imaginary (mhos)");
	yTable.SetColumnsLabel(admittanceColunsLabel);

	vector<wxString> powerColunsLabel;
	powerColunsLabel.push_back(frequencyColumnLabel);
	powerColunsLabel.push_back("Power (W)");
	powerTable.SetColumnsLabel(powerColunsLabel);

	list<ResultSmartPointer> result;
	result.push_back(ResultSmartPointer(new TableResult("Voltage", vTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Current", iTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Impedance", zTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Admittance", yTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Power", powerTable, canBeInterpretedAsChart)));
	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}

} /* namespace mom */
