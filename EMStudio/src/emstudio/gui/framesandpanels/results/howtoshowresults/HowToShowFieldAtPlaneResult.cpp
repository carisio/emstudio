/*
 * HowToShowFieldAtPlaneResult.cpp
 *
 *  Created on: 24/04/2013
 *      Author: Leandro
 */

#include "HowToShowFieldAtPlaneResult.h"

#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include <iostream>
using namespace::std;

HowToShowFieldAtPlaneResult::HowToShowFieldAtPlaneResult(ElementManagerSmartPointer elementsInProject)
	: HowToShowResults(), elementsInProject(elementsInProject) {

}

HowToShowFieldAtPlaneResult::~HowToShowFieldAtPlaneResult() {
}

int HowToShowFieldAtPlaneResult::GetNumberOfTabs() {
	return 1;
}

wxString HowToShowFieldAtPlaneResult::GetTabName(int tabIndex) {
	wxString tabName = "Movie";

	return tabName;
}

wxWindow* HowToShowFieldAtPlaneResult::GetWindow(int tabIndex, wxWindow* parent) {
	ResultSmartPointer ptrToResult = GetResult();

	wxWindow* ptr = new ShowMoviePanel(parent, elementsInProject, ptrToResult);

	return ptr;
}
// ---------------------------------------------------------------
// Classe ShowMoviePanel
// ---------------------------------------------------------------
ShowMoviePanel::ShowMoviePanel(wxWindow* parent, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result)
	:wxPanel(parent), elementsInProject(elementsInProject), result(result), index(0), defaultFrameSpeed(100) {

	FieldAtPlaneResult* fieldAtPlaneResult = static_cast<FieldAtPlaneResult*>(result.get());
	numberOfFrames = fieldAtPlaneResult->GetTimeVector().GetData().dim1();
	timeVec = fieldAtPlaneResult->GetTimeVector().GetData();
	timeUnit = fieldAtPlaneResult->GetTimeUnit();

	CreateControlsAndInsert();

	/* Inicializa a camera como auto */
	SetCameraMode(btnAuto->GetId());

	/* Inicializa o vídeo pausado */
	PlayPauseMovie(btnPause->GetId());
}
ShowMoviePanel::~ShowMoviePanel() {

}
void ShowMoviePanel::ShowNextFrame() {
	index++;
	if (index >= numberOfFrames) {
		index = 0;
	}
	wxString label = "t = ";
	label.Append(Converter::DoubleToFormattedString(timeVec[index], 2));
	label.Append(" ").Append(timeUnit);
	label.Append(". Frame = ").Append(Converter::IntToFormattedString(index));
	lblTime->SetLabel(label);
	sldFrame->SetValue(index);

	visualizationPanel->ShowFrame(index);
	visualizationPanel->ForceRedraw();
}
void ShowMoviePanel::OnTimerTick(wxTimerEvent& event) {
	ShowNextFrame();
}
/**
 * A velocidade é calculada da seguinte forma:
 *
 * Slider:                            Exemplo:
 * |----------|----------|            |----------|----------|
 * min       med        max           0          5         10
 *
 * Correspondência em velocidade:     Exemplo:
 * |----------|----------|            |----------|----------|
 * c*x        x          x/c         200        100        50
 *
 * x é representando pela variável defaultFrameSpeed e é dado em ms. Representa de qto em qto tempo
 * o frame é redesenhado
 * c é uma constante que indica qual a variação máxima permitida pelo software. Por exemplo, se c = 2, então
 * o usuário poderá estipular que o frame rate do filme varia de defaultFrameSpeed/2 até 2*defaultFrameSpeed
 *
 * Dado esse cenário, dado um valor qualquer no slider, deve-se calcular quanto ele representa em atraso.
 * Isso é feito com uma regra de 3 simples:
 *
 * A posição do slider (pos) indica que houve d=(pos-min)/(max-min) % de deslocamento.
 * Esse deslocamento, em unidades de velocidade, corresponde a:
 *
 * velocidade = c*x - (c*x - x/c)*(d)
 *
 */
