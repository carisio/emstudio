/*
 * Point3DFrame.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "Point3DFrame.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"

Point3DFrame::Point3DFrame(wxWindow* parent, Point3D p, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), point(p) {

	CreateControlsAndInsert();
	UpdateControls();
}

void Point3DFrame::CreateControlsAndInsert() {
	wxBoxSizer* outterSizer = new wxBoxSizer(wxVERTICAL);

	/*********************************************/
	/* PAINÉL COM AS CAIXAS DE TEXTO PARA EDIÇÃO */
	/*********************************************/
	txtX = UtilControls::NewTextCtrlWithDoubleValidator(this);
	txtY = UtilControls::NewTextCtrlWithDoubleValidator(this);
	txtZ = UtilControls::NewTextCtrlWithDoubleValidator(this);

	wxStaticText* labelX = new wxStaticText(this, wxID_STATIC,
			wxT("x: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* labelY = new wxStaticText(this, wxID_STATIC,
			wxT("y: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* labelZ = new wxStaticText(this, wxID_STATIC,
			wxT("z: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

	wxFlexGridSizer* editGridSizer = new wxFlexGridSizer(1, 6, 0, 0);
	editGridSizer->Add(labelX, 0, wxALL | wxALIGN_LEFT, 5);
	editGridSizer->Add(txtX, 0, wxALL | wxEXPAND, 5);
	editGridSizer->Add(labelY, 0, wxALL | wxALIGN_LEFT, 5);
	editGridSizer->Add(txtY, 0, wxALL | wxEXPAND, 5);
	editGridSizer->Add(labelZ, 0, wxALL | wxALIGN_LEFT, 5);
	editGridSizer->Add(txtZ, 0, wxALL | wxEXPAND, 5);
	editGridSizer->AddGrowableCol(1);
	editGridSizer->AddGrowableCol(3);
	editGridSizer->AddGrowableCol(5);

	/*********************************************/
	/* PAINÉL COM BOTÕES OK E CANCELAR           */
	/*********************************************/
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	/*********************************************/
	/* PAINÉL COM OS DOIS PAINÉIS ACIMA          */
	/*********************************************/
	outterSizer->Add(editGridSizer,0,wxALIGN_CENTER);
	outterSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	SetSizer(outterSizer);
	outterSizer->Fit(this);
	outterSizer->SetSizeHints(this);
}

void Point3DFrame::UpdateControls() {
	txtX->SetValue(Converter::DoubleToFormattedString_MaxPrecision(point.GetX()));
	txtY->SetValue(Converter::DoubleToFormattedString_MaxPrecision(point.GetY()));
	txtZ->SetValue(Converter::DoubleToFormattedString_MaxPrecision(point.GetZ()));
}

bool Point3DFrame::TransferDataFromWindow() {
	point.SetX(Converter::FormattedStringToDouble(txtX->GetValue()));
	point.SetY(Converter::FormattedStringToDouble(txtY->GetValue()));
	point.SetZ(Converter::FormattedStringToDouble(txtZ->GetValue()));

	return true;
}

Point3D Point3DFrame::GetPoint3D() {
	return point;
}

void Point3DFrame::SetPoint3D(Point3D p) {
	point.Copy(&p);
	UpdateControls();
}

Point3DFrame::~Point3DFrame() {
}

