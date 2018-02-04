/*
 * ExcitationMEFrame.cpp
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#include "ExcitationMEFrame.h"

#include "emstudio/util/controls/UtilControls.h"

ExcitationMEFrame::ExcitationMEFrame(wxWindow* parent, ExcitationME e, wxWindowID id, const wxString& title)
		: wxDialog(parent, id, title), excitation(e), textCtrls() {
	CreateEmptyControlsAndInsert();
	UpdateControlsState();
}

ExcitationMEFrame::~ExcitationMEFrame() {

}

void ExcitationMEFrame::CreateEmptyControlsAndInsert() {
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(1, 2, 0, 0);
	topGridSizer->AddGrowableCol(1);
	wxStaticText* textType = new wxStaticText(this, wxID_STATIC, wxT("Type: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	type = new wxComboBox(this, wxID_ANY, excitation.GetType(), wxDefaultPosition, wxDefaultSize, excitation.GetTypes(), wxCB_READONLY);
	Connect(type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ExcitationMEFrame::SelectExcitationMEType));
	topGridSizer->Add(textType, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(type, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	wxFlexGridSizer* bottomGridSizer = new wxFlexGridSizer(6, 2, 0, 0);
	// Suporta no máximo 6 parâmetros;
	for (int i = 0; i < 6; i++) {
		wxStaticText* label = new wxStaticText(this, wxID_STATIC, "", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
		wxTextCtrl* control = UtilControls::NewTextCtrlForMathExpression(this);

		control->Bind(wxEVT_SET_FOCUS, &ExcitationMEFrame::OnSetFocusEvent, this);
		control->Bind(wxEVT_KILL_FOCUS, &ExcitationMEFrame::OnLostFocusEvent, this);

		textCtrls.push_back(std::pair<wxStaticText*, wxTextCtrl*>(label, control));
		parsers.push_back(std::pair<wxTextCtrl*, MathParser>(control, MathParser()));

		bottomGridSizer->Add(label, 0, wxALL | wxALIGN_LEFT, 5);
		bottomGridSizer->Add(control, 0, wxALL | wxEXPAND, 5);
	}
	bottomGridSizer->AddGrowableCol(1, 3);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	topSizer->Add(topGridSizer,0,wxEXPAND);
	topSizer->Add(bottomGridSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	SetSizerAndFit(topSizer);

	UpdateControlsState();
}
void ExcitationMEFrame::UpdateControlsState() {
	type->SetValue(excitation.GetType());

	int n = excitation.GetNumberOfParameters();

	for (int i = 0; i < n; i++) {
		wxString paramName = excitation.GetParameter(i).first;
		wxString paramValue = excitation.GetParameter(i).second;

		textCtrls[i].first->SetLabel(paramName.append(":"));
		parsers[i].second.SetExpression(paramValue);
		wxString evaluatedParamValue;
		if (excitation.GetType() == "Generic") {
			parsers[i].second.DefineVariables();
			evaluatedParamValue = parsers[i].second.DefineConstantsAndCheckIfIsValid() ? parsers[i].second.GetExpression() : "Invalid expression";
		} else {
			evaluatedParamValue = parsers[i].second.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(parsers[i].second.Eval(), 2) : "Invalid expression";
		}
		textCtrls[i].second->SetValue(evaluatedParamValue);
		textCtrls[i].second->SetMinSize(wxSize(350, textCtrls[i].second->GetMinSize().y));

		textCtrls[i].first->Show(true);
		textCtrls[i].second->Show(true);
	}
	for (int i = n; i < 6; i++) {
		textCtrls[i].first->Show(false);
		textCtrls[i].second->Show(false);
	}
	GetSizer()->Fit(this);
}
void ExcitationMEFrame::OnSetFocusEvent(wxFocusEvent& event) {
	cout << "--------" << endl << "SetFocus" << endl;
	wxTextCtrl* control = static_cast<wxTextCtrl*>(FindWindowById(event.GetId(), this));
	MathParser& p = GetParser(control);

	control->SetValue(p.GetExpression());
	control->SelectAll();

	event.Skip();
}
void ExcitationMEFrame::OnLostFocusEvent(wxFocusEvent& event) {
	cout << "--------" << endl << "LostFocus" << endl;
	wxTextCtrl* control = static_cast<wxTextCtrl*>(FindWindowById(event.GetId(), this));
	MathParser& p = GetParser(control);

	if (type->GetValue() != "Generic") {
		p.SetExpression(control->GetValue());
		wxString value = p.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(p.Eval(), 2) : "Invalid expression";
		control->SetValue(value);
	} else {
		p.SetExpression(control->GetValue());
		p.DefineVariables();
		wxString value = p.DefineConstantsAndCheckIfIsValid() ? control->GetValue() : "Invalid expression";
		control->SetValue(value);
	}


	event.Skip();
}
MathParser& ExcitationMEFrame::GetParser(wxTextCtrl* txt) {
	for (size_t i = 0; i < parsers.size(); i++) {
		if (txt == parsers[i].first) {
			return parsers[i].second;
		}
	}
	MathParser parser;
	return parser; // Obs.: Não deve chegar nesse ponto!
}

void ExcitationMEFrame::SelectExcitationMEType(wxCommandEvent& event) {
	excitation.SetType(type->GetStringSelection());
	UpdateControlsState();
}

bool ExcitationMEFrame::TransferDataFromWindow() {
	excitation.SetType(type->GetStringSelection());

	int n = excitation.GetNumberOfParameters();

	for (int i = 0; i < n; i++) {
		wxString parameter = parsers[i].second.GetExpression();
		excitation.SetParameter(i, parameter);
	}

	return true;
}

ExcitationME ExcitationMEFrame::GetExcitationME() {
	return excitation;
}

void ExcitationMEFrame::SetExcitationME(ExcitationME e) {
//	ExcitationME.SetValue(e);
	excitation = e;
	UpdateControlsState();
}
