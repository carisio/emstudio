/*
 * NewMaterialFrame.cpp
 *
 *  Created on: 23/09/2011
 *      Author: leandrocarisio
 */

#include "NewMaterialFrame.h"
#include "emstudio/util/controls/UtilControls.h"
#include "wx/colordlg.h"
#include "wx/utils.h"

NewMaterialFrame::NewMaterialFrame(wxWindow* parent, Material m, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), material(m) {
	CreateAndInsertControls();
}

NewMaterialFrame::~NewMaterialFrame() {
}

void NewMaterialFrame::CreateAndInsertControls() {
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(2, 2, 0, 0);
	topGridSizer->AddGrowableCol(1);

	wxStaticText* textDescription = new wxStaticText(this, wxID_STATIC, wxT("Description:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	description = new wxTextCtrl(this, wxID_ANY, material.GetDescription());
	topGridSizer->Add(textDescription, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(description, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	wxStaticText* textType = new wxStaticText(this, wxID_STATIC, wxT("Type:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	type = new wxComboBox(this, wxID_ANY, GetType(), wxDefaultPosition, wxDefaultSize, GetAvailableTypes(), wxCB_READONLY);
	Connect(type->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(NewMaterialFrame::SelectMaterialType));
	topGridSizer->Add(textType, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(type, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	/* Original
	wxFlexGridSizer* bottomGridSizer = new wxFlexGridSizer(4, 6, 0, 0);
	textex = new wxStaticText(this, wxID_STATIC, wxT("\u03F5x"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textey = new wxStaticText(this, wxID_STATIC, wxT("\u03F5y"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textez = new wxStaticText(this, wxID_STATIC, wxT("\u03F5z"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textux = new wxStaticText(this, wxID_STATIC, wxT("\u03BCx"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textuy = new wxStaticText(this, wxID_STATIC, wxT("\u03BCy"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textuz = new wxStaticText(this, wxID_STATIC, wxT("\u03BCz"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textsx = new wxStaticText(this, wxID_STATIC, wxT("\u03C3x"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textsy = new wxStaticText(this, wxID_STATIC, wxT("\u03C3y"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textsz = new wxStaticText(this, wxID_STATIC, wxT("\u03C3z"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textrho = new wxStaticText(this, wxID_STATIC, wxT("\u03C1"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	*/

	/* Alteração para consertar erro E001 */
	wxStaticBox *electricPermittivityBox = new wxStaticBox(this, wxID_ANY, "Electric permittivity:");
	wxStaticBoxSizer *electricPermittivityBoxSizer = new wxStaticBoxSizer(electricPermittivityBox, wxVERTICAL);
	textex = new wxStaticText(electricPermittivityBox, wxID_STATIC, wxT("x: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textey = new wxStaticText(electricPermittivityBox, wxID_STATIC, wxT("y: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textez = new wxStaticText(electricPermittivityBox, wxID_STATIC, wxT("z: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticBox *magneticPermeabilityBox = new wxStaticBox(this, wxID_ANY, "Magnetic permeability:");
	wxStaticBoxSizer *magneticPermeabilityBoxSizer = new wxStaticBoxSizer(magneticPermeabilityBox, wxVERTICAL);
	textux = new wxStaticText(magneticPermeabilityBox, wxID_STATIC, wxT("x: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textuy = new wxStaticText(magneticPermeabilityBox, wxID_STATIC, wxT("y: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textuz = new wxStaticText(magneticPermeabilityBox, wxID_STATIC, wxT("z: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticBox *electricConductivityBox = new wxStaticBox(this, wxID_ANY, "Electric conductivity:");
	wxStaticBoxSizer *electricConductivityBoxSizer = new wxStaticBoxSizer(electricConductivityBox, wxVERTICAL);
	textsx = new wxStaticText(electricConductivityBox, wxID_STATIC, wxT("x: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textsy = new wxStaticText(electricConductivityBox, wxID_STATIC, wxT("y: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	textsz = new wxStaticText(electricConductivityBox, wxID_STATIC, wxT("z: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticBox *densityBox = new wxStaticBox(this, wxID_ANY, "Density:");
	wxStaticBoxSizer *densityBoxSizer = new wxStaticBoxSizer(densityBox, wxVERTICAL);
	textrho = new wxStaticText(densityBox, wxID_STATIC, wxT("\u03C1: "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

	ex = UtilControls::NewTextCtrlWithDoubleValidator(electricPermittivityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetEx()));
	ey = UtilControls::NewTextCtrlWithDoubleValidator(electricPermittivityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetEy()));
	ez = UtilControls::NewTextCtrlWithDoubleValidator(electricPermittivityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetEz()));
	ux = UtilControls::NewTextCtrlWithDoubleValidator(magneticPermeabilityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetUx()));
	uy = UtilControls::NewTextCtrlWithDoubleValidator(magneticPermeabilityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetUy()));
	uz = UtilControls::NewTextCtrlWithDoubleValidator(magneticPermeabilityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetUz()));
	sx = UtilControls::NewTextCtrlWithDoubleValidator(electricConductivityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetSx()));
	sy = UtilControls::NewTextCtrlWithDoubleValidator(electricConductivityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetSy()));
	sz = UtilControls::NewTextCtrlWithDoubleValidator(electricConductivityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetSz()));
	rho = UtilControls::NewTextCtrlWithDoubleValidator(densityBox, wxID_ANY, Converter::DoubleToFormattedString_MaxPrecision(material.GetRho()));

	/* Original
	bottomGridSizer->Add(textex, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(ex, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textey, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(ey, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textez, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(ez, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textux, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(ux, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textuy, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(uy, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textuz, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(uz, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textsx, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(sx, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textsy, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(sy, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textsz, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(sz, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->Add(textrho, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer->Add(rho, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer->AddGrowableCol(1);
	bottomGridSizer->AddGrowableCol(3);
	bottomGridSizer->AddGrowableCol(5);
	*/
	ChangeState();

	/* Alteração para consertar erro x, y, z */
	wxBoxSizer* bottomGridSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* bottomGridSizer1 = new wxFlexGridSizer(1, 6, 0, 0);
	wxFlexGridSizer* bottomGridSizer2 = new wxFlexGridSizer(1, 6, 0, 0);
	wxFlexGridSizer* bottomGridSizer3 = new wxFlexGridSizer(1, 6, 0, 0);
	wxFlexGridSizer* bottomGridSizer4 = new wxFlexGridSizer(1, 6, 0, 0);
	// Permissividade elétrica
	bottomGridSizer1->Add(textex, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer1->Add(ex, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer1->Add(textey, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer1->Add(ey, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer1->Add(textez, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer1->Add(ez, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer1->AddGrowableCol(1);
	bottomGridSizer1->AddGrowableCol(3);
	bottomGridSizer1->AddGrowableCol(5);
	electricPermittivityBoxSizer->Add(bottomGridSizer1);
	bottomGridSizer->Add(electricPermittivityBoxSizer, 0, wxALL | wxEXPAND, 5);
	// Permeabilidade magnética
	bottomGridSizer2->Add(textux, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer2->Add(ux, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer2->Add(textuy, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer2->Add(uy, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer2->Add(textuz, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer2->Add(uz, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer2->AddGrowableCol(1);
	bottomGridSizer2->AddGrowableCol(3);
	bottomGridSizer2->AddGrowableCol(5);
	magneticPermeabilityBoxSizer->Add(bottomGridSizer2);
	bottomGridSizer->Add(magneticPermeabilityBoxSizer, 0, wxALL | wxEXPAND, 5);
	// Condutividade elétrica
	bottomGridSizer3->Add(textsx, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer3->Add(sx, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer3->Add(textsy, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer3->Add(sy, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer3->Add(textsz, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer3->Add(sz, 0, wxALL | wxEXPAND, 5);
	bottomGridSizer3->AddGrowableCol(1);
	bottomGridSizer3->AddGrowableCol(3);
	bottomGridSizer3->AddGrowableCol(5);
	electricConductivityBoxSizer->Add(bottomGridSizer3);
	bottomGridSizer->Add(electricConductivityBoxSizer, 0, wxALL | wxEXPAND, 5);
	// Densidade
	bottomGridSizer4->Add(textrho, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer4->Add(rho, 0, wxALL | wxALIGN_LEFT, 5);
	bottomGridSizer4->AddGrowableCol(1);
	bottomGridSizer4->AddGrowableCol(3);
	bottomGridSizer4->AddGrowableCol(5);
	densityBoxSizer->Add(bottomGridSizer4);
	bottomGridSizer->Add(densityBoxSizer, 0, wxALL | wxEXPAND, 5);



	wxFlexGridSizer* colorGridSizer = new wxFlexGridSizer(1, 2, 0, 0);
	colorGridSizer->AddGrowableCol(1);
	wxStaticText* textColor = new wxStaticText(this, wxID_STATIC, wxT("Color:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	colorGridSizer->Add(textColor, 0, wxALL | wxALIGN_LEFT, 5);
	color = new wxButton(this, wxID_ANY, " ");
	color->SetBackgroundColour(material.GetColor());
	Connect(color->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewMaterialFrame::ChangeColor));
	colorGridSizer->Add(color, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "Add to library"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	topSizer->Add(topGridSizer,0,wxEXPAND);
	topSizer->Add(bottomGridSizer,0,wxALIGN_CENTER);
	topSizer->Add(colorGridSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void NewMaterialFrame::ChangeColor(wxCommandEvent& event) {
	wxColourData data;
	data.SetChooseFull(true);
	wxColourDialog dialog(color, &data);
	if (dialog.ShowModal() == wxID_OK) {
		wxColourData retData = dialog.GetColourData();
		wxColour col = retData.GetColour();

		material.SetColor(col);
	}

	color->SetBackgroundColour(material.GetColor());
}
wxString NewMaterialFrame::GetType() {
	if (material.GetType() == PEC)
		return "PEC";
	else if (material.GetType() == ISOTROPIC)
		return "Isotropic";
	else
		return "Anisotropic";
}
wxArrayString NewMaterialFrame::GetAvailableTypes() {
	wxArrayString array;

	array.Add(wxT("PEC"));
	array.Add(wxT("Isotropic"));
	// TODO: Deixar desabilitado, pois ainda não foi implementado o código que funciona com materiais desse tipo (VER A009)
//	array.Add(wxT("Anisotropic"));

	return array;
}

void NewMaterialFrame::ChangeState() {
	wxString materialType = type->GetStringSelection();

	bool PEC = false;
	bool anisotropic = false;
	if ("PEC" == materialType) {
		PEC = true;
	} else if ("Anisotropic" == materialType) {
		anisotropic = true;
	}

	bool showx  = !PEC;
	bool showyz = anisotropic;

	ex->Enable(showx); ux->Enable(showx); sx->Enable(showx);
	ey->Enable(showyz); uy->Enable(showyz); sy->Enable(showyz);
	ez->Enable(showyz); uz->Enable(showyz); sz->Enable(showyz);
	rho->Enable(showx);

	// TODO: O código ainda não está preparado para trabalhar com materiais magnéticos. Desabilitar até que esteja funcionando. Quando estiver, descomentar as linhas abaixo:
	ux->Enable(false);
	uy->Enable(false);
	uz->Enable(false);
}

void NewMaterialFrame::SelectMaterialType(wxCommandEvent& event) {
	ChangeState();
}

bool NewMaterialFrame::TransferDataFromWindow() {
	material = Material();
	material.SetDescription(description->GetValue());
	material.SetRho(Converter::FormattedStringToDouble(rho->GetValue()));

	material.SetEx(Converter::FormattedStringToDouble(ex->GetValue()));
	material.SetUx(Converter::FormattedStringToDouble(ux->GetValue()));
	material.SetSx(Converter::FormattedStringToDouble(sx->GetValue()));
	if (type->GetStringSelection() == "Anisotropic") {
		material.SetEy(Converter::FormattedStringToDouble(ey->GetValue()));
		material.SetEz(Converter::FormattedStringToDouble(ez->GetValue()));

		material.SetUy(Converter::FormattedStringToDouble(uy->GetValue()));
		material.SetUz(Converter::FormattedStringToDouble(uz->GetValue()));

		material.SetSy(Converter::FormattedStringToDouble(sy->GetValue()));
		material.SetSz(Converter::FormattedStringToDouble(sz->GetValue()));

		material.SetType(ANISOTROPIC);
	} else if (type->GetStringSelection() == "Isotropic") {
		material.SetEy(Converter::FormattedStringToDouble(ex->GetValue()));
		material.SetEz(Converter::FormattedStringToDouble(ex->GetValue()));

		material.SetUy(Converter::FormattedStringToDouble(ux->GetValue()));
		material.SetUz(Converter::FormattedStringToDouble(ux->GetValue()));

		material.SetSy(Converter::FormattedStringToDouble(sx->GetValue()));
		material.SetSz(Converter::FormattedStringToDouble(sx->GetValue()));

		material.SetType(ISOTROPIC);
	} else if(type->GetStringSelection() == "PEC") {
		material.SetRho(1);
		material.SetType(PEC);
	}
	material.SetColor(color->GetBackgroundColour());
	return true;
}

Material NewMaterialFrame::GetMaterial() {
	return material;
}
