/*
 * SheetFrame.cpp
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#include "SheetFrame.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"

SheetFrame::SheetFrame(wxWindow* parent, Sheet s, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), sheet(s) {

	CreateControlsAndInsert();
	UpdateControlsWithSheetInformation();
//	Fit();
}

SheetFrame::~SheetFrame() {

}

void SheetFrame::CreateControlsAndInsert() {
	/*********************************************/
	/* PAINÉL PRO USUÁRIO ESCOLHER O PLANO       */
	/*********************************************/
	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(2, 2, 0, 0);
	topGridSizer->AddGrowableCol(1);

	wxStaticText* lblSelectedPlane = new wxStaticText(this, wxID_STATIC, wxT("Cut at plane:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	plane = new wxComboBox(this, wxID_ANY, GetSelectedCut(), wxDefaultPosition, wxDefaultSize, GetAvailableCuts(), wxCB_READONLY);
	Connect(plane->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(SheetFrame::UserChangedSelectedPlane));
	topGridSizer->Add(lblSelectedPlane, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(plane, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	lblCutAt = new wxStaticText(this, wxID_STATIC, GetSelectedCut() + ":", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cutAt = UtilControls::NewTextCtrlWithDoubleValidator(this);
	topGridSizer->Add(lblCutAt, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(cutAt, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	/*********************************************/
	/* PAINÉL COM AS CAIXAS DE TEXTO PARA EDIÇÃO */
	/*********************************************/
	i0 = UtilControls::NewTextCtrlWithDoubleValidator(this);
	i1 = UtilControls::NewTextCtrlWithDoubleValidator(this);
	j0 = UtilControls::NewTextCtrlWithDoubleValidator(this);
	j1 = UtilControls::NewTextCtrlWithDoubleValidator(this);

	lbli0 = new wxStaticText(this, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lbli1 = new wxStaticText(this, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblj0 = new wxStaticText(this, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	lblj1 = new wxStaticText(this, wxID_STATIC, wxT(""), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

	wxFlexGridSizer* editGridSizer = new wxFlexGridSizer(2, 4, 0, 0);
	editGridSizer->Add(lbli0, 0, wxALL | wxALIGN_LEFT, 5);
	editGridSizer->Add(i0, 0, wxALL | wxEXPAND, 5);
	editGridSizer->Add(lbli1, 0, wxALL | wxALIGN_LEFT, 5);
	editGridSizer->Add(i1, 0, wxALL | wxEXPAND, 5);
	editGridSizer->Add(lblj0, 0, wxALL | wxALIGN_LEFT, 5);
	editGridSizer->Add(j0, 0, wxALL | wxEXPAND, 5);
	editGridSizer->Add(lblj1, 0, wxALL | wxALIGN_LEFT, 5);
	editGridSizer->Add(j1, 0, wxALL | wxEXPAND, 5);
	editGridSizer->AddGrowableCol(1);
	editGridSizer->AddGrowableCol(3);

	/*********************************************/
	/* PAINÉL COM BOTÕES OK E CANCELAR           */
	/*********************************************/
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	/*********************************************/
	/* PAINÉL COM OS TRÊS PAINÉIS ACIMA          */
	/*********************************************/
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(topGridSizer,0,wxEXPAND);
	topSizer->Add(editGridSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	/* Preenche os controles */
	UpdateControlsWithSheetInformation();

	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void SheetFrame::UpdateControlsWithSheetInformation() {
	plane->SetValue(GetSelectedCut());
	cutAt->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetCutAt()));
	if (sheet.IsCutAtX()) {
		i0->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetY0()));
		j0->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetZ0()));
		i1->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetY1()));
		j1->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetZ1()));
	} else if (sheet.IsCutAtY()) {
		i0->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetX0()));
		j0->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetZ0()));
		i1->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetX1()));
		j1->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetZ1()));
	} else if (sheet.IsCutAtZ()) {
		i0->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetX0()));
		j0->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetY0()));
		i1->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetX1()));
		j1->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetY1()));
	}
	ChangeLabels();
}
void SheetFrame::ChangeLabels() {
	if (plane->GetValue() == "X") {
		lblCutAt->SetLabel("x:");
		lbli0->SetLabel("From y = ");
		lblj0->SetLabel("From z = ");
		lbli1->SetLabel("to y = ");
		lblj1->SetLabel("to z = ");
	} else if (plane->GetValue() == "Y") {
		lblCutAt->SetLabel("y:");
		lbli0->SetLabel("From x = ");
		lblj0->SetLabel("From z = ");
		lbli1->SetLabel("to x = ");
		lblj1->SetLabel("to z = ");
	} else if (plane->GetValue() == "Z") {
		lblCutAt->SetLabel("z:");
		lbli0->SetLabel("From x = ");
		lblj0->SetLabel("From y = ");
		lbli1->SetLabel("to x = ");
		lblj1->SetLabel("to y = ");
	}
}
bool SheetFrame::TransferDataFromWindow() {
	double d_cutAt = Converter::FormattedStringToDouble(cutAt->GetValue());
	double d_i0 = Converter::FormattedStringToDouble(i0->GetValue());
	double d_j0 = Converter::FormattedStringToDouble(j0->GetValue());
	double d_i1 = Converter::FormattedStringToDouble(i1->GetValue());
	double d_j1 = Converter::FormattedStringToDouble(j1->GetValue());

	if (plane->GetValue() == "X") {
		sheet.SetCutAtX(d_cutAt);
		sheet.SetY0(d_i0);
		sheet.SetY1(d_i1);
		sheet.SetZ0(d_j0);
		sheet.SetZ1(d_j1);
	} else if (plane->GetValue() == "Y") {
		sheet.SetCutAtY(d_cutAt);
		sheet.SetX0(d_i0);
		sheet.SetX1(d_i1);
		sheet.SetZ0(d_j0);
		sheet.SetZ1(d_j1);
	} else if (plane->GetValue() == "Z") {
		sheet.SetCutAtZ(d_cutAt);
		sheet.SetX0(d_i0);
		sheet.SetX1(d_i1);
		sheet.SetY0(d_j0);
		sheet.SetY1(d_j1);
	}
	return true;
}

void SheetFrame::UserChangedSelectedPlane(wxCommandEvent& e) {
	ChangeLabels();
}
Sheet SheetFrame::GetSheet() {
	return sheet;
}

void SheetFrame::SetSheet(Sheet s) {
	sheet.Copy(&s);
	UpdateControlsWithSheetInformation();
}
wxArrayString SheetFrame::GetAvailableCuts() {
	wxArrayString array;

	array.Add(wxT("X"));
	array.Add(wxT("Y"));
	array.Add(wxT("Z"));

	return array;
}
wxString SheetFrame::GetSelectedCut() {
	wxString plane = "";
	if (sheet.IsCutAtX()) {
		plane = "X";
	} else if (sheet.IsCutAtY()) {
		plane = "Y";
	} else if (sheet.IsCutAtZ()) {
		plane = "Z";
	}
	return plane;
}
