/*
 * CartesianChartBuilder.h
 *
 *  Created on: 26/09/2013
 *      Author: leandrocarisio
 */

#ifndef CARTESIANCHARTBUILDER_H_
#define CARTESIANCHARTBUILDER_H_

#include "mathplot.h"
#include <vector>

class CartesianChartBuilder {
public:
	typedef std::vector<double> DoubleVec;
	typedef std::pair<DoubleVec, DoubleVec> DataXY;

private:
	wxString xAxisLabel;
	wxString yAxisLabel;
	wxFont xAxisFont;
	wxFont yAxisFont;

	/* Caneta default para o desenho das curvas */
	wxPen defaultDataPen;
	wxString defaultDataName;

	std::vector<DataXY> data;

public:
	CartesianChartBuilder();
	virtual ~CartesianChartBuilder();

	/* Métodos para a criação dos eixos */
	void SetXAxisLabel(wxString label);
	void SetYAxisLabel(wxString label);
	void SetXAxisFont(wxFont font);
	void SetYAxisFont(wxFont font);

	/* Método para a criação do layer com os dados */
	void SetDefaultDataPen(wxPen pen);
	void SetDefaultDataName(wxString name);

	/* Distância mínima entre os eixos */
	void SetMinimumDistanceYAxis(double min);

	/* Os métodos Create devem ser chamados após o SetData */
	void SetData(std::vector<DataXY> data);
	std::vector<mpLayer*> CreateAxisLayer();
	std::vector<mpLayer*> CreateDataLayers(std::vector<wxString> dataNames = std::vector<wxString>(),  std::vector<wxPen> pen = std::vector<wxPen>());
	std::vector<mpLayer*> CreateDefaultLayers(std::vector<DataXY> data, std::vector<wxString> vecNames = std::vector<wxString>());

};

#endif /* CARTESIANCHARTBUILDER_H_ */
