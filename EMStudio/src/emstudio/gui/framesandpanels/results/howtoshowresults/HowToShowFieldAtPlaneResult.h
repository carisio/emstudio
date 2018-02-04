/*
 * HowToShowFieldAtPlaneResult.h
 *
 *  Created on: 24/04/2013
 *      Author: Leandro
 */

#ifndef HOWTOSHOWFIELDATPLANERESULT_H_
#define HOWTOSHOWFIELDATPLANERESULT_H_

#include "HowToShowResults.h"
#include "emstudio/gui/elements/ElementManager.h"
#include <vector>
#include "emstudio/core/results/FieldAtPlaneResult.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/VisualizationPanel.h"
#include "emstudio/util/colormap/ColorMap.h"

#include "wx/wx.h"
#include "wx/slider.h"
#include "wx/tglbtn.h"
#include "wx/spinctrl.h"
#include "wx/radiobox.h"
#include "emstudio/util/tnt/tnt.h"

using namespace::TNT;

//class Timer : public wxTimer {
//private:
//	ShowMoviePanel* panel;
//
//public:
//	virtual void Notify();
//};


class OpenGLStateMachineWithFieldAtPlane : public OpenGLStateMachine {
private:
	bool linearScale; // true se escala linear. false se escala db.
	double minFieldDB; double minFieldLinear; double normalizedFactor;
	ResultSmartPointer result;
	int frame;
	Array1D<double> positionDim1;
	Array1D<double> positionDim2;
	Array3D<double> field;
	double cutAt;
	ColorMap colorMapLinearScale;
	ColorMap colorMapDBScale;
public:
	OpenGLStateMachineWithFieldAtPlane(wxGLCanvas *canvas, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result);
	void ShowFrame(int frame);
	void SetLinearScale();
	void SetDBScale();

	virtual ~OpenGLStateMachineWithFieldAtPlane();
	virtual void DoDraw();
	virtual void DrawDC(wxPaintDC& dc);
};

class VisualizationPanelWithFieldAtPlane : public VisualizationPanel {
private:
	ResultSmartPointer result;
public:
	VisualizationPanelWithFieldAtPlane(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result);
	~VisualizationPanelWithFieldAtPlane();

	void ShowFrame(int frame);
	void SetLinearScale();
	void SetDBScale();
	virtual OpenGLStateMachine* CreateOpenGLStateMachine(OpenGLVisualization* canvas, ElementManagerSmartPointer elementsInProject);
};

class ShowMoviePanel : public wxPanel {
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

	VisualizationPanelWithFieldAtPlane* visualizationPanel;

	/* Botões de controle de velocidade */
	wxToggleButton* btnPlay;
	wxToggleButton* btnPause;
	wxSlider* sldFrame;
	wxStaticText* lblTime;
	wxSpinCtrl* fps;
	void PlayPauseMovie(int buttonId);
	void PlayPauseMovie(wxCommandEvent& event);
	void SetFrame(wxCommandEvent& event);
	void SetFPS(wxSpinEvent& event);

	/* Controle do andamento do vídeo */
	Array1D<double> timeVec;
	wxString timeUnit;
	int numberOfFrames;
	int index;
	int defaultFrameSpeed; // Dado em milisegundos
	wxTimer timer;
	void ShowNextFrame();
	void OnTimerTick(wxTimerEvent& event);

	/* Controle de escala (linear/dB) */
	wxRadioButton* btnLinear;
	wxRadioButton* btnDB;
	void SetScale(wxCommandEvent& event);

	void CreateControlsAndInsert();
public:
	ShowMoviePanel (wxWindow* parent, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result);
	virtual ~ShowMoviePanel();
};


class HowToShowFieldAtPlaneResult : public HowToShowResults {
private:
	ElementManagerSmartPointer elementsInProject;
public:
	HowToShowFieldAtPlaneResult(ElementManagerSmartPointer elementsInProject);
	virtual ~HowToShowFieldAtPlaneResult();

	virtual int GetNumberOfTabs();
	virtual wxString GetTabName(int tabIndex);
	virtual wxWindow* GetWindow(int tabIndex, wxWindow* parent);
};

#endif /* HOWTOSHOWFIELDATPLANERESULT_H_ */
