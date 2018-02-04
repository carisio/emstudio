/*
 * Point3DMEMEFrame.cpp
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#include "Point3DMEFrame.h"

#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"

#include <iostream>
using namespace::std;

Point3DMEFrame::Point3DMEFrame(wxWindow* parent, Point3DME p, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), point(p) {

	CreateControlsAndInsert();
	UpdateControls();
}
void Point3DMEFrame::OnSetFocusEvent(wxFocusEvent& event) {
	cout << "--------" << endl << "SetFocus" << endl;
	if (event.GetId() == txtX->GetId()) {
		cout <<"X" << endl;
		cout << "point.GetXExpression() = " << point.GetXExpression() << endl;
		txtX->SetValue(point.GetXExpression());
		txtX->SelectAll();
	} else if (event.GetId() == txtY->GetId()) {
		txtY->SetValue(point.GetYExpression());
		txtY->SelectAll();
	} else if (event.GetId() == txtZ->GetId()) {
		txtZ->SetValue(point.GetZExpression());
		txtZ->SelectAll();
	}

	event.Skip();
}
void Point3DMEFrame::OnLostFocusEvent(wxFocusEvent& event) {
	cout << "--------" << endl << "LostFocus" << endl;
	if (event.GetId() == txtX->GetId()) {
		cout << "txtX->GetValue = " << txtX->GetValue() << endl;
		point.SetXExpression(txtX->GetValue());
		cout << "point.GetXExpression = " << point.GetXExpression() << endl;
		wxString value = point.isXExpressionValid() ? Converter::DoubleToFormattedString(point.GetX(), 2) : "Invalid expression";
		cout << "Value = " << value << endl;
		txtX->SetValue(value);
	} else if (event.GetId() == txtY->GetId()) {
		point.SetYExpression(txtY->GetValue());
		wxString value = point.isYExpressionValid() ? Converter::DoubleToFormattedString(point.GetY(), 2) : "Invalid expression";
		txtY->SetValue(value);
	} else if (event.GetId() == txtZ->GetId()) {
		point.SetZExpression(txtZ->GetValue());
		wxString value = point.isZExpressionValid() ? Converter::DoubleToFormattedString(point.GetZ(), 2) : "Invalid expression";
		txtZ->SetValue(value);
	}

	event.Skip();
}
void Point3DMEFrame::CreateControlsAndInsert() {
	wxBoxSizer* outterSizer = new wxBoxSizer(wxVERTICAL);

	/*********************************************/
	/* PAINÉL COM AS CAIXAS DE TEXTO PARA EDIÇÃO */
	/*********************************************/
	txtX = UtilControls::NewTextCtrlForMathExpression(this);
	txtY = UtilControls::NewTextCtrlForMathExpression(this);
	txtZ = UtilControls::NewTextCtrlForMathExpression(this);

	txtX->Bind(wxEVT_SET_FOCUS, &Point3DMEFrame::OnSetFocusEvent, this);
	txtY->Bind(wxEVT_SET_FOCUS, &Point3DMEFrame::OnSetFocusEvent, this);
	txtZ->Bind(wxEVT_SET_FOCUS, &Point3DMEFrame::OnSetFocusEvent, this);
	txtX->Bind(wxEVT_KILL_FOCUS, &Point3DMEFrame::OnLostFocusEvent, this);
	txtY->Bind(wxEVT_KILL_FOCUS, &Point3DMEFrame::OnLostFocusEvent, this);
	txtZ->Bind(wxEVT_KILL_FOCUS, &Point3DMEFrame::OnLostFocusEvent, this);
//	txtX->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnSetFocusEvent));
//	txtY->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnSetFocusEvent));
//	txtZ->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnSetFocusEvent));
//	txtX->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnLostFocusEvent));
//	txtY->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnLostFocusEvent));
//	txtZ->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnLostFocusEvent));

//	Connect(txtX->GetId(), wxEVT_SET_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnSetFocusEvent));
//	Connect(txtY->GetId(), wxEVT_SET_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnSetFocusEvent));
//	Connect(txtZ->GetId(), wxEVT_SET_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnSetFocusEvent));
//	Connect(txtX->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnLostFocusEvent));
//	Connect(txtY->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnLostFocusEvent));
//	Connect(txtZ->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(Point3DMEFrame::OnLostFocusEvent));


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

void Point3DMEFrame::UpdateControls() {
	wxString x = point.isXExpressionValid() ? Converter::DoubleToFormattedString(point.GetX(), 2) : "Invalid expression";
	wxString y = point.isYExpressionValid() ? Converter::DoubleToFormattedString(point.GetY(), 2) : "Invalid expression";
	wxString z = point.isZExpressionValid() ? Converter::DoubleToFormattedString(point.GetZ(), 2) : "Invalid expression";

	txtX->SetValue(x);
	txtY->SetValue(y);
	txtZ->SetValue(z);
}

bool Point3DMEFrame::TransferDataFromWindow() {
	/* A variável point já está atualizada, pois isso é feito usando através da perda de foco */
	return true;
}

Point3DME Point3DMEFrame::GetPoint3DME() {
	return point;
}

void Point3DMEFrame::SetPoint3DME(Point3DME p) {
	point.Copy(&p);
	UpdateControls();
}

Point3DMEFrame::~Point3DMEFrame() {
}


