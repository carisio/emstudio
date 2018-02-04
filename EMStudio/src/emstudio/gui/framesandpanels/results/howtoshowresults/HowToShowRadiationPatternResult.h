/*
 * HowToShowRadiationPatternResult.h
 *
 *  Created on: 18/04/2013
 *      Author: Leandro
 */

#ifndef HOWTOSHOWRADIATIONPATTERNRESULT_H_
#define HOWTOSHOWRADIATIONPATTERNRESULT_H_

#include "HowToShowTableResult.h"
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "wx/radiobox.h"
#include "wx/combobox.h"
#include "wx/arrstr.h"

class ContainerRadiationDiagramPanel : public wxPanel {
private:
	ResultSmartPointer resultPtr;
	std::vector<wxColour> availableColors;

	wxWindow* radDiagramChart;
	wxBoxSizer* controlSizer;
	wxComboBox *freqOptions;
	wxRadioButton *optClockwise, *optCounterClockwise;
	wxSpinCtrl* rotateAxis;
	wxTextCtrl* txtMinDistance;
	wxButton* btnRefresh;

	/* Nome dos eixos */
	wxString xLabel, yLabel;
	void CreateAndInsertControls();
	void SetDefaultControlValues();
	void UpdateChart();
	void OnRefreshClicked(wxCommandEvent& event);

	mpWindow* BuildPolarChart(wxWindow* parent);
	wxArrayString GetAvailableFrequencies();
public:
	ContainerRadiationDiagramPanel(wxWindow* parent, ResultSmartPointer result, std::vector<wxColour> availableColors);
	virtual ~ContainerRadiationDiagramPanel();
};

class ContainerRadiationDiagramCartesianPanel : public wxPanel {
private:
	ResultSmartPointer resultPtr;

	wxWindow* radDiagramChart;
	wxBoxSizer* controlSizer;
	wxComboBox *freqOptions;
	wxButton* btnRefresh;

	void CreateAndInsertControls();
	void UpdateChart();
	void OnRefreshClicked(wxCommandEvent& event);

	wxWindow* BuildCartesianChart();
	wxArrayString GetAvailableFrequencies();
public:
	ContainerRadiationDiagramCartesianPanel(wxWindow* parent, ResultSmartPointer result);
	virtual ~ContainerRadiationDiagramCartesianPanel();
};


class HowToShowRadiationPatternResult : public HowToShowTableResult {

public:
	HowToShowRadiationPatternResult();
	virtual ~HowToShowRadiationPatternResult();

	virtual int GetNumberOfTabs();
	virtual wxString GetTabName(int tabIndex);
	virtual wxWindow* GetWindow(int tabIndex, wxWindow* parent);

};

#endif /* HOWTOSHOWRADIATIONPATTERNRESULT_H_ */
