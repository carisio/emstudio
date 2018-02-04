/*
 * VoltageSourceMoMCore.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "VoltageSourceMoMCore.h"
#include "emstudio/core/engine/mom/MoMEngine.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"
#include "emstudio/util/converters/Converter.h"

#include <iostream>
using namespace::std;

namespace mom {

VoltageSourceMoMCore::VoltageSourceMoMCore() {
}

VoltageSourceMoMCore::~VoltageSourceMoMCore() {
}

ElementCoreSmartPointer VoltageSourceMoMCore::NewElementCore() {
	return ElementCoreSmartPointer(new VoltageSourceMoMCore);
}

void VoltageSourceMoMCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	VoltageSourceDTO* voltageSourceDTO = static_cast<VoltageSourceDTO*>(elementDTOSmartPtr.get());

	dto = *voltageSourceDTO;
}

MoMElementCoreType VoltageSourceMoMCore::GetType() {
	return SOURCE;
}
void VoltageSourceMoMCore::SetSource() {
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());

	int tagNumber;
	int segmentNumber;
	int mthSegment;

	bool r = engine->FindClosestSegment(dto.GetX(), dto.GetY(), dto.GetZ(), tagNumber, mthSegment, segmentNumber);
	double realPart = dto.GetRealPart();
	double imagPart = dto.GetImagPart();

	engine->GetNecContext()->ex_card(EXCITATION_VOLTAGE, tagNumber, mthSegment, 0, realPart, imagPart, 0, 0, 0, 0);
	necCommand = "EX ";
	necCommand.Append(Converter::IntToFormattedString(EXCITATION_VOLTAGE)).Append(" ").
			Append(Converter::IntToFormattedString(tagNumber)).Append(" ").
			Append(Converter::IntToFormattedString(mthSegment)).Append(" 0 ").
			Append(Converter::DoubleToFormattedString(realPart)).Append(" ").
			Append(Converter::DoubleToFormattedString(imagPart)).Append(" 0 0 0 0\n");
	cout << "engine->GetNecContext()->ex_card(EXCITATION_VOLTAGE, " << tagNumber << "," << mthSegment << "," << 0 <<"," << realPart << "," << imagPart << "," << 0 << "," << 0 << "," << 0 << "," << 0 << ");" << endl;
}
bool VoltageSourceMoMCore::HasResults() {
//	cout << "VoltageSourceMoMCore::HasResults" << endl;
	return true;
}
wxString VoltageSourceMoMCore::GetNECCommand() {
	return necCommand;
}
ElementResults VoltageSourceMoMCore::GetElementsResults() {
//	cout << "VoltageSourceMoMCore::GetElementsResults" << endl;
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());
	int nfreq = engine->GetMoMDTO().GetNFrequency();

	/* Guarda os dados a que essa fonte se refere */
	int tagNumber;
	int mthSegment;
	int segmentNumber;
	engine->FindClosestSegment(dto.GetX(), dto.GetY(), dto.GetZ(), tagNumber, mthSegment, segmentNumber);

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
		nec_antenna_input* inputAntenna = engine->GetNecContext()->get_input_parameters(i);
		frequencyData.push_back(inputAntenna->get_frequency()/normalized_frequency_factor); // Obs.: O NEC retorna os dados em Hz, apesar da entrada ser em MHz

		vector<int> tag = inputAntenna->get_tag();
		vector<int> segment = inputAntenna->get_segment();
//		cout << "inputAntenna->get_tag().size() = " << inputAntenna->get_tag().size() << endl;
		for (size_t j = 0; j < tag.size(); j++) {
//			cout << "pesquisando info da tag = " << tag[j] << " e segmento = " << segment[j] << " para freq = " << (inputAntenna->get_frequency()) << endl;
			// Procura nos resultados o elemento correto
			if (tag[j] == tagNumber && segment[j] == segmentNumber) {
//				cout << "Achou dados para essa tag (" << tagNumber << ") e segmento (" << segmentNumber << ")" << endl;
				vector<nec_complex> impedance = inputAntenna->get_impedance();
				vector<nec_complex> voltage = inputAntenna->get_voltage();
				vector<nec_complex> current = inputAntenna->get_current();
				vector<nec_float> power = inputAntenna->get_power();
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
//				cout << frequencyData[i] << "\t" << powerData[i] << endl;
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
