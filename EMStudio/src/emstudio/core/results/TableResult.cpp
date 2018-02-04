/*
 * TableData.cpp
 *
 *  Created on: 13/03/2012
 *      Author: leandrocarisio
 */

#include "TableResult.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/util/file/FileManager.h"

/*
 * Obs.: Se canBeInterpretedAsChart for verdadeiro, a primeira coluna da tablea será considerada como o eixo x.
 * Cada coluna excedente será considerada como diferentes curvas no eixo y.
 *
 * ----------------------------------------------------------------
 * | columnsLabel[0] | columnsLabel[1] | ...... | columnsLabel[N] |   -> Esses labels já estão embutidos na classe GenericTableData
 * ----------------------------------------------------------------
 * |                                                              |
 * ----------------------------------------------------------------
 * |               GENERIC                                        |
 * ----------------------------------------------------------------
 * |                      TABLE                                   |
 * ----------------------------------------------------------------
 * |                           DATA                               |
 * ----------------------------------------------------------------
 *
 */
TableResult::TableResult(wxString title, GenericTable data, BoolWrapper canBeInterpretedAsChart)
	: data(data),
	  canBeInterpretedAsChart(canBeInterpretedAsChart) {
	SetName(title);
//	this->title.SetUserFriendlyStringRepresentation(title);

//	AddProperty(Property("Title", &this->title));
//	AddProperty(Property("Columns name", &this->columnsLabel));
//	AddProperty(Property("Rows name", &this->rowName));
//	AddProperty(Property("Rows label", &this->rowsLabel));
	AddProperty(Property("Data", &this->data));
	AddProperty(Property("Can be interpreted as chart", &this->canBeInterpretedAsChart));

}

