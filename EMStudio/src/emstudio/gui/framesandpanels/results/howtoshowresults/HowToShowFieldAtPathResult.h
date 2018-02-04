/*
 * HowToShowFieldAtPathResult.h
 *
 *  Created on: 26/09/2013
 *      Author: leandrocarisio
 */

#ifndef HOWTOSHOWFIELDATPATHRESULT_H_
#define HOWTOSHOWFIELDATPATHRESULT_H_

#include "HowToShowResults.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/core/results/FieldAtPathResult.h"

#include "emstudio/util/converters/Converter.h"

#include "wx/grid.h"
#include "wx/wx.h"

#include "emstudio/util/wxmathplot/mathplot.h"

#include "HowToShowTableResult.h"
#include <vector>

class SwitchCartesianChartPanel : public wxPanel {
public:
	typedef std::vector<std::vector<CartesianChartBuilder::DataXY> > DatasXYPerChart;
	typedef std::vector<std::vector<wxString> > PlotsLabelsPerChart;

private:
	/* Dados para montar os vários gráficos */
	DatasXYPerChart datas;
	PlotsLabelsPerChart plotLabels;
	std::vector<wxString> xAxisLabels;

	std::vector<wxColour> availableColors;

	/* Janela com as telas */
	mpWindow* visualizationChart;

	/* Controle de escala (linear/dB) */
	std::vector<wxString> buttonsLabels;
	std::vector<wxRadioButton* > optButtons;
//	wxRadioButton* btnLinear;
//	wxRadioButton* btnDB;
	void OptButtonChanged(wxCommandEvent& event);

	void CreateControlsAndInsert();
public:
	SwitchCartesianChartPanel(wxWindow* parent, std::vector<wxString> buttonsLabels,
			DatasXYPerChart datas, PlotsLabelsPerChart plotLabels, std::vector<wxString> xAxisLabels, std::vector<wxColour> availableColors);
	virtual ~SwitchCartesianChartPanel();
};

class HowToShowFieldAtPathResult : public HowToShowResults {
private:
	SwitchCartesianChartPanel::DatasXYPerChart GetDatasXYLinearDB(std::vector<int> selectedColumns);
	SwitchCartesianChartPanel::DatasXYPerChart GetDatasXYDegreeRadian(std::vector<int> selectedColumns);
	SwitchCartesianChartPanel::PlotsLabelsPerChart GetPlotLabels(std::vector<int> selectedColumns);
	std::vector<wxString> GetAxisLabels(int nLabels);
public:
	HowToShowFieldAtPathResult();
	virtual ~HowToShowFieldAtPathResult();

	virtual int GetNumberOfTabs();
	virtual wxString GetTabName(int tabIndex);
	virtual wxWindow* GetWindow(int tabIndex, wxWindow* parent);
};

vector<double> ToDB(vector<double> linear, double minDB, double mult);
vector<double> ToDegree(vector<double> rad);

#endif /* HOWTOSHOWFIELDATPATHRESULT_H_ */
