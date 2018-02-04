/*
 * DirectionPlaneWaveFrame.cpp
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWaveFrame.h"
#include "wx/valnum.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/util/controls/UtilControls.h"

DirectionPlaneWaveFrame::DirectionPlaneWaveFrame(wxWindow* parent, DirectionPlaneWave d, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), direction(d) {

	CreateEmptyControlsAndInsert();
	UpdateControlsState();
}

DirectionPlaneWaveFrame::~DirectionPlaneWaveFrame() {
}

void DirectionPlaneWaveFrame::CreateEmptyControlsAndInsert() {
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
	txtTheta = UtilControls::NewTextCtrlWithDoubleValidator(this);
	txtPhi = UtilControls::NewTextCtrlWithDoubleValidator(this);
	txtPsi = UtilControls::NewTextCtrlWithDoubleValidator(this);

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
void DirectionPlaneWaveFrame::UpdateControlsState() {
	txtTheta->SetValue(Converter::DoubleToFormattedString_MaxPrecision(direction.GetTheta()));
	txtPhi->SetValue(Converter::DoubleToFormattedString_MaxPrecision(direction.GetPhi()));
	txtPsi->SetValue(Converter::DoubleToFormattedString_MaxPrecision(direction.GetPsi()));
}
bool DirectionPlaneWaveFrame::TransferDataFromWindow() {
	double theta = Converter::FormattedStringToDouble(txtTheta->GetValue());
	double phi = Converter::FormattedStringToDouble(txtPhi->GetValue());
	double psi = Converter::FormattedStringToDouble(txtPsi->GetValue());

	direction.SetTheta(theta);
	direction.SetPhi(phi);
	direction.SetPsi(psi);

	return true;
}
DirectionPlaneWave DirectionPlaneWaveFrame::GetDirection() {
	return direction;
}
void DirectionPlaneWaveFrame::SetDirection(DirectionPlaneWave d) {
	direction.Copy(&d);
	UpdateControlsState();
}