void ShowMoviePanel::PlayPauseMovie(int buttonId) {
	btnPlay->SetValue(false);
	btnPause->SetValue(false);

	if (buttonId == btnPlay->GetId()) {
		btnPlay->SetValue(true);

		double currentSpeedMs = 1000.0/fps->GetValue();
		timer.Start((int)(currentSpeedMs), false);
	} else if (buttonId == btnPause->GetId()) {
		btnPause->SetValue(true);
		timer.Stop();
	}
}
void ShowMoviePanel::SetFrame(wxCommandEvent& event) {
	index = sldFrame->GetValue();
	// Se o vído estiver pausado, atualiza a tela. Se estive no play, a atualização já é feita.
	if (btnPause->GetValue()) {
		ShowNextFrame();
	}
}
void ShowMoviePanel::SetFPS(wxSpinEvent& event) {
	if (btnPlay->GetValue()) {
		PlayPauseMovie(btnPlay->GetId());
	}
}
void ShowMoviePanel::PlayPauseMovie(wxCommandEvent& event) {
	PlayPauseMovie(event.GetId());
}
void ShowMoviePanel::SetScale(wxCommandEvent& event) {
	if (btnLinear->GetValue())
		visualizationPanel->SetLinearScale();
	if (btnDB->GetValue())
		visualizationPanel->SetDBScale();

	visualizationPanel->ForceRedraw();
}
void ShowMoviePanel::SetCameraMode(int buttonId) {
	btnAuto->SetValue(false);
	btnXY->SetValue(false);
	btnYZ->SetValue(false);
	btnXZ->SetValue(false);
	btnMove->SetValue(false);
	btnRotate->SetValue(false);
	btnZoom->SetValue(false);

	if (buttonId == btnAuto->GetId()) {
		btnAuto->SetValue(true);
		visualizationPanel->SetCameraMode(CAM_AUTO);
	} else if (buttonId == btnXY->GetId()) {
		btnXY->SetValue(true);
		visualizationPanel->SetCameraMode(CAM_XY);
	} else if (buttonId == btnYZ->GetId()) {
		btnYZ->SetValue(true);
		visualizationPanel->SetCameraMode(CAM_YZ);
	} else if (buttonId == btnXZ->GetId()) {
		btnXZ->SetValue(true);
		visualizationPanel->SetCameraMode(CAM_XZ);
	} else if (buttonId == btnMove->GetId()) {
		btnMove->SetValue(true);
		visualizationPanel->EnableCameraMove();
	} else if (buttonId == btnRotate->GetId()) {
		btnRotate->SetValue(true);
		visualizationPanel->EnableCameraRotate();
	} else if (buttonId == btnZoom->GetId()) {
		btnZoom->SetValue(true);
		visualizationPanel->EnableCameraZoom();
	}
}
void ShowMoviePanel::SetCameraMode(wxCommandEvent& event) {
	SetCameraMode(event.GetId());
}
void ShowMoviePanel::CreateControlsAndInsert() {
	/*******************************************************/
	/* PAINÉL COM BOTÕES DE CONTROLE DE VISUALIZAÇÃO       */
	/*******************************************************/
	btnAuto = new wxToggleButton(this, wxID_ANY, "Auto");
	btnXY = new wxToggleButton(this, wxID_ANY, "XY");
	btnYZ = new wxToggleButton(this, wxID_ANY, "YZ");
	btnXZ= new wxToggleButton(this, wxID_ANY, "XZ");
	btnMove = new wxToggleButton(this, wxID_ANY, "Move");
	btnRotate = new wxToggleButton(this, wxID_ANY, "Rotate");
	btnZoom = new wxToggleButton(this, wxID_ANY, "Zoom");

	Connect(btnAuto->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::SetCameraMode));
	Connect(btnXY->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::SetCameraMode));
	Connect(btnYZ->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::SetCameraMode));
	Connect(btnXZ->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::SetCameraMode));
	Connect(btnMove->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::SetCameraMode));
	Connect(btnRotate->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::SetCameraMode));
	Connect(btnZoom->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::SetCameraMode));

	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsSizer->Add(btnAuto, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnXY, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnYZ, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnXZ, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnMove, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnRotate, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnZoom, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);

	/*******************************************************/
	/* PAINÉL COM O OPENGL                                 */
	/*******************************************************/
	visualizationPanel = new VisualizationPanelWithFieldAtPlane(this, wxID_ANY, elementsInProject, result);
	visualizationPanel->Create();

	/*******************************************************/
	/* PAINÉL COM O CONTROLE DO FILME                      */
	/*******************************************************/
	timer.SetOwner(this);
	Connect(timer.GetId(), wxEVT_TIMER, wxTimerEventHandler(ShowMoviePanel::OnTimerTick), NULL, this);

	btnPlay = new wxToggleButton(this, wxID_ANY, ">");
	btnPause = new wxToggleButton(this, wxID_ANY, "||");
	sldFrame = new wxSlider(this, wxID_ANY, 0, 0, numberOfFrames-1, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_AUTOTICKS);
	lblTime = new wxStaticText(this, wxID_ANY, "");
	fps = new wxSpinCtrl(this, wxID_ANY, "10", wxDefaultPosition, wxDefaultSize, wxSP_WRAP | wxSP_ARROW_KEYS, 1, 30);
	btnLinear = new wxRadioButton(this, wxID_ANY, "Linear"); btnLinear->SetValue(true); visualizationPanel->SetLinearScale();
	btnDB = new wxRadioButton(this, wxID_ANY, "dB (normalized)");

	Connect(btnPlay->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::PlayPauseMovie));
	Connect(btnPause->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowMoviePanel::PlayPauseMovie));
	Connect(sldFrame->GetId(), wxEVT_COMMAND_SLIDER_UPDATED, wxCommandEventHandler(ShowMoviePanel::SetFrame));
	Connect(fps->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ShowMoviePanel::SetFPS));
	Connect(btnLinear->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ShowMoviePanel::SetScale));
	Connect(btnDB->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ShowMoviePanel::SetScale));

	wxBoxSizer* movieControlSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* boxFrameControl = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* boxScaleControl = new wxBoxSizer(wxVERTICAL);

