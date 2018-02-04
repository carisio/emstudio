/*
 * ABCFrame.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "ABCFrame.h"
#include "wx/valnum.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"

#include <iostream>
using std::cout;
using std::endl;

ABCFrame::ABCFrame(wxWindow* parent, AbsorvingBoundaryCondition a, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), abc(a) {

	chkNegX = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, abc.GetAvailableABCsXDirection(), wxCB_READONLY);
	chkNegY = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition ,wxDefaultSize, abc.GetAvailableABCsYDirection(), wxCB_READONLY);
	chkNegZ = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, abc.GetAvailableABCsZDirection(), wxCB_READONLY);
	chkPosX = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, abc.GetAvailableABCsXDirection(), wxCB_READONLY);
	chkPosY = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, abc.GetAvailableABCsYDirection(), wxCB_READONLY);
	chkPosZ = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, abc.GetAvailableABCsZDirection(), wxCB_READONLY);
	Connect(chkNegX->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ABCFrame::SelectABCType));
	Connect(chkNegY->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ABCFrame::SelectABCType));
	Connect(chkNegZ->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ABCFrame::SelectABCType));
	Connect(chkPosX->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ABCFrame::SelectABCType));
	Connect(chkPosY->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ABCFrame::SelectABCType));
	Connect(chkPosZ->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ABCFrame::SelectABCType));
	txtNpml = UtilControls::NewTextCtrlWithIntIntervalValidator(this, 0, 16);
	CreateEmptyControlsAndInsert();
	UpdateControlsState();
}

ABCFrame::~ABCFrame() {

}

bool ABCFrame::TransferDataFromWindow() {
	abc.SetABCXNeg(chkNegX->GetStringSelection());
	abc.SetABCYNeg(chkNegY->GetStringSelection());
	abc.SetABCZNeg(chkNegZ->GetStringSelection());
	abc.SetABCXPos(chkPosX->GetStringSelection());
	abc.SetABCYPos(chkPosY->GetStringSelection());
	abc.SetABCZPos(chkPosZ->GetStringSelection());
	abc.SetNpml(Converter::FormattedStringToInt(txtNpml->GetValue()));
	return true;
}

AbsorvingBoundaryCondition ABCFrame::GetABC() {
	return abc;
}

void ABCFrame::SetABC(AbsorvingBoundaryCondition a) {
	abc.Copy(&a);
	UpdateControlsState();
}

void ABCFrame::CreateEmptyControlsAndInsert() {
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(3, 4, 0, 0);
	topGridSizer->AddGrowableCol(1);
	topGridSizer->AddGrowableCol(3);
	wxStaticText* lblNegX = new wxStaticText(this, wxID_STATIC, wxT("-X: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* lblNegY = new wxStaticText(this, wxID_STATIC, wxT("-Y: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* lblNegZ = new wxStaticText(this, wxID_STATIC, wxT("-Z: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* lblPosX = new wxStaticText(this, wxID_STATIC, wxT("+X: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* lblPosY = new wxStaticText(this, wxID_STATIC, wxT("+Y: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* lblPosZ = new wxStaticText(this, wxID_STATIC, wxT("+Z: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

	topGridSizer->Add(lblNegX, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(chkNegX, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(lblPosX, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(chkPosX, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(lblNegY, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(chkNegY, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(lblPosY, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(chkPosY, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(lblNegZ, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(chkNegZ, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	topGridSizer->Add(lblPosZ, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(chkPosZ, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	wxFlexGridSizer* npmlSizer = new wxFlexGridSizer(1, 2, 0, 0);
	npmlSizer->AddGrowableCol(1);
	wxStaticText* lblNpml = new wxStaticText(this, wxID_STATIC, wxT("Npml: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	npmlSizer->Add(lblNpml, 0, wxALL | wxALIGN_LEFT, 5);
	npmlSizer->Add(txtNpml, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	UpdateControlsState();

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	topSizer->Add(topGridSizer,0,wxEXPAND);
	topSizer->Add(npmlSizer, 0, wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}

void ABCFrame::ApplyRulesForComboBox(wxComboBox* changedComboBox, wxComboBox* theOtherComboBox, wxString& captionOfChangedComboBox) {
	// Verifica se o usuário selecionou o periódico. Caso tenha selecionado, seleciona também o do lado positivo
	if (changedComboBox->GetStringSelection() == "Periodic") {
		theOtherComboBox->SetValue("Periodic");
	}

	// Verifica se o usuário deselecionou o periódico. Caso tenha selecionado, desseleciona também o do lado positivo
	if ((changedComboBox->GetStringSelection() != "Periodic") && captionOfChangedComboBox == "Periodic") {
		theOtherComboBox->SetValue(changedComboBox->GetStringSelection());
	}
}
void ABCFrame::SelectABCType(wxCommandEvent& event) {
	int controlID = event.GetId();

	/* Verifica se é o combo com dados de informação de negX */
	if (controlID == chkNegX->GetId()) {
		ApplyRulesForComboBox(chkNegX, chkPosX, negXCaption);
	}
	/* Verifica se é o combo com dados de informação de posX */
	if (controlID == chkPosX->GetId()) {
		ApplyRulesForComboBox(chkPosX, chkNegX, posXCaption);
	}
	/* Verifica se é o combo com dados de informação de negY */
	if (controlID == chkNegY->GetId()) {
		ApplyRulesForComboBox(chkNegY, chkPosY, negYCaption);
	}
	/* Verifica se é o combo com dados de informação de posY */
	if (controlID == chkPosY->GetId()) {
		ApplyRulesForComboBox(chkPosY, chkNegY, posYCaption);
	}
	/* Verifica se é o combo com dados de informação de negZ */
	if (controlID == chkNegZ->GetId()) {
		ApplyRulesForComboBox(chkNegZ, chkPosZ, negZCaption);
	}
	/* Verifica se é o combo com dados de informação de posZ */
	if (controlID == chkPosZ->GetId()) {
		ApplyRulesForComboBox(chkPosZ, chkNegZ, posZCaption);
	}
	// Atualiza os valores antigos para os novos valores corretos
	negXCaption = chkNegX->GetStringSelection();
	posXCaption = chkPosX->GetStringSelection();
	negYCaption = chkNegY->GetStringSelection();
	posYCaption = chkPosY->GetStringSelection();
	negZCaption = chkNegZ->GetStringSelection();
	posZCaption = chkPosZ->GetStringSelection();

	cout << "ABCFrame::SelectABCType()" << endl;
	cout << "negXCaption = " << negXCaption << endl;
	cout << "negYCaption = " << negYCaption << endl;
	cout << "negZCaption = " << negZCaption << endl;
	cout << "posXCaption = " << posXCaption << endl;
	cout << "posYCaption = " << posYCaption << endl;
	cout << "posZCaption = " << posZCaption << endl;
	cout << "chkNegX = " << chkNegX->GetStringSelection() << endl;
	cout << "chkNegY = " << chkNegY->GetStringSelection() << endl;
	cout << "chkNegZ = " << chkNegZ->GetStringSelection() << endl;
	cout << "chkPosX = " << chkPosX->GetStringSelection() << endl;
	cout << "chkPosY = " << chkPosY->GetStringSelection() << endl;
	cout << "chkPosZ = " << chkPosZ->GetStringSelection() << endl;
	cout << "chkNegX = " << chkNegX->GetValue() << endl;
	cout << "chkNegY = " << chkNegY->GetValue() << endl;
	cout << "chkNegZ = " << chkNegZ->GetValue() << endl;
	cout << "chkPosX = " << chkPosX->GetValue() << endl;
	cout << "chkPosY = " << chkPosY->GetValue() << endl;
	cout << "chkPosZ = " << chkPosZ->GetValue() << endl;
	cout << "--------------------" << endl;
}

void ABCFrame::UpdateControlsState() {

	chkNegX->SetValue(abc.GetABCXNeg());
	chkNegY->SetValue(abc.GetABCYNeg());
	chkNegZ->SetValue(abc.GetABCZNeg());
	chkPosX->SetValue(abc.GetABCXPos());
	chkPosY->SetValue(abc.GetABCYPos());
	chkPosZ->SetValue(abc.GetABCZPos());

	negXCaption = chkNegX->GetValue();
	negYCaption = chkNegY->GetValue();
	negZCaption = chkNegZ->GetValue();
	posXCaption = chkPosX->GetValue();
	posYCaption = chkPosY->GetValue();
	posZCaption = chkPosZ->GetValue();

	txtNpml->SetValue(Converter::IntToFormattedString(abc.GetNpml()));

	Fit();
}
