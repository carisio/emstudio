/*
 * RectangularTubeGeometryMEFrame.cpp
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#include "RectangularTubeGeometryMEFrame.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"
#include <iostream>

using namespace::std;

RectangularTubeGeometryMEFrame::RectangularTubeGeometryMEFrame(wxWindow* parent, RectangularTubeGeometryME g, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), geometry(g) {

	cout << "1" << endl;
	CreateControlsAndInsert();
	cout << "2" << endl;
	UpdateControlsWithGeometryInformation();
	cout << "3" << endl;
}

RectangularTubeGeometryMEFrame::~RectangularTubeGeometryMEFrame() {

}

void RectangularTubeGeometryMEFrame::CreateControlsAndInsert() {
	/****************************************************/
	/* PAINÉL PRO USUÁRIO ESCOLHER A ORIENTAÇÃO DO TUBO */
	/****************************************************/
	wxStaticText* lblOrientation = new wxStaticText(this, wxID_STATIC, wxT("Orientation: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cboOrientation = new wxComboBox(this, wxID_ANY, GetSelectedOrientation(), wxDefaultPosition, wxDefaultSize, GetAvailableOrientation(), wxCB_READONLY);
	Connect(cboOrientation->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(RectangularTubeGeometryMEFrame::UserChangedOrientation));

	wxFlexGridSizer* selectOrientationSizer = new wxFlexGridSizer(1, 2, 0, 0);
	selectOrientationSizer->AddGrowableCol(1);
	selectOrientationSizer->Add(lblOrientation, 0, wxALL | wxALIGN_LEFT, 5);
	selectOrientationSizer->Add(cboOrientation, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	/****************************************************/
	/* PAINÉL PRO USUÁRIO ENTRAR COM OS DADOS DA BASE   */
	/****************************************************/
	wxStaticBox *lblBaseTitle = new wxStaticBox(this, wxID_ANY, "Base:");
	wxStaticBoxSizer* baseSizer = new wxStaticBoxSizer(lblBaseTitle, wxVERTICAL);
	lblBaseCutAt = new wxStaticText(lblBaseTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblBaseCoord1Begin = new wxStaticText(lblBaseTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblBaseCoord1End = new wxStaticText(lblBaseTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblBaseCoord1Thickness = new wxStaticText(lblBaseTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblBaseCoord2Begin = new wxStaticText(lblBaseTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblBaseCoord2End = new wxStaticText(lblBaseTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblBaseCoord2Thickness = new wxStaticText(lblBaseTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

	txtBaseCoord1Begin = UtilControls::NewTextCtrlForMathExpression(lblBaseTitle);
	txtBaseCoord1End = UtilControls::NewTextCtrlForMathExpression(lblBaseTitle);
	txtBaseCoord1Thickness = UtilControls::NewTextCtrlForMathExpression(lblBaseTitle);
	txtBaseCoord2Begin = UtilControls::NewTextCtrlForMathExpression(lblBaseTitle);
	txtBaseCoord2End = UtilControls::NewTextCtrlForMathExpression(lblBaseTitle);
	txtBaseCoord2Thickness = UtilControls::NewTextCtrlForMathExpression(lblBaseTitle);
	txtBaseCutAt = UtilControls::NewTextCtrlForMathExpression(lblBaseTitle);
	txtBaseCutAt->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtBaseCutAt->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtBaseCoord1Begin->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtBaseCoord1Begin->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtBaseCoord1End->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtBaseCoord1End->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtBaseCoord1Thickness->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtBaseCoord1Thickness->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtBaseCoord2Begin->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtBaseCoord2Begin->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtBaseCoord2End->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtBaseCoord2End->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtBaseCoord2Thickness->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtBaseCoord2Thickness->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);

//	wxFlexGridSizer* baseCutAtSizer = new wxFlexGridSizer(1, 2, 0, 0);
//	baseCutAtSizer->AddGrowableCol(1);
//	baseCutAtSizer->Add(lblBaseCutAt, 0, wxALL | wxALIGN_LEFT, 5);
//	baseCutAtSizer->Add(txtBaseCutAt, 0, wxALL | wxEXPAND, 5);

	wxFlexGridSizer* baseCoordsSizer = new wxFlexGridSizer(3, 6, 0, 0);
	baseCoordsSizer->AddGrowableCol(1);
	baseCoordsSizer->AddGrowableCol(3);
	baseCoordsSizer->AddGrowableCol(5);
	baseCoordsSizer->Add(lblBaseCoord1Begin, 0, wxALL | wxALIGN_LEFT, 5);
	baseCoordsSizer->Add(txtBaseCoord1Begin, 0, wxALL | wxEXPAND, 5);
	baseCoordsSizer->Add(lblBaseCoord1End, 0, wxALL | wxALIGN_LEFT, 5);
	baseCoordsSizer->Add(txtBaseCoord1End, 0, wxALL | wxEXPAND, 5);
	baseCoordsSizer->Add(lblBaseCoord1Thickness, 0, wxALL | wxALIGN_LEFT, 5);
	baseCoordsSizer->Add(txtBaseCoord1Thickness, 0, wxALL | wxEXPAND, 5);
	baseCoordsSizer->Add(lblBaseCoord2Begin, 0, wxALL | wxALIGN_LEFT, 5);
	baseCoordsSizer->Add(txtBaseCoord2Begin, 0, wxALL | wxEXPAND, 5);
	baseCoordsSizer->Add(lblBaseCoord2End, 0, wxALL | wxALIGN_LEFT, 5);
	baseCoordsSizer->Add(txtBaseCoord2End, 0, wxALL | wxEXPAND, 5);
	baseCoordsSizer->Add(lblBaseCoord2Thickness, 0, wxALL | wxALIGN_LEFT, 5);
	baseCoordsSizer->Add(txtBaseCoord2Thickness, 0, wxALL | wxEXPAND, 5);
	baseCoordsSizer->Add(lblBaseCutAt, 0, wxALL | wxALIGN_LEFT, 5);
	baseCoordsSizer->Add(txtBaseCutAt, 0, wxALL | wxEXPAND, 5);

//	baseSizer->Add(baseCutAtSizer);
	baseSizer->Add(baseCoordsSizer);

	/****************************************************/
	/* PAINÉL PRO USUÁRIO ENTRAR COM OS DADOS DO TOPO   */
	/****************************************************/
	wxStaticBox *lblTopTitle = new wxStaticBox(this, wxID_ANY, "Top:");
	wxStaticBoxSizer *topSizer = new wxStaticBoxSizer(lblTopTitle, wxVERTICAL);
	lblTopCutAt = new wxStaticText(lblTopTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblTopCoord1Begin = new wxStaticText(lblTopTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblTopCoord1End = new wxStaticText(lblTopTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblTopCoord1Thickness = new wxStaticText(lblTopTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblTopCoord2Begin = new wxStaticText(lblTopTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblTopCoord2End = new wxStaticText(lblTopTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblTopCoord2Thickness = new wxStaticText(lblTopTitle, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	txtTopCoord1Begin = UtilControls::NewTextCtrlForMathExpression(lblTopTitle);
	txtTopCoord1End = UtilControls::NewTextCtrlForMathExpression(lblTopTitle);
	txtTopCoord1Thickness = UtilControls::NewTextCtrlForMathExpression(lblTopTitle);
	txtTopCoord2Begin = UtilControls::NewTextCtrlForMathExpression(lblTopTitle);
	txtTopCoord2End = UtilControls::NewTextCtrlForMathExpression(lblTopTitle);
	txtTopCoord2Thickness = UtilControls::NewTextCtrlForMathExpression(lblTopTitle);
	txtTopCutAt = UtilControls::NewTextCtrlForMathExpression(lblTopTitle);
	txtTopCutAt->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtTopCutAt->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtTopCoord1Begin->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtTopCoord1Begin->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtTopCoord1End->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtTopCoord1End->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtTopCoord1Thickness->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtTopCoord1Thickness->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtTopCoord2Begin->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtTopCoord2Begin->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtTopCoord2End->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtTopCoord2End->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);
	txtTopCoord2Thickness->Bind(wxEVT_SET_FOCUS, &RectangularTubeGeometryMEFrame::OnSetFocusEvent, this);
	txtTopCoord2Thickness->Bind(wxEVT_KILL_FOCUS, &RectangularTubeGeometryMEFrame::OnLostFocusEvent, this);

//	wxFlexGridSizer* topCutAtSizer = new wxFlexGridSizer(1, 2, 0, 0);
//	topCutAtSizer->AddGrowableCol(1);
//	topCutAtSizer->Add(lblTopCutAt, 0, wxALL | wxALIGN_LEFT, 5);
//	topCutAtSizer->Add(txtTopCutAt, 0, wxALL | wxEXPAND, 5);

	wxFlexGridSizer* topCoordsSizer = new wxFlexGridSizer(3, 6, 0, 0);
	topCoordsSizer->AddGrowableCol(1);
	topCoordsSizer->AddGrowableCol(3);
	topCoordsSizer->AddGrowableCol(5);
	topCoordsSizer->Add(lblTopCoord1Begin, 0, wxALL | wxALIGN_LEFT, 5);
	topCoordsSizer->Add(txtTopCoord1Begin, 0, wxALL | wxEXPAND, 5);
	topCoordsSizer->Add(lblTopCoord1End, 0, wxALL | wxALIGN_LEFT, 5);
	topCoordsSizer->Add(txtTopCoord1End, 0, wxALL | wxEXPAND, 5);
	topCoordsSizer->Add(lblTopCoord1Thickness, 0, wxALL | wxALIGN_LEFT, 5);
	topCoordsSizer->Add(txtTopCoord1Thickness, 0, wxALL | wxEXPAND, 5);
	topCoordsSizer->Add(lblTopCoord2Begin, 0, wxALL | wxALIGN_LEFT, 5);
	topCoordsSizer->Add(txtTopCoord2Begin, 0, wxALL | wxEXPAND, 5);
	topCoordsSizer->Add(lblTopCoord2End, 0, wxALL | wxALIGN_LEFT, 5);
	topCoordsSizer->Add(txtTopCoord2End, 0, wxALL | wxEXPAND, 5);
	topCoordsSizer->Add(lblTopCoord2Thickness, 0, wxALL | wxALIGN_LEFT, 5);
	topCoordsSizer->Add(txtTopCoord2Thickness, 0, wxALL | wxEXPAND, 5);
	topCoordsSizer->Add(lblTopCutAt, 0, wxALL | wxALIGN_LEFT, 5);
	topCoordsSizer->Add(txtTopCutAt, 0, wxALL | wxEXPAND, 5);

//	topSizer->Add(topCutAtSizer);
	topSizer->Add(topCoordsSizer);

	/*********************************************/
	/* PAINÉL COM BOTÕES OK E CANCELAR           */
	/*********************************************/
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER | wxEXPAND, 5);

	/****************************************/
	/* PAINÉL COM OS PAINÉIS ACIMA          */
	/****************************************/
	wxFlexGridSizer* mainSizer = new wxFlexGridSizer(4, 1, 0, 0);
	mainSizer->AddGrowableRow(1);
	mainSizer->AddGrowableRow(2);
	mainSizer->Add(selectOrientationSizer,0,wxEXPAND);
	mainSizer->Add(baseSizer, 0, wxALL | wxALIGN_LEFT | wxEXPAND);
	mainSizer->Add(topSizer, 0, wxALL | wxALIGN_LEFT | wxEXPAND);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

	/* Preenche os controles */
	UpdateControlsWithGeometryInformation();

	/* Adequa o tamanho */
	SetSizer(mainSizer);
	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);
}

void RectangularTubeGeometryMEFrame::OnSetFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == txtBaseCutAt->GetId()) {
		txtBaseCutAt->SetValue(geometry.GetBaseCutAtExpression());
		txtBaseCutAt->SelectAll();
	} else if (event.GetId() == txtBaseCoord1Begin->GetId()) {
		txtBaseCoord1Begin->SetValue(geometry.GetBaseCoord1BeginExpression());
		txtBaseCoord1Begin->SelectAll();
	} else if (event.GetId() == txtBaseCoord1End->GetId()) {
		txtBaseCoord1End->SetValue(geometry.GetBaseCoord1EndExpression());
		txtBaseCoord1End->SelectAll();
	} else if (event.GetId() == txtBaseCoord1Thickness->GetId()) {
		txtBaseCoord1Thickness->SetValue(geometry.GetBaseCoord1ThicknessExpression());
		txtBaseCoord1Thickness->SelectAll();
	} else if (event.GetId() == txtBaseCoord2Begin->GetId()) {
		txtBaseCoord2Begin->SetValue(geometry.GetBaseCoord2BeginExpression());
		txtBaseCoord2Begin->SelectAll();
	} else if (event.GetId() == txtBaseCoord2End->GetId()) {
		txtBaseCoord2End->SetValue(geometry.GetBaseCoord2EndExpression());
		txtBaseCoord2End->SelectAll();
	} else if (event.GetId() == txtBaseCoord2Thickness->GetId()) {
		txtBaseCoord2Thickness->SetValue(geometry.GetBaseCoord2ThicknessExpression());
		txtBaseCoord2Thickness->SelectAll();
	} else if (event.GetId() == txtTopCutAt->GetId()) {
		txtTopCutAt->SetValue(geometry.GetTopCutAtExpression());
		txtTopCutAt->SelectAll();
	} else if (event.GetId() == txtTopCoord1Begin->GetId()) {
		txtTopCoord1Begin->SetValue(geometry.GetTopCoord1BeginExpression());
		txtTopCoord1Begin->SelectAll();
	} else if (event.GetId() == txtTopCoord1End->GetId()) {
		txtTopCoord1End->SetValue(geometry.GetTopCoord1EndExpression());
		txtTopCoord1End->SelectAll();
	} else if (event.GetId() == txtTopCoord1Thickness->GetId()) {
		txtTopCoord1Thickness->SetValue(geometry.GetTopCoord1ThicknessExpression());
		txtTopCoord1Thickness->SelectAll();
	} else if (event.GetId() == txtTopCoord2Begin->GetId()) {
		txtTopCoord2Begin->SetValue(geometry.GetTopCoord2BeginExpression());
		txtTopCoord2Begin->SelectAll();
	} else if (event.GetId() == txtTopCoord2End->GetId()) {
		txtTopCoord2End->SetValue(geometry.GetTopCoord2EndExpression());
		txtTopCoord2End->SelectAll();
	} else if (event.GetId() == txtTopCoord2Thickness->GetId()) {
		txtTopCoord2Thickness->SetValue(geometry.GetTopCoord2ThicknessExpression());
		txtTopCoord2Thickness->SelectAll();
	}

	event.Skip();
}
void RectangularTubeGeometryMEFrame::OnLostFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == txtBaseCutAt->GetId()) {
		geometry.SetBaseCutAtExpression(txtBaseCutAt->GetValue());
		wxString value = geometry.IsBaseCutAtExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCutAt(), 2) : "Invalid expression";
		txtBaseCutAt->SetValue(value);
	} else if (event.GetId() == txtBaseCoord1Begin->GetId()) {
		geometry.SetBaseCoord1BeginExpression(txtBaseCoord1Begin->GetValue());
		wxString value = geometry.IsBaseCoord1BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord1Begin(), 2) : "Invalid expression";
		txtBaseCoord1Begin->SetValue(value);
	} else if (event.GetId() == txtBaseCoord1End->GetId()) {
		geometry.SetBaseCoord1EndExpression(txtBaseCoord1End->GetValue());
		wxString value = geometry.IsBaseCoord1EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord1End(), 2) : "Invalid expression";
		txtBaseCoord1End->SetValue(value);
	} else if (event.GetId() == txtBaseCoord1Thickness->GetId()) {
		geometry.SetBaseCoord1ThicknessExpression(txtBaseCoord1Thickness->GetValue());
		wxString value = geometry.IsBaseCoord1ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord1Thickness(), 2) : "Invalid expression";
		txtBaseCoord1Thickness->SetValue(value);
	} else if (event.GetId() == txtBaseCoord2Begin->GetId()) {
		geometry.SetBaseCoord2BeginExpression(txtBaseCoord2Begin->GetValue());
		wxString value = geometry.IsBaseCoord2BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord2Begin(), 2) : "Invalid expression";
		txtBaseCoord2Begin->SetValue(value);
	} else if (event.GetId() == txtBaseCoord2End->GetId()) {
		geometry.SetBaseCoord2EndExpression(txtBaseCoord2End->GetValue());
		wxString value = geometry.IsBaseCoord2EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord2End(), 2) : "Invalid expression";
		txtBaseCoord2End->SetValue(value);
	} else if (event.GetId() == txtBaseCoord2Thickness->GetId()) {
		geometry.SetBaseCoord2ThicknessExpression(txtBaseCoord2Thickness->GetValue());
		wxString value = geometry.IsBaseCoord2ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord2Thickness(), 2) : "Invalid expression";
		txtBaseCoord2Thickness->SetValue(value);
	} else 	if (event.GetId() == txtTopCutAt->GetId()) {
		geometry.SetTopCutAtExpression(txtTopCutAt->GetValue());
		wxString value = geometry.IsTopCutAtExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCutAt(), 2) : "Invalid expression";
		txtTopCutAt->SetValue(value);
	} else if (event.GetId() == txtTopCoord1Begin->GetId()) {
		geometry.SetTopCoord1BeginExpression(txtTopCoord1Begin->GetValue());
		wxString value = geometry.IsTopCoord1BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord1Begin(), 2) : "Invalid expression";
		txtTopCoord1Begin->SetValue(value);
	} else if (event.GetId() == txtTopCoord1End->GetId()) {
		geometry.SetTopCoord1EndExpression(txtTopCoord1End->GetValue());
		wxString value = geometry.IsTopCoord1EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord1End(), 2) : "Invalid expression";
		txtTopCoord1End->SetValue(value);
	} else if (event.GetId() == txtTopCoord1Thickness->GetId()) {
		geometry.SetTopCoord1ThicknessExpression(txtTopCoord1Thickness->GetValue());
		wxString value = geometry.IsTopCoord1ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord1Thickness(), 2) : "Invalid expression";
		txtTopCoord1Thickness->SetValue(value);
	} else if (event.GetId() == txtTopCoord2Begin->GetId()) {
		geometry.SetTopCoord2BeginExpression(txtTopCoord2Begin->GetValue());
		wxString value = geometry.IsTopCoord2BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord2Begin(), 2) : "Invalid expression";
		txtTopCoord2Begin->SetValue(value);
	} else if (event.GetId() == txtTopCoord2End->GetId()) {
		geometry.SetTopCoord2EndExpression(txtTopCoord2End->GetValue());
		wxString value = geometry.IsTopCoord2EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord2End(), 2) : "Invalid expression";
		txtTopCoord2End->SetValue(value);
	} else if (event.GetId() == txtTopCoord2Thickness->GetId()) {
		geometry.SetTopCoord2ThicknessExpression(txtTopCoord2Thickness->GetValue());
		wxString value = geometry.IsTopCoord2ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord2Thickness(), 2) : "Invalid expression";
		txtTopCoord2Thickness->SetValue(value);
	}
	event.Skip();
}
void RectangularTubeGeometryMEFrame::UpdateControlsWithGeometryInformation() {
	cboOrientation->SetValue(GetSelectedOrientation());

	wxString invalidExp = "Invalid expression";

	txtBaseCutAt->SetValue(geometry.IsBaseCutAtExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCutAt(), 2) : invalidExp);
	txtBaseCoord1Begin->SetValue(geometry.IsBaseCoord1BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord1Begin(), 2) : invalidExp);
	txtBaseCoord1End->SetValue(geometry.IsBaseCoord1EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord1End(), 2) : invalidExp);
	txtBaseCoord1Thickness->SetValue(geometry.IsBaseCoord1ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord1Thickness(), 2) : invalidExp);
	txtBaseCoord2Begin->SetValue(geometry.IsBaseCoord2BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord2Begin(), 2) : invalidExp);
	txtBaseCoord2End->SetValue(geometry.IsBaseCoord2EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord2End(), 2) : invalidExp);
	txtBaseCoord2Thickness->SetValue(geometry.IsBaseCoord2ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetBaseCoord2Thickness(), 2) : invalidExp);

	txtTopCutAt->SetValue(geometry.IsTopCutAtExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCutAt(), 2) : invalidExp);
	txtTopCoord1Begin->SetValue(geometry.IsTopCoord1BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord1Begin(), 2) : invalidExp);
	txtTopCoord1End->SetValue(geometry.IsTopCoord1EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord1End(), 2) : invalidExp);
	txtTopCoord1Thickness->SetValue(geometry.IsTopCoord1ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord1Thickness(), 2) : invalidExp);
	txtTopCoord2Begin->SetValue(geometry.IsTopCoord2BeginExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord2Begin(), 2) : invalidExp);
	txtTopCoord2End->SetValue(geometry.IsTopCoord2EndExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord2End(), 2) : invalidExp);
	txtTopCoord2Thickness->SetValue(geometry.IsTopCoord2ThicknessExpressionValid() ? Converter::DoubleToFormattedString(geometry.GetTopCoord2Thickness(), 2) : invalidExp);

	ChangeLabels();
}
void RectangularTubeGeometryMEFrame::ChangeLabels() {
	if (cboOrientation->GetValue() == "X") {
		lblBaseCutAt->SetLabel("Cut at:");
		lblBaseCoord1Begin->SetLabel("From y = ");
		lblBaseCoord1End->SetLabel("to y = ");
		lblBaseCoord1Thickness->SetLabel("Thickness (y): ");
		lblBaseCoord2Begin->SetLabel("From z = ");
		lblBaseCoord2End->SetLabel("to z = ");
		lblBaseCoord2Thickness->SetLabel("Thickness (z):");
		lblTopCutAt->SetLabel("Cut at:");
		lblTopCoord1Begin->SetLabel("From y = ");
		lblTopCoord1End->SetLabel("to y = ");
		lblTopCoord1Thickness->SetLabel("Thickness (y): ");
		lblTopCoord2Begin->SetLabel("From z = ");
		lblTopCoord2End->SetLabel("to z = ");
		lblTopCoord2Thickness->SetLabel("Thickness (z):");
	} else if (cboOrientation->GetValue() == "Y") {
		lblBaseCutAt->SetLabel("Cut at:");
		lblBaseCoord1Begin->SetLabel("From x = ");
		lblBaseCoord1End->SetLabel("to x = ");
		lblBaseCoord1Thickness->SetLabel("Thickness (x): ");
		lblBaseCoord2Begin->SetLabel("From z = ");
		lblBaseCoord2End->SetLabel("to z = ");
		lblBaseCoord2Thickness->SetLabel("Thickness (z):");
		lblTopCutAt->SetLabel("Cut at:");
		lblTopCoord1Begin->SetLabel("From x = ");
		lblTopCoord1End->SetLabel("to x = ");
		lblTopCoord1Thickness->SetLabel("Thickness (x): ");
		lblTopCoord2Begin->SetLabel("From z = ");
		lblTopCoord2End->SetLabel("to z = ");
		lblTopCoord2Thickness->SetLabel("Thickness (z):");
	} else if (cboOrientation->GetValue() == "Z") {
		lblBaseCutAt->SetLabel("Cut at:");
		lblBaseCoord1Begin->SetLabel("From x = ");
		lblBaseCoord1End->SetLabel("to x = ");
		lblBaseCoord1Thickness->SetLabel("Thickness (x): ");
		lblBaseCoord2Begin->SetLabel("From y = ");
		lblBaseCoord2End->SetLabel("to y = ");
		lblBaseCoord2Thickness->SetLabel("Thickness (y):");
		lblTopCutAt->SetLabel("Cut at:");
		lblTopCoord1Begin->SetLabel("From x = ");
		lblTopCoord1End->SetLabel("to x = ");
		lblTopCoord1Thickness->SetLabel("Thickness (x): ");
		lblTopCoord2Begin->SetLabel("From y = ");
		lblTopCoord2End->SetLabel("to y = ");
		lblTopCoord2Thickness->SetLabel("Thickness (y):");
	}
}
bool RectangularTubeGeometryMEFrame::TransferDataFromWindow() {
	return true;
}

void RectangularTubeGeometryMEFrame::UserChangedOrientation(wxCommandEvent& e) {
	if (cboOrientation->GetValue() == "X")
		geometry.SetXOriented();
	else if (cboOrientation->GetValue() == "Y")
		geometry.SetYOriented();
	else if (cboOrientation->GetValue() == "Z")
		geometry.SetZOriented();
	ChangeLabels();
}

RectangularTubeGeometryME RectangularTubeGeometryMEFrame::GetRectangularTubeGeometryME() {
	return geometry;
}

void RectangularTubeGeometryMEFrame::SetRectangularTubeGeometryME (RectangularTubeGeometryME g) {
	geometry.Copy(&g);
	UpdateControlsWithGeometryInformation();
}
wxArrayString RectangularTubeGeometryMEFrame::GetAvailableOrientation() {
	wxArrayString array;

	array.Add(wxT("X"));
	array.Add(wxT("Y"));
	array.Add(wxT("Z"));

	return array;
}
wxString RectangularTubeGeometryMEFrame::GetSelectedOrientation() {
	if (geometry.IsXOriented()) return "X";
	if (geometry.IsYOriented()) return "Y";
	if (geometry.IsZOriented()) return "Z";
	return "";
}

