/*
 * DirectionPlaneWaveMEFrame.cpp
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWaveMEFrame.h"
#include "wx/valnum.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/util/controls/UtilControls.h"

DirectionPlaneWaveMEFrame::DirectionPlaneWaveMEFrame(wxWindow* parent, DirectionPlaneWaveME d, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), direction(d) {

	CreateEmptyControlsAndInsert();
	UpdateControlsState();
}

DirectionPlaneWaveMEFrame::~DirectionPlaneWaveMEFrame() {

}

void DirectionPlaneWaveMEFrame::OnSetFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == txtTheta->GetId()) {
		cout <<"X" << endl;
		txtTheta->SetValue(direction.GetThetaExpression());
		txtTheta->SelectAll();
	} else if (event.GetId() == txtPhi->GetId()) {
		txtPhi->SetValue(direction.GetPhiExpression());
		txtPhi->SelectAll();
	} else if (event.GetId() == txtPsi->GetId()) {
		txtPsi->SetValue(direction.GetPsiExpression());
		txtPsi->SelectAll();
	}
	event.Skip();
}
void DirectionPlaneWaveMEFrame::OnLostFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == txtTheta->GetId()) {
		direction.SetThetaExpression(txtTheta->GetValue());
		wxString value = direction.isThetaExpressionValid() ? Converter::DoubleToFormattedString(direction.GetTheta(), 2) : "Invalid expression";
		txtTheta->SetValue(value);
	} else if (event.GetId() == txtPhi->GetId()) {
		direction.SetPhiExpression(txtPhi->GetValue());
		wxString value = direction.isPhiExpressionValid() ? Converter::DoubleToFormattedString(direction.GetPhi(), 2) : "Invalid expression";
		txtPhi->SetValue(value);
	} else if (event.GetId() == txtPsi->GetId()) {
		direction.SetPsiExpression(txtPsi->GetValue());
		wxString value = direction.isPsiExpressionValid() ? Converter::DoubleToFormattedString(direction.GetPsi(), 2) : "Invalid expression";
		txtPsi->SetValue(value);
	}

	event.Skip();
}
void DirectionPlaneWaveMEFrame::CreateEmptyControlsAndInsert() {
	/* PAINEL DA ESQUERDA */
	wxFlexGridSizer* leftSizer = new wxFlexGridSizer(5, 2, 0, 0);
	leftSizer->AddGrowableCol(1);
	leftSizer->AddGrowableRow(1);
	leftSizer->AddGrowableRow(3);

	wxFont font(wxFONTSIZE_MEDIUM, wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL, false, "Symbol"/*, wxFONTENCODING_ISO8859_1*/);
	wxStaticText* lblTheta = new wxStaticText(this, wxID_STATIC, "q: ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT); // Unicode para teta wxT("\u03B8: ")
	wxStaticText* lblPhi = new wxStaticText(this, wxID_STATIC, "f: ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT); // Unicode para phi wxT("\u03D5: ")
	wxStaticText* lblPsi = new wxStaticText(this, wxID_STATIC, "y: ", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT); // Unicode para psi wxT("\u03A8: ")
	lblTheta->SetFont(font);
	lblPhi->SetFont(font);
	lblPsi->SetFont(font);
	txtTheta = UtilControls::NewTextCtrlForMathExpression(this);
	txtPhi = UtilControls::NewTextCtrlForMathExpression(this);
	txtPsi = UtilControls::NewTextCtrlForMathExpression(this);

	txtTheta->Bind(wxEVT_SET_FOCUS, &DirectionPlaneWaveMEFrame::OnSetFocusEvent, this);
	txtPhi->Bind(wxEVT_SET_FOCUS, &DirectionPlaneWaveMEFrame::OnSetFocusEvent, this);
	txtPsi->Bind(wxEVT_SET_FOCUS, &DirectionPlaneWaveMEFrame::OnSetFocusEvent, this);
	txtTheta->Bind(wxEVT_KILL_FOCUS, &DirectionPlaneWaveMEFrame::OnLostFocusEvent, this);
	txtPhi->Bind(wxEVT_KILL_FOCUS, &DirectionPlaneWaveMEFrame::OnLostFocusEvent, this);
	txtPsi->Bind(wxEVT_KILL_FOCUS, &DirectionPlaneWaveMEFrame::OnLostFocusEvent, this);

	leftSizer->Add(lblTheta, 0, wxALL | wxALIGN_LEFT, 5);
	leftSizer->Add(txtTheta, 0, wxALL | wxEXPAND, 5);
	leftSizer->Add(new wxStaticText(this, wxID_STATIC, wxT(" ")), 0, wxALL | wxEXPAND, 5);
	leftSizer->Add(new wxStaticText(this, wxID_STATIC, wxT(" ")), 0, wxALL | wxEXPAND, 5);
	leftSizer->Add(lblPhi, 0, wxALL | wxALIGN_LEFT, 5);
	leftSizer->Add(txtPhi, 0, wxALL | wxEXPAND, 5);
	leftSizer->Add(new wxStaticText(this, wxID_STATIC, wxT(" ")), 0, wxALL | wxEXPAND, 5);
	leftSizer->Add(new wxStaticText(this, wxID_STATIC, wxT(" ")), 0, wxALL | wxEXPAND, 5);
	leftSizer->Add(lblPsi, 0, wxALL | wxALIGN_LEFT, 5);
	leftSizer->Add(txtPsi, 0, wxALL | wxEXPAND, 5);

	/* PAINEL DA DIREITA */
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBitmap* bmp = new wxStaticBitmap(this, wxID_ANY, UtilResource::GetBitmap("directionPlaneWave"));
	bmp->SetSize(bmp->GetSize().GetWidth()/2, bmp->GetSize().GetHeight()/2);
	rightSizer->Add(bmp, 0, wxEXPAND | wxALL, 10);

	/* PAINEL QUE INCLUI O DA DIREITA E O DO ESQUERDA */
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(leftSizer,  wxALL);
	mainSizer->Add(rightSizer, wxALL);

	/* PAINEL DE BOTÕES */
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	/* PAINEL QUE CONTÉM TODOS OS OUTROS */
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(mainSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	/* Preenche os controles */
	UpdateControlsState();

	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void DirectionPlaneWaveMEFrame::UpdateControlsState() {
	wxString theta = direction.isThetaExpressionValid() ? Converter::DoubleToFormattedString(direction.GetTheta(), 2) : "Invalid expression";
	wxString phi = direction.isPhiExpressionValid() ? Converter::DoubleToFormattedString(direction.GetPhi(), 2) : "Invalid expression";
	wxString psi = direction.isPsiExpressionValid() ? Converter::DoubleToFormattedString(direction.GetPsi(), 2) : "Invalid expression";

	txtTheta->SetValue(theta);
	txtPhi->SetValue(phi);
	txtPsi->SetValue(psi);
}
bool DirectionPlaneWaveMEFrame::TransferDataFromWindow() {
	/* A variável point já está atualizada, pois isso é feito usando através da perda de foco */

	return true;
}
DirectionPlaneWaveME DirectionPlaneWaveMEFrame::GetDirection() {
	return direction;
}
void DirectionPlaneWaveMEFrame::SetDirection(DirectionPlaneWaveME d) {
	direction.Copy(&d);
	UpdateControlsState();
}
