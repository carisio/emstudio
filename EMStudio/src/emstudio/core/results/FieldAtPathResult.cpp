/*
 * FieldAtPathResult.cpp
 *
 *  Created on: 26/09/2013
 *      Author: leandrocarisio
 */

#include "FieldAtPathResult.h"
#include "emstudio/util/file/FileManager.h"

FieldAtPathResult::FieldAtPathResult(wxString title, GenericTable data, BoolWrapper canBeInterpretedAsChart)
	: TableResult(title, data, canBeInterpretedAsChart) {
	SetCanBeInterpretedAsChart(true);
}

FieldAtPathResult::~FieldAtPathResult() {
}

wxString FieldAtPathResult::GetResultClassName() {
	return "FieldAtPathResult";
}
ResultSmartPointer FieldAtPathResult::NewResult() {
	return ResultSmartPointer(new FieldAtPathResult);
}
/**
 * Os campos são organizados em um GenericTable. Na tabela as colunas 0...13 representam:
 * 0 - positionField
 * 1 - ExMag
 * 2 - EyMag
 * 3 - EzMag
 * 4 - HxMag
 * 5 - HyMag
 * 6 - HzMag
 * 7 - ExPhase
 * 8 - EyPhase
 * 9 - EzPhase
 * 10 - HxPhase
 * 11 - HyPhase
 * 12 - HzPhase
 */
void FieldAtPathResult::SetField(
		GenericTable::ColumnDataRepresentation positionField, wxString positionTitle,
		GenericTable::ColumnDataRepresentation ExMag, GenericTable::ColumnDataRepresentation EyMag,
		GenericTable::ColumnDataRepresentation EzMag, GenericTable::ColumnDataRepresentation HxMag,
		GenericTable::ColumnDataRepresentation HyMag, GenericTable::ColumnDataRepresentation HzMag,
		GenericTable::ColumnDataRepresentation ExPhase, GenericTable::ColumnDataRepresentation EyPhase,
		GenericTable::ColumnDataRepresentation EzPhase, GenericTable::ColumnDataRepresentation HxPhase,
		GenericTable::ColumnDataRepresentation HyPhase, GenericTable::ColumnDataRepresentation HzPhase) {

	GenericTable table;
	std::vector<wxString> columnsLabel;

	table.AddColumn(positionField);	columnsLabel.push_back(positionTitle);
	table.AddColumn(ExMag);			columnsLabel.push_back("Ex (V/m)");
	table.AddColumn(EyMag);			columnsLabel.push_back("Ey (V/m)");
	table.AddColumn(EzMag);			columnsLabel.push_back("Ez (V/m)");
	table.AddColumn(HxMag);			columnsLabel.push_back("Hx (A/m)");
	table.AddColumn(HyMag);			columnsLabel.push_back("Hy (A/m)");
	table.AddColumn(HzMag);			columnsLabel.push_back("Hz (A/m)");
	table.AddColumn(ExPhase);		columnsLabel.push_back("Ex (rad)");
	table.AddColumn(EyPhase);		columnsLabel.push_back("Ey (rad)");
	table.AddColumn(EzPhase);		columnsLabel.push_back("Ez (rad)");
	table.AddColumn(HxPhase);		columnsLabel.push_back("Hx (rad)");
	table.AddColumn(HyPhase);		columnsLabel.push_back("Hy (rad)");
	table.AddColumn(HzPhase);		columnsLabel.push_back("Hz (rad)");

	table.SetColumnsLabel(columnsLabel);
	SetData(table);
}

