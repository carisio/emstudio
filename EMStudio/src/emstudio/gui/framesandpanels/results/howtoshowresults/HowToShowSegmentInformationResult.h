/*
 * HowToShowSegmentInformationResult.h
 *
 *  Created on: 10/07/2014
 *      Author: leandrocarisio
 */

#ifndef HOWTOSHOWSEGMENTINFORMATIONRESULT_H_
#define HOWTOSHOWSEGMENTINFORMATIONRESULT_H_

#include "HowToShowResults.h"
#include "HowToShowTableResult.h"
#include "emstudio/core/results/SegmentInformationResult.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/VisualizationPanel.h"
#include "emstudio/util/colormap/ColorMap.h"
#include <vector>
#include <complex>
#include "wx/wx.h"
#include "wx/tglbtn.h"
#include "wx/radiobox.h"
#include "wx/combobox.h"

namespace mom {

class OpenGLStateMachineForSegmentInformation : public OpenGLStateMachine {
private:
	double startFreqIndex, endFreqIndex;
	double radiusMultiplier;
	ResultSmartPointer result;
	std::vector<double> infoReal, infoImag, infoAmplitude, infoPhase;
	ColorMap colorMapReal, colorMapImag, colorMapAbs, colorMapPhase;
	wxString infoType;
public:
	OpenGLStateMachineForSegmentInformation(wxGLCanvas *canvas, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result);
	void SetRadiusMultiplier(double r);
	void SetFrequency(double f);
	void ShowAmplitude();
	void ShowPhase();
	void ShowReal();
	void ShowImag();

	virtual ~OpenGLStateMachineForSegmentInformation();
	bool ShouldIDrawThisElement(ElementGUISmartPointer e);
	virtual void DoDraw();
	virtual void DrawDC(wxPaintDC& dc);
};

class VisualizationPanelForSegmentInformation : public VisualizationPanel {
private:
	ElementManagerSmartPointer elementsInProject;
	ResultSmartPointer result;
public:
	VisualizationPanelForSegmentInformation(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result);
	~VisualizationPanelForSegmentInformation();

	void SetRadiusMultiplier(double m);
	void SetFrequency(double f);
	void ShowReal();
	void ShowImag();
	void ShowAmplitude();
	void ShowPhase();
	virtual OpenGLStateMachine* CreateOpenGLStateMachine(OpenGLVisualization* canvas, ElementManagerSmartPointer elementsInProject);
};

class ShowSegmentInformationPanel : public wxPanel {
private:
	ElementManagerSmartPointer elementsInProject;
	ResultSmartPointer result;

	/* Botões de controle de visão */
	wxToggleButton* btnAuto;
	wxToggleButton* btnXY;
	wxToggleButton* btnYZ;
	wxToggleButton* btnXZ;
	wxToggleButton* btnMove;
	wxToggleButton* btnRotate;
	wxToggleButton* btnZoom;
	void SetCameraMode(wxCommandEvent& event);
	void SetCameraMode(int buttonId);

	VisualizationPanelForSegmentInformation* visualizationPanel;

	/* Controle de informação (escolher frequencia, tipo de informação, multiplicador do raio) */
	wxComboBox* cboRadiusMultiplier;
	wxComboBox* cboFrequency;
	void SetFrequency(wxCommandEvent& event);
	void SetFrequency(int selection);
	void GenerateUniqueFrequenciesList();
	std::vector<double> uniqueFrequenciesDouble;
	wxArrayString uniqueFrequenciesString;
	void SetRadiusMultiplier(wxCommandEvent& event);
	wxRadioButton* btnReal;
	wxRadioButton* btnImag;
	wxRadioButton* btnAmplitude;
	wxRadioButton* btnPhase;
	void SetInformation(wxCommandEvent& event);

	void CreateControlsAndInsert();
public:
	ShowSegmentInformationPanel(wxWindow* parent, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result);
	virtual ~ShowSegmentInformationPanel();
};


class HowToShowSegmentInformationResult : public HowToShowResults {
private:
	ElementManagerSmartPointer elementsInProject;
public:
	HowToShowSegmentInformationResult(ElementManagerSmartPointer elementsInProject);
	virtual ~HowToShowSegmentInformationResult();

	virtual int GetNumberOfTabs();
	virtual wxString GetTabName(int tabIndex);
	virtual wxWindow* GetWindow(int tabIndex, wxWindow* parent);
};

} /* namespace mom */
#endif /* HOWTOSHOWSEGMENTINFORMATIONRESULT_H_ */
