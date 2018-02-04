/*
 * SheetMEFrame.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "SheetMEFrame.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"

SheetMEFrame::SheetMEFrame(wxWindow* parent, SheetME s, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), sheet(s) {

	CreateControlsAndInsert();
	UpdateControlsWithSheetInformation();
//	Fit();
}

SheetMEFrame::~SheetMEFrame() {

}

void SheetMEFrame::CreateControlsAndInsert() {
	/*********************************************/
	/* PAINÉL PRO USUÁRIO ESCOLHER O PLANO       */
	/*********************************************/
	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(2, 2, 0, 0);
	topGridSizer->AddGrowableCol(1);

	wxStaticText* lblSelectedPlane = new wxStaticText(this, wxID_STATIC, wxT("Cut at plane:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	plane = new wxComboBox(this, wxID_ANY, GetSelectedCut(), wxDefaultPosition, wxDefaultSize, GetAvailableCuts(), wxCB_READONLY);
	Connect(plane->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(SheetMEFrame::UserChangedSelectedPlane));
	topGridSizer->Add(lblSelectedPlane, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(plane, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	lblCutAt = new wxStaticText(this, wxID_STATIC, GetSelectedCut() + ":", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cutAt = UtilControls::NewTextCtrlForMathExpression(this);
	cutAt->Bind(wxEVT_SET_FOCUS, &SheetMEFrame::OnSetFocusEvent, this);
	cutAt->Bind(wxEVT_KILL_FOCUS, &SheetMEFrame::OnLostFocusEvent, this);
	topGridSizer->Add(lblCutAt, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(cutAt, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	/*********************************************/
	/* PAINÉL COM AS CAIXAS DE TEXTO PARA EDIÇÃO */
	/*********************************************/
	i0 = UtilControls::NewTextCtrlForMathExpression(this);
	i1 = UtilControls::NewTextCtrlForMathExpression(this);
	j0 = UtilControls::NewTextCtrlForMathExpression(this);
	j1 = UtilControls::NewTextCtrlForMathExpression(this);
	i0->Bind(wxEVT_SET_FOCUS, &SheetMEFrame::OnSetFocusEvent, this);
	i0->Bind(wxEVT_KILL_FOCUS, &SheetMEFrame::OnLostFocusEvent, this);
	j0->Bind(wxEVT_SET_FOCUS, &SheetMEFrame::OnSetFocusEvent, this);
	j0->Bind(wxEVT_KILL_FOCUS, &SheetMEFrame::OnLostFocusEvent, this);
	i1->Bind(wxEVT_SET_FOCUS, &SheetMEFrame::OnSetFocusEvent, this);
	i1->Bind(wxEVT_KILL_FOCUS, &SheetMEFrame::OnLostFocusEvent, this);
	j1->Bind(wxEVT_SET_FOCUS, &SheetMEFrame::OnSetFocusEvent, this);
	j1->Bind(wxEVT_KILL_FOCUS, &SheetMEFrame::OnLostFocusEvent, this);

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
void SheetMEFrame::OnSetFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == cutAt->GetId()) {
		cutAt->SetValue(cutAtParser.GetExpression());
		cutAt->SelectAll();
	} else if (event.GetId() == i0->GetId()) {
		i0->SetValue(i0Parser.GetExpression());
		i0->SelectAll();
	} else if (event.GetId() == i1->GetId()) {
		i1->SetValue(i1Parser.GetExpression());
		i1->SelectAll();
	} else if (event.GetId() == j0->GetId()) {
		j0->SetValue(j0Parser.GetExpression());
		j0->SelectAll();
	} else if (event.GetId() == j1->GetId()) {
		j1->SetValue(j1Parser.GetExpression());
		j1->SelectAll();
	}

	event.Skip();
}
void SheetMEFrame::OnLostFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == cutAt->GetId()) {
		cutAtParser.SetExpression(cutAt->GetValue());
		wxString value = cutAtParser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(cutAtParser.Eval(), 2) : "Invalid expression";
		cutAt->SetValue(value);
	} else if (event.GetId() == i0->GetId()) {
		i0Parser.SetExpression(i0->GetValue());
		wxString value = i0Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(i0Parser.Eval(), 2) : "Invalid expression";
		i0->SetValue(value);
	} else if (event.GetId() == i1->GetId()) {
		i1Parser.SetExpression(i1->GetValue());
		wxString value = i1Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(i1Parser.Eval(), 2) : "Invalid expression";
		i1->SetValue(value);
	} else if (event.GetId() == j0->GetId()) {
		j0Parser.SetExpression(j0->GetValue());
		wxString value = j0Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(j0Parser.Eval(), 2) : "Invalid expression";
		j0->SetValue(value);
	} else if (event.GetId() == j1->GetId()) {
		j1Parser.SetExpression(j1->GetValue());
		wxString value = j1Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(j1Parser.Eval(), 2) : "Invalid expression";
		j1->SetValue(value);
	}
	event.Skip();
}
void SheetMEFrame::UpdateControlsWithSheetInformation() {
	plane->SetValue(GetSelectedCut());

	wxString invalidExp = "Invalid expression";

	cutAt->SetValue(cutAtParser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(cutAtParser.Eval(), 2) : invalidExp);
	i0->SetValue(i0Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(i0Parser.Eval(), 2) : invalidExp);
	j0->SetValue(j0Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(j0Parser.Eval(), 2) : invalidExp);
	i1->SetValue(i1Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(i1Parser.Eval(), 2) : invalidExp);
	j1->SetValue(j1Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(j1Parser.Eval(), 2) : invalidExp);

	ChangeLabels();
}
void SheetMEFrame::ChangeLabels() {
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
bool SheetMEFrame::TransferDataFromWindow() {
	wxString cutAtExp = cutAtParser.GetExpression();
	wxString i0Exp = i0Parser.GetExpression();
	wxString j0Exp = j0Parser.GetExpression();
	wxString i1Exp = i1Parser.GetExpression();
	wxString j1Exp = j1Parser.GetExpression();

	if (plane->GetValue() == "X") {
		sheet.SetCutAtX(cutAtExp);
		sheet.SetY0Expression(i0Exp);
		sheet.SetY1Expression(i1Exp);
		sheet.SetZ0Expression(j0Exp);
		sheet.SetZ1Expression(j1Exp);
	} else if (plane->GetValue() == "Y") {
		sheet.SetCutAtY(cutAtExp);
		sheet.SetX0Expression(i0Exp);
		sheet.SetX1Expression(i1Exp);
		sheet.SetZ0Expression(j0Exp);
		sheet.SetZ1Expression(j1Exp);
	} else if (plane->GetValue() == "Z") {
		sheet.SetCutAtZ(cutAtExp);
		sheet.SetX0Expression(i0Exp);
		sheet.SetX1Expression(i1Exp);
		sheet.SetY0Expression(j0Exp);
		sheet.SetY1Expression(j1Exp);
	}
	return true;
	return true;
}

void SheetMEFrame::UserChangedSelectedPlane(wxCommandEvent& e) {
	ChangeLabels();
}
SheetME SheetMEFrame::GetSheetME() {
	return sheet;
}

void SheetMEFrame::SetSheetME(SheetME s) {
	sheet.Copy(&s);
	/* Copia os parsers do sheet */
	cutAtParser.SetExpression(sheet.GetCutAtExpression());
	if (sheet.IsCutAtX()) {
		i0Parser.SetExpression(sheet.GetY0Expression());
		j0Parser.SetExpression(sheet.GetZ0Expression());
		i1Parser.SetExpression(sheet.GetY1Expression());
		j1Parser.SetExpression(sheet.GetZ1Expression());
	} else if (sheet.IsCutAtY()) {
		i0Parser.SetExpression(sheet.GetX0Expression());
		j0Parser.SetExpression(sheet.GetZ0Expression());
		i1Parser.SetExpression(sheet.GetX1Expression());
		j1Parser.SetExpression(sheet.GetZ1Expression());
	} else if (sheet.IsCutAtZ()) {
		i0Parser.SetExpression(sheet.GetX0Expression());
		j0Parser.SetExpression(sheet.GetY0Expression());
		i1Parser.SetExpression(sheet.GetX1Expression());
		j1Parser.SetExpression(sheet.GetY1Expression());
	}
	UpdateControlsWithSheetInformation();
}
wxArrayString SheetMEFrame::GetAvailableCuts() {
	wxArrayString array;

	array.Add(wxT("X"));
	array.Add(wxT("Y"));
	array.Add(wxT("Z"));

	return array;
}
wxString SheetMEFrame::GetSelectedCut() {
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