wxString FieldAtPathResult::GetPositionTitle() {
	return GetData().GetColumnsLabel()[0];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetPosition() {
	return GetData().GetColumns()[0];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetExMag() {
	return GetData().GetColumns()[1];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetEyMag() {
	return GetData().GetColumns()[2];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetEzMag() {
	return GetData().GetColumns()[3];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetHxMag() {
	return GetData().GetColumns()[4];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetHyMag() {
	return GetData().GetColumns()[5];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetHzMag() {
	return GetData().GetColumns()[6];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetExPhase() {
	return GetData().GetColumns()[7];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetEyPhase() {
	return GetData().GetColumns()[8];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetEzPhase() {
	return GetData().GetColumns()[9];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetHxPhase() {
	return GetData().GetColumns()[10];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetHyPhase() {
	return GetData().GetColumns()[11];
}
GenericTable::ColumnDataRepresentation FieldAtPathResult::GetHzPhase() {
	return GetData().GetColumns()[12];
}
bool FieldAtPathResult::ExportData(wxString fileName) {
	return TableResult::ExportData(fileName);
}
wxString FieldAtPathResult::GetMatlabFileContents(wxString dataFileName) {
	std::vector<wxColour> availableColors = GetAvailableColors();
	std::vector<wxString> matlabColors;

	for (int i = 0; i < 3; i++) {
		wxString strColor = "[";
		double r = availableColors[i].Red()/255.0;
		double g = availableColors[i].Green()/255.0;
		double b = availableColors[i].Blue()/255.0;
		strColor.Append(Converter::DoubleToString(r)).Append(" ").Append(Converter::DoubleToString(g)).Append(" ").Append(Converter::DoubleToString(b)).Append("]");
		matlabColors.push_back(strColor);
	}
	std::vector<GenericTable::ColumnDataRepresentation>& columns = GetData().GetColumns();
	std::vector<wxString>& columnsLabel = GetData().GetColumnsLabel();

	wxString contentsMatlabFile;
	contentsMatlabFile.Append("clear all;\n").Append("close all;\n").Append("clc;\n\n");
	contentsMatlabFile.Append("dataFile = load('").Append(dataFileName).Append("');\n");
	contentsMatlabFile.Append("position = dataFile(:,1);\n");
	contentsMatlabFile.Append("ExAmp = dataFile(:,2);\n");
	contentsMatlabFile.Append("EyAmp = dataFile(:,3);\n");
	contentsMatlabFile.Append("EzAmp = dataFile(:,4);\n");
	contentsMatlabFile.Append("HxAmp = dataFile(:,5);\n");
	contentsMatlabFile.Append("HyAmp = dataFile(:,6);\n");
	contentsMatlabFile.Append("HzAmp = dataFile(:,7);\n");
	contentsMatlabFile.Append("ExPhase = dataFile(:,8);\n");
	contentsMatlabFile.Append("EyPhase = dataFile(:,9);\n");
	contentsMatlabFile.Append("EzPhase = dataFile(:,10);\n");
	contentsMatlabFile.Append("HxPhase = dataFile(:,11);\n");
	contentsMatlabFile.Append("HyPhase = dataFile(:,12);\n");
	contentsMatlabFile.Append("HzPhase = dataFile(:,13);\n\n");

	wxString xLabel = "xlabel('"; xLabel.Append(columnsLabel[0]).Append("');\n");

	contentsMatlabFile.Append("figure(1);\n");
	contentsMatlabFile.Append("hPlot1 = plot(position, ExAmp, position, EyAmp, position, EzAmp);\n");
	contentsMatlabFile.Append("hxLabel1 = ").Append(xLabel);
	contentsMatlabFile.Append("hLegend1 = legend('Ex', 'Ey', 'Ez');\n");
	contentsMatlabFile.Append("title('E Field (Amplitude)');\n");
	contentsMatlabFile.Append("set(hxLabel1, 'FontSize', 11);\n");
	contentsMatlabFile.Append("set(hLegend1, 'FontSize', 11);\n");
	for (int i = 0; i < 3; i++) {
		contentsMatlabFile.Append("set(hPlot1(").Append(Converter::IntToFormattedString(i+1)).Append("), 'Color', ").Append(matlabColors[i]).Append(", 'LineWidth', 2);\n");
	}
	contentsMatlabFile.Append("\n");
	contentsMatlabFile.Append("\n");

	contentsMatlabFile.Append("figure(2);\n");
	contentsMatlabFile.Append("hPlot2 = plot(position, HxAmp, position, HyAmp, position, HzAmp);\n");
	contentsMatlabFile.Append("hxLabel2 = ").Append(xLabel);
	contentsMatlabFile.Append("hLegend2 = legend('Hx', 'Hy', 'Hz');\n");
	contentsMatlabFile.Append("title('H Field (Amplitude)');\n");
	contentsMatlabFile.Append("set(hxLabel2, 'FontSize', 11);\n");
	contentsMatlabFile.Append("set(hLegend2, 'FontSize', 11);\n");
	for (int i = 0; i < 3; i++) {
		contentsMatlabFile.Append("set(hPlot2(").Append(Converter::IntToFormattedString(i+1)).Append("), 'Color', ").Append(matlabColors[i]).Append(", 'LineWidth', 2);\n");
	}
	contentsMatlabFile.Append("\n");
	contentsMatlabFile.Append("\n");

	contentsMatlabFile.Append("figure(3);\n");
	contentsMatlabFile.Append("hPlot3 = plot(position, ExPhase, position, EyPhase, position, EzPhase);\n");
	contentsMatlabFile.Append("hxLabel3 = ").Append(xLabel);
	contentsMatlabFile.Append("hLegend3 = legend('Ex', 'Ey', 'Ez');\n");
	contentsMatlabFile.Append("title('E Field (Phase)');\n");
	contentsMatlabFile.Append("set(hxLabel3, 'FontSize', 11);\n");
	contentsMatlabFile.Append("set(hLegend3, 'FontSize', 11);\n");
	for (int i = 0; i < 3; i++) {
		contentsMatlabFile.Append("set(hPlot3(").Append(Converter::IntToFormattedString(i+1)).Append("), 'Color', ").Append(matlabColors[i]).Append(", 'LineWidth', 2);\n");
	}
	contentsMatlabFile.Append("\n");
	contentsMatlabFile.Append("\n");

	contentsMatlabFile.Append("figure(4);\n");
	contentsMatlabFile.Append("hPlot4 = plot(position, HxPhase, position, HyPhase, position, HzPhase);\n");
	contentsMatlabFile.Append("hxLabel4 = ").Append(xLabel);
	contentsMatlabFile.Append("hLegend4 = legend('Hx', 'Hy', 'Hz');\n");
	contentsMatlabFile.Append("title('H Field (Phase)');\n");
	contentsMatlabFile.Append("set(hxLabel4, 'FontSize', 11);\n");
	contentsMatlabFile.Append("set(hLegend4, 'FontSize', 11);\n");
	for (int i = 0; i < 3; i++) {
		contentsMatlabFile.Append("set(hPlot4(").Append(Converter::IntToFormattedString(i+1)).Append("), 'Color', ").Append(matlabColors[i]).Append(", 'LineWidth', 2);\n");
	}
	contentsMatlabFile.Append("\n");
	contentsMatlabFile.Append("\n");

	return contentsMatlabFile;
}
