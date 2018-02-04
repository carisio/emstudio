/*
 * GroundParametersFrame.cpp
 *
 *  Created on: 18/03/2015
 *      Author: Leandro
 */

#include "wx/utils.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/GroundParametersFrame.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"
#include "emstudio/util/dialogs/UtilDialog.h"

namespace mom {

GroundParametersFrame::GroundParametersFrame(wxWindow* parent, GroundParameters g, wxWindowID id, const wxString& title)
		: wxDialog(parent, id, title), gp(g) {

	CreateControlsAndInsert();
	UpdateControlsWithGroundParametersInformation();
}

GroundParametersFrame::~GroundParametersFrame() {

}

void GroundParametersFrame::CreateControlsAndInsert() {
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBox *lblGround1 = new wxStaticBox(this, wxID_ANY, "Ground 1");
	wxStaticBoxSizer *ground1BoxSizer = new wxStaticBoxSizer(lblGround1, wxVERTICAL);
	wxFlexGridSizer *ground1GridSizer = new wxFlexGridSizer(2, 2, 0, 0);
	wxStaticText *lblGround1Medium = new wxStaticText(this, wxID_STATIC, wxT("Medium: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cboMedium1 = new wxComboBox(this, wxID_ANY, gp.GetGround1().GetDescription(), wxDefaultPosition, wxDefaultSize, gp.GetGround1().GetMaterialLibrary()->GetMaterialDescriptionList(), wxCB_READONLY);
	wxStaticText *lblCurrentsOnSegToucGround = new wxStaticText(this, wxID_STATIC, wxT("Currents on segments touching ground: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cboCurrentOnSegmentsTouchingGround = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, GetCurrentsExpansionTypes(), wxCB_READONLY);
	ground1GridSizer->Add(lblGround1Medium, 0, wxALL | wxALIGN_LEFT, 5);
	ground1GridSizer->Add(cboMedium1, 0, wxALL | wxEXPAND, 5);
	ground1GridSizer->Add(lblCurrentsOnSegToucGround, 0, wxALL | wxALIGN_LEFT, 5);
	ground1GridSizer->Add(cboCurrentOnSegmentsTouchingGround, 0, wxALL | wxEXPAND, 5);
	ground1BoxSizer->Add(ground1GridSizer);

	wxStaticBox *lblGround2 = new wxStaticBox(this, wxID_ANY, "Ground 2");
	wxStaticBoxSizer *ground2BoxSizer = new wxStaticBoxSizer(lblGround2, wxVERTICAL);
	wxFlexGridSizer *ground2GridSizer = new wxFlexGridSizer(5, 2, 0, 0);
	wxStaticText *lblInsertGround2 = new wxStaticText(this, wxID_STATIC, wxT("Insert ground 2? "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	chkGround2Exists = new wxCheckBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
	wxStaticText *lblGround2Medium = new wxStaticText(this, wxID_STATIC, wxT("Medium: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cboMedium2 = new wxComboBox(this, wxID_ANY, gp.GetGround2().GetDescription(), wxDefaultPosition, wxDefaultSize, gp.GetGround2().GetMaterialLibrary()->GetMaterialDescriptionList(), wxCB_READONLY);
	wxStaticText *lblCliff = new wxStaticText(this, wxID_STATIC, wxT("Cliff: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cboCliffType = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, GetCliffTypes(), wxCB_READONLY);
	wxStaticText *lblDistBelowGround = new wxStaticText(this, wxID_STATIC, wxT("Distance below ground: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	txtDistanceBelowGround = UtilControls::NewTextCtrlForMathExpression(this);
	wxStaticText *lblDistFromOrigin = new wxStaticText(this, wxID_STATIC, wxT("Distance from origin: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	txtDistanceFromOrigin = UtilControls::NewTextCtrlForMathExpression(this);
	ground2GridSizer->Add(lblInsertGround2, 0, wxALL | wxALIGN_LEFT, 5);
	ground2GridSizer->Add(chkGround2Exists, 0, wxALL | wxEXPAND, 5);
	ground2GridSizer->Add(lblGround2Medium, 0, wxALL | wxALIGN_LEFT, 5);
	ground2GridSizer->Add(cboMedium2, 0, wxALL | wxEXPAND, 5);
	ground2GridSizer->Add(lblCliff, 0, wxALL | wxALIGN_LEFT, 5);
	ground2GridSizer->Add(cboCliffType, 0, wxALL | wxEXPAND, 5);
	ground2GridSizer->Add(lblDistBelowGround , 0, wxALL | wxALIGN_LEFT, 5);
	ground2GridSizer->Add(txtDistanceBelowGround, 0, wxALL | wxEXPAND, 5);
	ground2GridSizer->Add(lblDistFromOrigin, 0, wxALL | wxALIGN_LEFT, 5);
	ground2GridSizer->Add(txtDistanceFromOrigin, 0, wxALL | wxEXPAND, 5);
	ground2BoxSizer->Add(ground2GridSizer);

	wxStaticBox *lblRadials = new wxStaticBox(this, wxID_ANY, "Radials");
	wxStaticBoxSizer *radialsBoxSizer = new wxStaticBoxSizer(lblRadials, wxVERTICAL);
	wxFlexGridSizer *radialsGridSizer = new wxFlexGridSizer(3, 2, 0, 0);
	wxStaticText *lblNumberOfWires = new wxStaticText(this, wxID_STATIC, wxT("Number of wires: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	txtNumberOfWires = UtilControls::NewTextCtrlForMathExpression(this);
	wxStaticText *lblWireLength = new wxStaticText(this, wxID_STATIC, wxT("Wire length: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	txtWireLength = UtilControls::NewTextCtrlForMathExpression(this);
	wxStaticText *lblWireRadius = new wxStaticText(this, wxID_STATIC, wxT("Wire radius: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	txtWireRadius = UtilControls::NewTextCtrlForMathExpression(this);
	radialsGridSizer->Add(lblNumberOfWires, 0, wxALL | wxALIGN_LEFT, 5);
	radialsGridSizer->Add(txtNumberOfWires, 0, wxALL | wxEXPAND, 5);
	radialsGridSizer->Add(lblWireLength, 0, wxALL | wxALIGN_LEFT, 5);
	radialsGridSizer->Add(txtWireLength, 0, wxALL | wxEXPAND, 5);
	radialsGridSizer->Add(lblWireRadius, 0, wxALL | wxALIGN_LEFT, 5);
	radialsGridSizer->Add(txtWireRadius, 0, wxALL | wxEXPAND, 5);
	radialsBoxSizer->Add(radialsGridSizer);


	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	topSizer->Add(ground1BoxSizer,0,wxEXPAND);
	topSizer->Add(ground2BoxSizer,0,wxEXPAND);
	topSizer->Add(radialsBoxSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);


	// Events handlers
	txtDistanceBelowGround->Bind(wxEVT_SET_FOCUS, &GroundParametersFrame::OnSetFocusEvent, this);
	txtDistanceFromOrigin->Bind(wxEVT_SET_FOCUS, &GroundParametersFrame::OnSetFocusEvent, this);
	txtNumberOfWires->Bind(wxEVT_SET_FOCUS, &GroundParametersFrame::OnSetFocusEvent, this);
	txtWireLength->Bind(wxEVT_SET_FOCUS, &GroundParametersFrame::OnSetFocusEvent, this);
	txtWireRadius->Bind(wxEVT_SET_FOCUS, &GroundParametersFrame::OnSetFocusEvent, this);
	txtDistanceBelowGround->Bind(wxEVT_KILL_FOCUS, &GroundParametersFrame::OnLostFocusEvent, this);
	txtDistanceFromOrigin->Bind(wxEVT_KILL_FOCUS, &GroundParametersFrame::OnLostFocusEvent, this);
	txtNumberOfWires->Bind(wxEVT_KILL_FOCUS, &GroundParametersFrame::OnLostFocusEvent, this);
	txtWireLength->Bind(wxEVT_KILL_FOCUS, &GroundParametersFrame::OnLostFocusEvent, this);
	txtWireRadius->Bind(wxEVT_KILL_FOCUS, &GroundParametersFrame::OnLostFocusEvent, this);
	cboMedium1->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &GroundParametersFrame::GroundCommandEvent, this);
	cboCurrentOnSegmentsTouchingGround->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &GroundParametersFrame::GroundCommandEvent, this);
	cboMedium2->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &GroundParametersFrame::GroundCommandEvent, this);
	cboCliffType->Bind(wxEVT_COMMAND_COMBOBOX_SELECTED, &GroundParametersFrame::GroundCommandEvent, this);
	chkGround2Exists->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &GroundParametersFrame::GroundCommandEvent, this);
}
void GroundParametersFrame::UpdateControlsWithGroundParametersInformation() {
	cboMedium1->SetValue(gp.GetGround1().GetDescription());
	cboCurrentOnSegmentsTouchingGround->SetValue(gp.IsCurrentsOnSegmentsTouchingGroundGoToZero() ? "go to zero" : (gp.IsCurrentsOnSegmentsTouchingGroundInterpolated() ? "are interpolated" : ""));

	chkGround2Exists->SetValue(gp.IsGround2());
	cboMedium2->SetValue(gp.GetGround2().GetDescription());
	cboCliffType->SetValue(gp.IsCircularCliff() ? "Circular" : (gp.IsLinearCliff() ? "Linear" : ""));
	wxString dbelowground = gp.IsDistanceBelowGroundExpressionValid() ? Converter::DoubleToFormattedString(gp.GetDistanceBelowGround(), 2) : "Invalid expression";
	txtDistanceBelowGround->SetValue(dbelowground);
	wxString dfromorigin = gp.IsDistanceFromOriginExpressionValid() ? Converter::DoubleToFormattedString(gp.GetDistanceFromOrigin(), 2) : "Invalid expression";
	txtDistanceFromOrigin->SetValue(dfromorigin);

	wxString numberOfWires = gp.IsNumberOfWiresExpressionValid() ? Converter::IntToFormattedString(gp.GetNumberOfWires()) : "Invalid expression";
	wxString wireLength = gp.IsWireLengthExpressionValid() ? Converter::DoubleToFormattedString(gp.GetWireLength(), 2) : "Invalid expression";
	wxString wireRadiuis = gp.IsWireRadiusExpressionValid() ? Converter::DoubleToFormattedString(gp.GetWireRadius(), 2) : "Invalid expression";
	txtNumberOfWires->SetValue(numberOfWires);
	txtWireLength->SetValue(wireLength);
	txtWireRadius->SetValue(wireRadiuis);

	bool enable = chkGround2Exists->IsChecked();
	gp.SetGround2Exists(enable);
	cboMedium2->Enable(enable);
	cboCliffType->Enable(enable);
	txtDistanceBelowGround->Enable(enable);
	txtDistanceFromOrigin->Enable(enable);
}

wxArrayString GroundParametersFrame::GetCliffTypes() {
	wxArrayString result = wxArrayString();
	result.Add("Circular");
	result.Add("Linear");
	return result;
}
wxArrayString GroundParametersFrame::GetCurrentsExpansionTypes() {
	wxArrayString result = wxArrayString();
	result.Add("are interpolated");
	result.Add("go to zero");
	return result;
}

void GroundParametersFrame::OnSetFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == txtDistanceBelowGround->GetId()) {
		txtDistanceBelowGround->SetValue(gp.GetDistanceBelowGroundExpression());
		txtDistanceBelowGround->SelectAll();
	} else if (event.GetId() == txtDistanceFromOrigin->GetId()) {
		txtDistanceFromOrigin->SetValue(gp.GetDistanceFromOriginExpression());
		txtDistanceFromOrigin->SelectAll();
	} else if (event.GetId() == txtNumberOfWires->GetId()) {
		txtNumberOfWires->SetValue(gp.GetNumberOfWiresExpression());
		txtNumberOfWires->SelectAll();
	} else if (event.GetId() == txtWireLength->GetId()) {
		txtWireLength->SetValue(gp.GetWireLengthExpression());
		txtWireLength->SelectAll();
	} else if (event.GetId() == txtWireRadius->GetId()) {
		txtWireRadius->SetValue(gp.GetWireRadiusExpression());
		txtWireRadius->SelectAll();
	}

	event.Skip();
}
void GroundParametersFrame::OnLostFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == txtDistanceBelowGround->GetId()) {
		gp.SetDistanceBelowGroundExpression(txtDistanceBelowGround->GetValue());
		wxString value = gp.IsDistanceBelowGroundExpressionValid() ? Converter::DoubleToFormattedString(gp.GetDistanceBelowGround(), 2) : "Invalid expression";
		txtDistanceBelowGround->SetValue(value);
	} else if (event.GetId() == txtDistanceFromOrigin->GetId()) {
		gp.SetDistanceFromOriginExpression(txtDistanceFromOrigin->GetValue());
		wxString value = gp.IsDistanceFromOriginExpressionValid() ? Converter::DoubleToFormattedString(gp.GetDistanceFromOrigin(), 2) : "Invalid expression";
		txtDistanceFromOrigin->SetValue(value);
	} else if (event.GetId() == txtNumberOfWires->GetId()) {
		gp.SetNumberOfWiresExpression(txtNumberOfWires->GetValue());
		wxString value = gp.IsNumberOfWiresExpressionValid() ? Converter::IntToFormattedString(gp.GetNumberOfWires()) : "Invalid expression";
		txtNumberOfWires->SetValue(value);
	} else if (event.GetId() == txtWireLength->GetId()) {
		gp.SetWireLengthExpression(txtWireLength->GetValue());
		wxString value = gp.IsWireLengthExpressionValid() ? Converter::DoubleToFormattedString(gp.GetWireLength(), 2) : "Invalid expression";
		txtWireLength->SetValue(value);
	} else if (event.GetId() == txtWireRadius->GetId()) {
		gp.SetWireRadiusExpression(txtWireRadius->GetValue());
		wxString value = gp.IsWireRadiusExpressionValid() ? Converter::DoubleToFormattedString(gp.GetWireRadius(), 2) : "Invalid expression";
		txtWireRadius->SetValue(value);
	}
	event.Skip();
}

void GroundParametersFrame::GroundCommandEvent(wxCommandEvent& event) {
	if (event.GetId() == cboMedium1->GetId()) {
		wxString materialDescription = cboMedium1->GetValue();
		Material m = Material::GetMaterialLibrary()->GetMaterial(materialDescription);
		gp.SetGround1(m);
	} else if (event.GetId() == cboCurrentOnSegmentsTouchingGround->GetId()) {
		wxString currentExpansion = cboCurrentOnSegmentsTouchingGround->GetValue();
		if (currentExpansion == "are interpolated")
			gp.SetCurrentsOnSegmentsTouchingGroundInterpolated();
		else if (currentExpansion == "go to zero")
			gp.SetCurrentsOnSegmentsTouchingGroundGoToZero();
	} else if (event.GetId() == cboMedium2->GetId()) {
		wxString materialDescription = cboMedium2->GetValue();
		Material m = Material::GetMaterialLibrary()->GetMaterial(materialDescription);
		gp.SetGround2(m);
	} else if (event.GetId() == cboCliffType->GetId()) {
		if (cboCliffType->GetValue() == "Linear") {
			gp.SetLinearCliff();
		} else if (cboCliffType->GetValue() == "Circular") {
			gp.SetCircularCliff();
		}
	} else if (event.GetId() == chkGround2Exists->GetId()) {
		bool enable = chkGround2Exists->IsChecked();
		gp.SetGround2Exists(enable);
		cboMedium2->Enable(enable);
		cboCliffType->Enable(enable);
		txtDistanceBelowGround->Enable(enable);
		txtDistanceFromOrigin->Enable(enable);
	}
}

bool GroundParametersFrame::TransferDataFromWindow() {
	/*
	 * Precisa apenar retornar true. As coordenadas já são gerenciadas usando a variável ports.
	 */
	return true;
}

GroundParameters GroundParametersFrame::GetGroundParameters() {
	return gp;
}

void GroundParametersFrame::SetGroundParameters(GroundParameters g) {
	gp.Copy(&g);
	UpdateControlsWithGroundParametersInformation();
}

} /* namespace mom */