ResultSmartPointer TableResult::NewResult() {
	return ResultSmartPointer(new TableResult);
}
wxIcon TableResult::GetIcon() {
	if (CanBeInterpretedAsChart()) {
		return UtilResource::GetIcon("chart");
	} else {
		return UtilResource::GetIcon("table");
	}
}
bool TableResult::ExportData(wxString fileName) {
	bool saveOk = true;

	wxString path = FileManager::GetFolder(fileName);
	wxString baseFileName = FileManager::GetFileNameWithoutExtension(fileName);

	/* Salva o conteúdo do arquivo */
	wxString contentsDataFile = GetDataFileContents();
	wxString dataFileName = path; dataFileName.Append(baseFileName).Append("-data.txt");
	saveOk &= FileManager::SaveFile(dataFileName, contentsDataFile);

	/* Salva o arquivo de informações */
	wxString contentsInfoDataFile = GetInfoFileContents();
	wxString infoFileName = path; infoFileName.Append(baseFileName).Append("-info.txt");
	saveOk &= FileManager::SaveFile(infoFileName, contentsInfoDataFile);

	/* Salva o arquivo do matlab */
	if (! (canBeInterpretedAsChart.IsValue())) {
		return saveOk;
	}
	dataFileName = baseFileName; dataFileName.Append("-data.txt");
	wxString contentsMatlabFile = GetMatlabFileContents(dataFileName);
	wxString matlabFileName = path; matlabFileName.Append(baseFileName).Append(".m");
	saveOk &= FileManager::SaveFile(matlabFileName, contentsMatlabFile);

	return saveOk;
}
wxString TableResult::GetDataFileContents() {
	wxString contentsDataFile;
	std::vector<GenericTable::ColumnDataRepresentation>& columns = data.GetColumns();
	for (size_t row = 0; row < columns[0].size(); row++) {
		for (size_t col = 0; col < columns.size(); col++) {
			contentsDataFile.Append(Converter::DoubleToString(columns[col][row])).Append("\t");
		}
		contentsDataFile.Append("\n");
	}
	return contentsDataFile;
}
wxString TableResult::GetInfoFileContents() {
	/* Salva o arquivo de informações */
	wxString contentsInfoDataFile;
	contentsInfoDataFile.Append("Table title: ").Append(GetTitle()).Append("\n\n");
	contentsInfoDataFile.Append("Columns description:\n");
	contentsInfoDataFile.Append("--------------------\n");
	std::vector<wxString> columnsLabel = data.GetColumnsLabel();
	for (size_t col = 0; col < columnsLabel.size(); col++) {
		contentsInfoDataFile.Append("Column #").Append(Converter::IntToFormattedString(col+1)).Append(": ").Append(columnsLabel[col]).Append("\n");
	}

	return contentsInfoDataFile;
}
std::vector<wxColour> TableResult::GetAvailableColors() {
	std::vector<wxColour> availableColors;
	availableColors.push_back(wxColour(0,0,255));
	availableColors.push_back(wxColour(255,0,0));
	availableColors.push_back(wxColour(34,177,76));
	availableColors.push_back(wxColour(198,13,193));
	availableColors.push_back(wxColour(255,153,0));
	availableColors.push_back(wxColour(13,193,193));
	availableColors.push_back(wxColour(193,193,13));
	availableColors.push_back(wxColour(255,255,0));
	availableColors.push_back(wxColour(177,160,199));
	availableColors.push_back(wxColour(153,102,51));
	return availableColors;
}
wxString TableResult::GetMatlabFileContents(wxString dataFileName) {
	std::vector<wxColour> availableColors = GetAvailableColors();

	std::vector<GenericTable::ColumnDataRepresentation>& columns = data.GetColumns();
	std::vector<wxString> columnsLabel = data.GetColumnsLabel();

	wxString contentsMatlabFile;
	contentsMatlabFile.Append("clear all;\n").Append("close all;\n").Append("clc;\n\n");
	contentsMatlabFile.Append("dataFile = load('").Append(dataFileName).Append("');\n");
	// Plota o gráfico
	wxString plotStr = "hPlot = plot(dataFile(:,1), dataFile(:,2)";
	for (size_t col = 2; col < columns.size(); col++) {
		plotStr.Append(", dataFile(:,1), dataFile(:, ").Append(Converter::IntToFormattedString(col+1)).Append(")");
	}
	plotStr.Append(");\n\n");
	contentsMatlabFile.Append(plotStr);
	// Coloca nome no eixo x
	contentsMatlabFile.Append("hxLabel = xlabel('").Append(columnsLabel[0]).Append("');\n");
	// Coloca legenda
	wxString legendStr = "hLegend = legend('";
	legendStr.Append(columnsLabel[1]).Append("'");
	for (size_t col = 2; col < columnsLabel.size(); col++) {
		legendStr.Append(", '").Append(columnsLabel[col]).Append("'");
	}
	legendStr.Append(");\n");
	contentsMatlabFile.Append(legendStr).Append("\n\n");
	contentsMatlabFile.Append("set(hxLabel,'FontSize', 11);\n");
	contentsMatlabFile.Append("set(hLegend,'FontSize', 11);\n");
	for (size_t col = 1; col < columnsLabel.size(); col++) {
		wxString color = "[0.4 0.4 0.4]";
		if (col <= availableColors.size()) {
			color = "[";
			double r = availableColors[col-1].Red()/255.0;
			double g = availableColors[col-1].Green()/255.0;
			double b = availableColors[col-1].Blue()/255.0;
			color.Append(Converter::DoubleToString(r)).Append(" ").Append(Converter::DoubleToString(g)).Append(" ").Append(Converter::DoubleToString(b)).Append("]");
		}
		wxString hPlotStr = "set(hPlot(";
		hPlotStr.Append(Converter::IntToFormattedString(col)).Append("), 'Color', ").Append(color).Append(", 'LineWidth', 2);");
		contentsMatlabFile.Append(hPlotStr).Append("\n");
	}
	return contentsMatlabFile;
}
wxString TableResult::GetResultClassName() {
	return "TableResult";
}
wxString TableResult::GetTitle() {
	return GetName();
}
void TableResult::SetTitle(wxString str) {
//	title.SetValue(str);
	SetName(str);
}
GenericTable& TableResult::GetData() {
	return data;
}
void TableResult::SetData(GenericTable& table) {
	data.Copy(&table);
}
void TableResult::SetCanBeInterpretedAsChart(bool b) {
	canBeInterpretedAsChart.SetValue(b);
}
bool TableResult::CanBeInterpretedAsChart() {
	return canBeInterpretedAsChart.IsValue();
}
TableResult::~TableResult() {
}