//	movieControlSizer->AddGrowableCol(3);
	movieControlSizer->Add(btnPlay, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	movieControlSizer->Add(btnPause, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	boxFrameControl->Add(sldFrame, 0, wxEXPAND | wxALL | wxALIGN_CENTER_VERTICAL, 0);
	boxFrameControl->Add(lblTime, 0, wxALL | wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL, 0);
	movieControlSizer->Add(boxFrameControl, 10, wxEXPAND | wxALL | wxALIGN_CENTER, 5);
	movieControlSizer->Add(new wxStaticText(this, wxID_ANY, "FPS:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	movieControlSizer->Add(fps, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	boxScaleControl->Add(btnLinear, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	boxScaleControl->Add(btnDB, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	movieControlSizer->Add(boxScaleControl, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

//	wxFlexGridSizer* topSizer = new wxFlexGridSizer(3, 1, 0, 0);
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
//	topSizer->AddGrowableRow(1);
//	topSizer->AddGrowableCol(0);
	topSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	topSizer->Add(visualizationPanel, 10, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	topSizer->Add(movieControlSizer, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
	topSizer->Layout();
}

// ---------------------------------------------------------------
// Classe OpenGLStateMachineWithFieldAtPlane
// ---------------------------------------------------------------
OpenGLStateMachineWithFieldAtPlane::OpenGLStateMachineWithFieldAtPlane(wxGLCanvas *canvas, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result)
	: OpenGLStateMachine(canvas, elementsInProject), result(result), frame(0) {

	FieldAtPlaneResult* fieldAtPlaneResult = static_cast<FieldAtPlaneResult*>(result.get());

	positionDim1 = fieldAtPlaneResult->GetPositionDim1().GetData();
	positionDim2 = fieldAtPlaneResult->GetPositionDim2().GetData();
	cutAt = fieldAtPlaneResult->GetPlane().GetCutAt();
	field = fieldAtPlaneResult->GetField().GetData();

	// Cria a escala de cores - escala linear
	double fieldMin = 1e30;
	double fieldMax = -1e30;
	// Cria a escala de cores - escala dB
	double fieldMinABS = 1e30;
	double fieldMaxABS = -1e30;

	for (int i = 0; i < field.dim1(); i++) {
		for (int j = 0; j < field.dim2(); j++) {
			for (int k = 0; k < field.dim3(); k++) {
				/* limites para escala linear */
				double f = field[i][j][k];
				if (f < fieldMin)
					fieldMin = f;
				if (f > fieldMax)
					fieldMax = f;

				/* limites para escala em dB */
				double abs_f = abs(f);
				if (abs_f < fieldMinABS)
					fieldMinABS = abs_f;
				if (abs_f > fieldMaxABS)
					fieldMaxABS = abs_f;
			}
		}
	}
	cout << "fieldMin = " << fieldMin << endl;
	cout << "fieldMax = " << fieldMax << endl;
	colorMapLinearScale = ColorMap(100, fieldMin, fieldMax);
	minFieldDB = -60;
	minFieldLinear = pow(10,minFieldDB/20);
	/* Normaliza */
	normalizedFactor = fieldMaxABS;
	fieldMaxABS /= normalizedFactor;
	fieldMinABS /= normalizedFactor;
	if (fieldMinABS < minFieldLinear) {
		fieldMinABS = minFieldLinear;
	}
	if (fieldMaxABS < minFieldLinear) {
		fieldMaxABS = minFieldLinear;
	}
	cout << "fieldMaxABS = " << fieldMinABS << endl;
	cout << "fieldMaxABS = " << fieldMaxABS << endl;
	colorMapDBScale = ColorMap(100, 20*log10(fieldMinABS), 20*log10(fieldMaxABS));
}
void OpenGLStateMachineWithFieldAtPlane::ShowFrame(int frame) {
	this->frame = frame;
}
void OpenGLStateMachineWithFieldAtPlane::SetLinearScale() {
	linearScale = true;
}
void OpenGLStateMachineWithFieldAtPlane::SetDBScale() {
	linearScale = false;
}
OpenGLStateMachineWithFieldAtPlane::~OpenGLStateMachineWithFieldAtPlane() {

}
void OpenGLStateMachineWithFieldAtPlane::DoDraw() {
	OpenGLStateMachine::DoDraw();
	FieldAtPlaneResult* fieldAtPlaneResult = static_cast<FieldAtPlaneResult*>(result.get());

	Sheet plane = fieldAtPlaneResult->GetPlane();

	if (plane.IsCutAtZ()) {
		// Dimension 1 = x
		// Dimension 2 = y

		for (int i = 0; i < positionDim1.dim1()-1; i++) {
			for (int j = 0; j < positionDim2.dim1()-1; j++) {
				if (linearScale) {
					SetColor(colorMapLinearScale.GetColor(field[i][j][frame]));
				} else {
					double abs_f = abs(field[i][j][frame])/normalizedFactor;
					if (abs_f < minFieldLinear) {
						abs_f = minFieldLinear;
					}
					SetColor(colorMapDBScale.GetColor(20*log10(abs_f)));
				}
				DrawPlaneZ(positionDim1[i], positionDim2[j], positionDim1[i+1], positionDim2[j+1], cutAt, true);
			}
		}
	} else if (plane.IsCutAtX()) {
		// Dimension 1 = y
		// Dimension 2 = z

		for (int j = 0; j < positionDim1.dim1()-1; j++) {
			for (int k = 0; k < positionDim2.dim1()-1;k++) {
				if (linearScale) {
					SetColor(colorMapLinearScale.GetColor(field[j][k][frame]));
				} else {
					double abs_f = abs(field[j][k][frame])/normalizedFactor;
					if (abs_f < minFieldLinear) {
						abs_f = minFieldLinear;
					}
					SetColor(colorMapDBScale.GetColor(20*log10(abs_f)));
				}
				DrawPlaneX(positionDim1[j], positionDim2[k], positionDim1[j+1], positionDim2[k+1], cutAt, true);
			}
		}
	} else if (plane.IsCutAtY()) {
		// Dimension 1 = x
		// Dimension 2 = z

		for (int i = 0; i < positionDim1.dim1()-1; i++) {
			for (int k = 0; k < positionDim2.dim1()-1;k++) {
				if (linearScale) {
					SetColor(colorMapLinearScale.GetColor(field[i][k][frame]));
				} else {
					double abs_f = abs(field[i][k][frame])/normalizedFactor;
					if (abs_f < minFieldLinear) {
						abs_f = minFieldLinear;
					}
					SetColor(colorMapDBScale.GetColor(20*log10(abs_f)));

				}
				DrawPlaneY(positionDim1[i], positionDim2[k], positionDim1[i+1], positionDim2[k+1], cutAt, true);
			}
		}
	}
}
void OpenGLStateMachineWithFieldAtPlane::DrawDC(wxPaintDC& dc) {
	OpenGLStateMachine::DrawDC(dc);
	ColorMap& colorMap = linearScale ? colorMapLinearScale : colorMapDBScale;
	int px1 = 20;
	int px2 = 60;
	int py1 = dc.GetSize().y-20;
	int py2 = py1 - 300; // Coordenadas y são invertidas
	if (py2 < 0) py2 = 100;
//	int py2 = 100; // Coordenadas y são invertidas
	int nColors = 50;

	int stepY = (py1-py2)/nColors;
	for (int i = 0; i < nColors; i++) {
		double value = colorMap.Max() - (colorMap.Max()-colorMap.Min())*(i+0.5)/nColors;
		wxColour color = colorMap.GetColor(value);

		wxPen p(color);
		wxBrush b(color);
		dc.SetPen(p);
		dc.SetBrush(b);

		int pyi = py2 + stepY*i;
		int pyf = py2 + stepY*(i+1);
		dc.DrawRectangle(px1, pyi, (px2-px1), (pyf-pyi));
	}
	/*
	 *  O código abaixo foi inspirado na resposta dada em:
	 *  https://groups.google.com/forum/#!searchin/wx-users/clearbackground/wx-users/7NlWvj5kEaQ/nL85LtH9rZkJ
	 *
	 *  A ideia é a seguinte:
	 *
	 *	Antes de desenhar o texto, reseta a bounding box. Depois disso, desenha o texto.
	 *	As coordenadas MinX, MinY, MaxX e MaxY vão guardar os valores em que o texto está contido
	 *	Depois disso, desenha um retângulo embaixo, de cor branca, em cima do texto
	 *	Depois, desenha novamente o texto, já que o retângulo cobriu o texto.
	 *
	 *	Se não fizer isso, se tirar o desenho do retângulo, a tela vai guardar um lixo onde desenha o texto (no Windows 7, no XP funciona bem)
	 */
	wxPen pp(colorMap.GetColor(colorMap.Min()+(colorMap.Max()-colorMap.Min())/2), 1, wxTRANSPARENT);
	wxBrush bb(wxColor(255,255,255));
	dc.SetPen(pp);
	dc.SetBrush(bb);
	dc.SetBackgroundMode(wxTRANSPARENT);

	dc.SetTextForeground(colorMap.GetColor(colorMap.Min()+(colorMap.Max()-colorMap.Min())/2));
	dc.ResetBoundingBox();
	dc.DrawText(Converter::DoubleToScientificNotationString(colorMap.Min()+(colorMap.Max()-colorMap.Min())/2, 2), px2+5, py2 + (py1-py2)/2 - stepY);
	dc.DrawRectangle(wxRect(wxPoint(dc.MinX(), dc.MinY()), wxPoint(dc.MaxX(), dc.MaxY())));
	dc.DrawText(Converter::DoubleToScientificNotationString(colorMap.Min()+(colorMap.Max()-colorMap.Min())/2, 2), px2+5, py2 + (py1-py2)/2 - stepY);

	dc.SetTextForeground(colorMap.GetColor(colorMap.Min()));
	dc.ResetBoundingBox();
	dc.DrawText(Converter::DoubleToScientificNotationString(colorMap.Min(), 2), px1, py1+5);
	dc.DrawRectangle(wxRect(wxPoint(dc.MinX(), dc.MinY()), wxPoint(dc.MaxX(), dc.MaxY())));
	dc.DrawText(Converter::DoubleToScientificNotationString(colorMap.Min(), 2), px1, py1+5);

	dc.SetTextForeground(colorMap.GetColor(colorMap.Max()));
	dc.ResetBoundingBox();
	dc.DrawText(Converter::DoubleToScientificNotationString(colorMap.Max(), 2), px1, py2-20);
	dc.DrawRectangle(wxRect(wxPoint(dc.MinX(), dc.MinY()), wxPoint(dc.MaxX(), dc.MaxY())));
	dc.DrawText(Converter::DoubleToScientificNotationString(colorMap.Max(), 2), px1, py2-20);
}
// ---------------------------------------------------------------
// Classe VisualizationPanelWithFieldAtPlane
// ---------------------------------------------------------------
VisualizationPanelWithFieldAtPlane::VisualizationPanelWithFieldAtPlane(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result)
	: VisualizationPanel(parent, id, elementsInProject) , result(result) {
}
VisualizationPanelWithFieldAtPlane::~VisualizationPanelWithFieldAtPlane() {

}
void VisualizationPanelWithFieldAtPlane::ShowFrame(int frame) {
	((OpenGLStateMachineWithFieldAtPlane*)GetOpenGLStateMachine())->ShowFrame(frame);
}
void VisualizationPanelWithFieldAtPlane::SetLinearScale() {
	((OpenGLStateMachineWithFieldAtPlane*)GetOpenGLStateMachine())->SetLinearScale();
}
void VisualizationPanelWithFieldAtPlane::SetDBScale() {
	((OpenGLStateMachineWithFieldAtPlane*)GetOpenGLStateMachine())->SetDBScale();
}
OpenGLStateMachine* VisualizationPanelWithFieldAtPlane::CreateOpenGLStateMachine(OpenGLVisualization* canvas, ElementManagerSmartPointer elementsInProject) {
	return new OpenGLStateMachineWithFieldAtPlane(canvas, elementsInProject, result);
}
