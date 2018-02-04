/*
 * HowToShowSegmentInformationResult.cpp
 *
 *  Created on: 10/07/2014
 *      Author: leandrocarisio
 */

#include "HowToShowSegmentInformationResult.h"

#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/constants/Constants.h"
#include "wx/arrstr.h"

#include "emstudio/gui/elements/types/WireType.h"

#include <iostream>
using namespace::std;

namespace mom {

HowToShowSegmentInformationResult::HowToShowSegmentInformationResult(ElementManagerSmartPointer elementsInProject)
		: HowToShowResults(), elementsInProject(elementsInProject) {

}

HowToShowSegmentInformationResult::~HowToShowSegmentInformationResult() {
}

int HowToShowSegmentInformationResult::GetNumberOfTabs() {
	return 2;
}
wxString HowToShowSegmentInformationResult::GetTabName(int tabIndex) {
	ResultSmartPointer ptr = GetResult();
	SegmentInformationResult* segInformationResult = static_cast<SegmentInformationResult*>(ptr.get());

	wxString tabName;

	if (tabIndex == 0) {
		tabName = "Chart";
	} else if (tabIndex == 1) {
		tabName = "Table";
	}

	return tabName;
}
wxWindow* HowToShowSegmentInformationResult::GetWindow(int tabIndex, wxWindow* parent) {
	ResultSmartPointer ptrToResult = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptrToResult.get());
	wxWindow* ptr = 0;

	switch(tabIndex) {
	case 0:
	{
		ptr = new ShowSegmentInformationPanel(parent, elementsInProject, ptrToResult);
		break;
	}
	case 1:
	{
		ptr = GenerateGridForGenericTable(parent, new TableBaseForGenericTable(GetResult(), true));
		break;
	}
	} // END SWITCH

	return ptr;
}


