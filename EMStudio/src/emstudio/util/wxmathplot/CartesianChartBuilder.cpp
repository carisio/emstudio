/*
 * CartesianChartBuilder.cpp
 *
 *  Created on: 26/09/2013
 *      Author: leandrocarisio
 */

#include "CartesianChartBuilder.h"

CartesianChartBuilder::CartesianChartBuilder() {
	xAxisLabel = "";
	yAxisLabel = "";

	wxFont defaultFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	xAxisFont = defaultFont;
	yAxisFont = defaultFont;

	defaultDataPen = wxPen(*wxBLUE, 2, wxPENSTYLE_SOLID);
	defaultDataName = "";
}

CartesianChartBuilder::~CartesianChartBuilder() {

}

void CartesianChartBuilder::SetXAxisLabel(wxString label) {
	xAxisLabel = label;
}
void CartesianChartBuilder::SetYAxisLabel(wxString label) {
	yAxisLabel = label;
}
void CartesianChartBuilder::SetXAxisFont(wxFont font) {
	xAxisFont = font;
}
void CartesianChartBuilder::SetYAxisFont(wxFont font) {
	yAxisFont = font;
}
void CartesianChartBuilder::SetData(std::vector<DataXY> data) {
	this->data = data;
}
void CartesianChartBuilder::SetDefaultDataPen(wxPen pen) {
	defaultDataPen = pen;
}
void CartesianChartBuilder::SetDefaultDataName(wxString name) {
	defaultDataName = name;
}
std::vector<mpLayer*> CartesianChartBuilder::CreateAxisLayer() {
	std::vector<mpLayer*> destination;

	mpScaleX* xaxis = new mpScaleX(xAxisLabel, mpALIGN_BOTTOM, true, mpX_NORMAL);
	mpScaleY* yaxis = new mpScaleY(yAxisLabel, mpALIGN_LEFT, true);

    xaxis->SetFont(xAxisFont);
    yaxis->SetFont(yAxisFont);

    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

    destination.push_back(xaxis);
    destination.push_back(yaxis);

	return destination;
}
std::vector<mpLayer*> CartesianChartBuilder::CreateDataLayers(std::vector<wxString> dataNames,  std::vector<wxPen> pens) {
	std::vector<mpLayer*> destination;

	bool defaultName = dataNames.size() == data.size() ? false: true;
	bool defaultPen = pens.size() == data.size() ? false: true;

	for (size_t i = 0; i < data.size(); i++) {
		DataXY& xyData = data[i];

		DoubleVec vectorx = xyData.first;
		DoubleVec vectory = xyData.second;

		wxString name = defaultName ? defaultDataName : dataNames[i];
		wxPen pen = defaultPen ? defaultDataPen : pens[i];

		mpFXYVector* vectorLayer = new mpFXYVector(name);
		vectorLayer->SetData(vectorx, vectory);
		vectorLayer->SetContinuity(true);
		vectorLayer->SetPen(pen);
		vectorLayer->SetDrawOutsideMargins(false);
		destination.push_back(vectorLayer);
	}

	return destination;
}
std::vector<mpLayer*> CartesianChartBuilder::CreateDefaultLayers(std::vector<DataXY> data, std::vector<wxString> vecNames) {
	std::vector<mpLayer*> result;

	SetData(data);

	/* Cria os eixos */
	std::vector<mpLayer*> layers = CreateAxisLayer();
	result.insert(result.end(), layers.begin(), layers.end());

	/* Cria um mpFXYVector para cada DataXY correspondente. Nesse caso, considera que x contém os angulos em graus */
	layers = CreateDataLayers(vecNames);
	result.insert(result.end(), layers.begin(), layers.end());

	return result;
}