// ---------------------------------------------------------------
// Classe ShowSegmentInformationPanel
// ---------------------------------------------------------------
ShowSegmentInformationPanel::ShowSegmentInformationPanel(wxWindow* parent, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result)
	:wxPanel(parent), elementsInProject(elementsInProject), result(result) {
	cout << "Ctor de ShowSegmentInformationPanel" << endl;
	CreateControlsAndInsert();
	cout << "Criou controles e inseriu!" << endl;
	/* Inicializa a camera como auto */
	SetCameraMode(btnAuto->GetId());
}
ShowSegmentInformationPanel::~ShowSegmentInformationPanel() {

}
void ShowSegmentInformationPanel::SetInformation(wxCommandEvent& event) {
	if (btnReal->GetValue())
		visualizationPanel->ShowReal();
	if (btnImag->GetValue())
		visualizationPanel->ShowImag();
	if (btnAmplitude->GetValue())
		visualizationPanel->ShowAmplitude();
	if (btnPhase->GetValue())
		visualizationPanel->ShowPhase();

	visualizationPanel->ForceRedraw();
}
void ShowSegmentInformationPanel::SetFrequency(wxCommandEvent& event) {
	SetFrequency(cboFrequency->GetSelection());
}
void ShowSegmentInformationPanel::SetFrequency(int selection) {
	visualizationPanel->SetFrequency(uniqueFrequenciesDouble[selection]);
	visualizationPanel->ForceRedraw();
}
void ShowSegmentInformationPanel::SetRadiusMultiplier(wxCommandEvent& event) {
	visualizationPanel->SetRadiusMultiplier(Converter::FormattedStringToDouble(cboRadiusMultiplier->GetValue()));
	visualizationPanel->ForceRedraw();
}
void ShowSegmentInformationPanel::SetCameraMode(int buttonId) {
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
void ShowSegmentInformationPanel::SetCameraMode(wxCommandEvent& event) {
	SetCameraMode(event.GetId());
}
void ShowSegmentInformationPanel::CreateControlsAndInsert() {
	cout << "ShowSegmentInformationPanel::CreateControlsAndInsert --- 1" << endl;
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

	Connect(btnAuto->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowSegmentInformationPanel::SetCameraMode));
	Connect(btnXY->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowSegmentInformationPanel::SetCameraMode));
	Connect(btnYZ->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowSegmentInformationPanel::SetCameraMode));
	Connect(btnXZ->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowSegmentInformationPanel::SetCameraMode));
	Connect(btnMove->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowSegmentInformationPanel::SetCameraMode));
	Connect(btnRotate->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowSegmentInformationPanel::SetCameraMode));
	Connect(btnZoom->GetId(), wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler(ShowSegmentInformationPanel::SetCameraMode));

	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsSizer->Add(btnAuto, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnXY, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnYZ, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnXZ, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnMove, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnRotate, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonsSizer->Add(btnZoom, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);

	cout << "ShowSegmentInformationPanel::CreateControlsAndInsert --- 2" << endl;
	/*******************************************************/
	/* PAINÉL COM O OPENGL                                 */
	/*******************************************************/
	visualizationPanel = new VisualizationPanelForSegmentInformation(this, wxID_ANY, elementsInProject, result);
	visualizationPanel->Create();

	cout << "ShowSegmentInformationPanel::CreateControlsAndInsert --- 2" << endl;
	/*******************************************************/
	/* PAINÉL COM O CONTROLE DO                            */
	/*******************************************************/
	wxBoxSizer* informationEditSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* boxInfoControl = new wxBoxSizer(wxVERTICAL);

	btnReal = new wxRadioButton(this, wxID_ANY, "Real");
	btnImag = new wxRadioButton(this, wxID_ANY, "Imaginary");
	btnAmplitude = new wxRadioButton(this, wxID_ANY, "Amplitude"); btnAmplitude->SetValue(true); visualizationPanel->ShowAmplitude();
	btnPhase = new wxRadioButton(this, wxID_ANY, "Phase");
	Connect(btnReal->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ShowSegmentInformationPanel::SetInformation));
	Connect(btnImag->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ShowSegmentInformationPanel::SetInformation));
	Connect(btnAmplitude->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ShowSegmentInformationPanel::SetInformation));
	Connect(btnPhase->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(ShowSegmentInformationPanel::SetInformation));
	boxInfoControl->Add(btnReal, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	boxInfoControl->Add(btnImag, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	boxInfoControl->Add(btnAmplitude, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	boxInfoControl->Add(btnPhase, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);

	wxArrayString radiusMultiplierOptions; double d;
	for (d = 0.125; d <= 32; d = d * 2)
		radiusMultiplierOptions.Add(Converter::DoubleToFormattedString(d,2));
	d = 1;
	cboRadiusMultiplier = new wxComboBox(this, wxID_ANY, Converter::DoubleToFormattedString(d,2), wxDefaultPosition, wxDefaultSize, radiusMultiplierOptions, wxCB_READONLY);
	Connect(cboRadiusMultiplier->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ShowSegmentInformationPanel::SetRadiusMultiplier));

	GenerateUniqueFrequenciesList();
	cboFrequency = new wxComboBox(this, wxID_ANY, uniqueFrequenciesString[0], wxDefaultPosition, wxDefaultSize, uniqueFrequenciesString, wxCB_READONLY);
	SetFrequency(0); // Seleciona a primeira frequência.
	Connect(cboFrequency->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ShowSegmentInformationPanel::SetFrequency));

	informationEditSizer->Add(boxInfoControl, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	informationEditSizer->Add(new wxStaticText(this, wxID_ANY, "Frequency:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	informationEditSizer->Add(cboFrequency, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	informationEditSizer->Add(new wxStaticText(this, wxID_ANY, "Radius multiplier:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	informationEditSizer->Add(cboRadiusMultiplier, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	topSizer->Add(visualizationPanel, 10, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	topSizer->Add(informationEditSizer, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	cout << "ShowSegmentInformationPanel::CreateControlsAndInsert --- 3" << endl;
	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
	topSizer->Layout();
	cout << "ShowSegmentInformationPanel::CreateControlsAndInsert --- 4" << endl;
}
// Existe pelo menos uma frequência.
// Da forma como foi construído o programa, todas as informações de frequência estão sequenciais. Por exemplo:
// freq0 col1 col2 col3
// freq0
// freq0
// freq1
// freq1
// freq1 etc
void ShowSegmentInformationPanel::GenerateUniqueFrequenciesList() {
	SegmentInformationResult* segInformationResult = static_cast<SegmentInformationResult*>(result.get());
	GenericTable::ColumnDataRepresentation frequenciesDouble = segInformationResult->GetFrequency();
	wxString freqUnit = segInformationResult->GetFrequencyUnit();

	double currentFrequency = frequenciesDouble[0];
	uniqueFrequenciesDouble.clear();
	uniqueFrequenciesString.clear();

	uniqueFrequenciesDouble.push_back(currentFrequency);
	uniqueFrequenciesString.push_back(Converter::DoubleToFormattedString(currentFrequency,4) + " " + freqUnit);

	for (int i = 1; i < frequenciesDouble.size(); i++) {
		if (currentFrequency != frequenciesDouble[i]) {
			currentFrequency = frequenciesDouble[i];
			uniqueFrequenciesDouble.push_back(currentFrequency);
			uniqueFrequenciesString.push_back(Converter::DoubleToFormattedString(currentFrequency,4) + " " + freqUnit);
		}
	}
}
// ---------------------------------------------------------------
// Classe VisualizationPanelForSegmentInformation
// ---------------------------------------------------------------
VisualizationPanelForSegmentInformation::VisualizationPanelForSegmentInformation(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result)
	: VisualizationPanel(parent, id, elementsInProject), elementsInProject(elementsInProject), result(result) {
	cout << "ctor de VisualizationPanelForSegmentInformation" << endl;
}
VisualizationPanelForSegmentInformation::~VisualizationPanelForSegmentInformation() {

}
void VisualizationPanelForSegmentInformation::SetRadiusMultiplier(double m) {
	((OpenGLStateMachineForSegmentInformation*)GetOpenGLStateMachine())->SetRadiusMultiplier(m);
}
void VisualizationPanelForSegmentInformation::SetFrequency(double f) {
	((OpenGLStateMachineForSegmentInformation*)GetOpenGLStateMachine())->SetFrequency(f);
}
void VisualizationPanelForSegmentInformation::ShowReal() {
	((OpenGLStateMachineForSegmentInformation*)GetOpenGLStateMachine())->ShowReal();
}
void VisualizationPanelForSegmentInformation::ShowImag() {
	((OpenGLStateMachineForSegmentInformation*)GetOpenGLStateMachine())->ShowImag();
}
void VisualizationPanelForSegmentInformation::ShowAmplitude() {
	((OpenGLStateMachineForSegmentInformation*)GetOpenGLStateMachine())->ShowAmplitude();
}
void VisualizationPanelForSegmentInformation::ShowPhase() {
	((OpenGLStateMachineForSegmentInformation*)GetOpenGLStateMachine())->ShowPhase();
}
OpenGLStateMachine* VisualizationPanelForSegmentInformation::CreateOpenGLStateMachine(OpenGLVisualization* canvas, ElementManagerSmartPointer elementsInProject) {
	return new OpenGLStateMachineForSegmentInformation(canvas, elementsInProject, result);
}

// ---------------------------------------------------------------
// Classe OpenGLStateMachineForSegmentInformation
// ---------------------------------------------------------------
OpenGLStateMachineForSegmentInformation::OpenGLStateMachineForSegmentInformation(wxGLCanvas *canvas, ElementManagerSmartPointer elementsInProject, ResultSmartPointer result)
	: OpenGLStateMachine(canvas, elementsInProject), startFreqIndex(-1), endFreqIndex(-1), radiusMultiplier(1), result(result), infoType("Real") {

	cout << "ctor de OpenGLStateMachineForSegmentInformation" << endl;

	SegmentInformationResult* segmentInfoResult = static_cast<SegmentInformationResult*>(result.get());

	infoReal = segmentInfoResult->GetInfoReal();
	infoImag = segmentInfoResult->GetInfoImag();

	for (int i = 0; i < infoReal.size(); i++) {
		complex<double> c = complex<double>(infoReal[i], infoImag[i]);
		infoAmplitude.push_back(std::abs(c));
		infoPhase.push_back(std::arg(c)*180/PI);
	}
	cout << "OK ctor de OpenGLStateMachineForSegmentInformation" << endl;
}
OpenGLStateMachineForSegmentInformation::~OpenGLStateMachineForSegmentInformation() {

}
bool OpenGLStateMachineForSegmentInformation::ShouldIDrawThisElement(ElementGUISmartPointer e) {
	wxString wireType = WireType().GetName();
	return e->GetType()->GetName() != wireType;
}
void OpenGLStateMachineForSegmentInformation::DoDraw() {
	OpenGLStateMachine::DoDraw();
	cout << "OpenGLStateMachineForSegmentInformation::DoDraw --- 1" << endl;
	SegmentInformationResult* segmentInformationResult = static_cast<SegmentInformationResult*>(result.get());

	ColorMap colorMap;
	std::vector<double> info;
	if (infoType == "Amplitude") {
		colorMap = colorMapAbs;
		info = infoAmplitude;
	} else if (infoType == "Phase") {
		colorMap = colorMapPhase;
		info = infoPhase;
	} else if (infoType == "Real") {
		colorMap = colorMapReal;
		info = infoReal;
	} else if (infoType == "Imag") {
		colorMap = colorMapImag;
		info = infoImag;
	}
	cout << "OpenGLStateMachineForSegmentInformation::DoDraw --- 2" << endl;
	GenericTable::ColumnDataRepresentation x1 = segmentInformationResult->GetX1();
	GenericTable::ColumnDataRepresentation y1 = segmentInformationResult->GetY1();
	GenericTable::ColumnDataRepresentation z1 = segmentInformationResult->GetZ1();
	GenericTable::ColumnDataRepresentation x2 = segmentInformationResult->GetX2();
	GenericTable::ColumnDataRepresentation y2 = segmentInformationResult->GetY2();
	GenericTable::ColumnDataRepresentation z2 = segmentInformationResult->GetZ2();
	GenericTable::ColumnDataRepresentation r  = segmentInformationResult->GetRadius();

	cout << "OpenGLStateMachineForSegmentInformation::DoDraw --- 3" << endl;
	if (startFreqIndex != -1 && endFreqIndex != -1) {
		for (int i = startFreqIndex; i <= endFreqIndex; i++) {
			wxColour x = colorMap.GetColor(info[i]);
			cout << infoType << "\t" << "valor: " << info[i] << "\t" << (int)(x.Red()) << "\t" << (int)(x.Green()) << "\t" << (int)(x.Blue()) << endl;
			SetColor(colorMap.GetColor(info[i]));
			DrawSegment(x1[i], y1[i], z1[i], x2[i], y2[i], z2[i], r[i]*radiusMultiplier, true);
		}
	}
	cout << "OpenGLStateMachineForSegmentInformation::DoDraw --- 4" << endl;
}
void OpenGLStateMachineForSegmentInformation::DrawDC(wxPaintDC& dc) {
	OpenGLStateMachine::DrawDC(dc);
	ColorMap colorMap;
	if (infoType == "Amplitude") {
		colorMap = colorMapAbs;
	} else if (infoType == "Phase") {
		colorMap = colorMapPhase;
	} else if (infoType == "Real") {
		colorMap = colorMapReal;
	} else if (infoType == "Imag") {
		colorMap = colorMapImag;
	}
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
void OpenGLStateMachineForSegmentInformation::SetRadiusMultiplier(double r) {
	radiusMultiplier = r;
}
void OpenGLStateMachineForSegmentInformation::SetFrequency(double f) {
	SegmentInformationResult* segInformationResult = static_cast<SegmentInformationResult*>(result.get());
	GenericTable::ColumnDataRepresentation frequenciesDouble = segInformationResult->GetFrequency();

	startFreqIndex = -1; endFreqIndex = -1;

	for (int i = 0; i < frequenciesDouble.size(); i++) {
		if (frequenciesDouble[i] == f) {
			if (startFreqIndex == -1)
				startFreqIndex = i;

			endFreqIndex = i;
		}
	}


	// Cria a escala de cores - escala Real
	double infoMinReal = 1e30;
	double infoMaxReal = -1e30;
	// Cria a escala de cores - escala Imag
	double infoMinImag = 1e30;
	double infoMaxImag = -1e30;
	// Cria a escala de cores - escala Amplitude
	double infoMinAbs = 1e30;
	double infoMaxAbs= -1e30;
	// Cria a escala de cores - escala Phase
	double infoMinPhase = 1e30;
	double infoMaxPhase = -1e30;

	for (int i = startFreqIndex; i <= endFreqIndex; i++) {
		/* limites para escala real */
		double value = infoReal[i];
		if (value < infoMinReal)
			infoMinReal = value;
		if (value > infoMaxReal)
			infoMaxReal = value;
		/* limites para escala Imag */
		value = infoImag[i];
		if (value < infoMinImag)
			infoMinImag = value;
		if (value > infoMaxImag)
			infoMaxImag = value;
		/* limites para escala Abs */
		value = infoAmplitude[i];
		if (value < infoMinAbs)
			infoMinAbs = value;
		if (value > infoMaxAbs)
			infoMaxAbs = value;
		/* limites para escala Abs */
		value = infoPhase[i];
		if (value < infoMinPhase)
			infoMinPhase = value;
		if (value > infoMaxPhase)
			infoMaxPhase = value;
	}
	cout << "infoMinReal = " << infoMinReal << endl;
	cout << "infoMaxReal = " << infoMaxReal << endl;
	cout << "infoMinImag = " << infoMinImag << endl;
	cout << "infoMaxImag = " << infoMaxImag << endl;
	cout << "infoMinAbs = " << infoMinAbs << endl;
	cout << "infoMaxAbs = " << infoMaxAbs << endl;
	cout << "infoMinPhase = " << infoMinPhase << endl;
	cout << "infoMaxPhase = " << infoMaxPhase << endl;
	colorMapReal  = ColorMap(100, infoMinReal, infoMaxReal);
	colorMapImag  = ColorMap(100, infoMinImag, infoMaxImag);
	colorMapAbs   = ColorMap(100, infoMinAbs, infoMaxAbs);
	colorMapPhase = ColorMap(100, infoMinPhase, infoMaxPhase);

}
void OpenGLStateMachineForSegmentInformation::ShowAmplitude() {
	infoType = "Amplitude";
}
void OpenGLStateMachineForSegmentInformation::ShowPhase() {
	infoType = "Phase";
}
void OpenGLStateMachineForSegmentInformation::ShowReal() {
	infoType = "Real";
}
void OpenGLStateMachineForSegmentInformation::ShowImag() {
	infoType = "Imag";
}

} /* namespace mom */
