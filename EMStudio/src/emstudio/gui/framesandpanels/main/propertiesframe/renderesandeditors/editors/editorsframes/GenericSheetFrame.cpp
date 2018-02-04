/*
 * GenericSheetFrame.cpp
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetFrame.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"
#include "emstudio/util/dialogs/UtilDialog.h"
#include <iostream>
using namespace::std;

GenericSheetFrame::GenericSheetFrame(wxWindow* parent, GenericSheet s, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), sheet(s) {

	CreateControlsAndInsert();
	UpdateControlsWithSheetInformation();
//	Fit();
}

GenericSheetFrame::~GenericSheetFrame() {
}

void GenericSheetFrame::CreateControlsAndInsert() {
	/*********************************************/
	/* PAINÉL PRO USUÁRIO ESCOLHER O PLANO       */
	/*********************************************/
	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(3, 2, 0, 0);
	topGridSizer->AddGrowableCol(1);

	wxStaticText* lblSelectedPlane = new wxStaticText(this, wxID_STATIC, wxT("Cut at plane:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	plane = new wxComboBox(this, wxID_ANY, GetSelectedCut(), wxDefaultPosition, wxDefaultSize, GetAvailableCuts(), wxCB_READONLY);
	Connect(plane->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(GenericSheetFrame::UserChangedSelectedPlane));
	topGridSizer->Add(lblSelectedPlane, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(plane, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	lblCutAt = new wxStaticText(this, wxID_STATIC, GetSelectedCut() + ":", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cutAt = UtilControls::NewTextCtrlWithDoubleValidator(this);
	topGridSizer->Add(lblCutAt, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(cutAt, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	lblPoint = new wxStaticText(this, wxID_STATIC, wxT("Point:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	point1 = UtilControls::NewTextCtrlWithDoubleValidator(this);
	wxStaticText* lblComma = new wxStaticText(this, wxID_STATIC, wxT(", "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	point2 = UtilControls::NewTextCtrlWithDoubleValidator(this);
	addPoint = new wxButton(this, wxID_ANY, "Add");
	Connect(addPoint->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetFrame::AddPoint));
	changePoint = new wxButton(this, wxID_ANY, "Change");
	Connect(changePoint->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetFrame::ChangePoint));
	wxFlexGridSizer* addPointGridSizer = new wxFlexGridSizer(1, 5, 0, 0);
	addPointGridSizer->AddGrowableCol(0);
	addPointGridSizer->AddGrowableCol(2);
	addPointGridSizer->Add(point1, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	addPointGridSizer->Add(lblComma, 0, wxALL | wxALIGN_LEFT, 5);
	addPointGridSizer->Add(point2, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	addPointGridSizer->Add(addPoint, 0, wxALL | wxALIGN_LEFT, 5);
	addPointGridSizer->Add(changePoint, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(lblPoint, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	topGridSizer->Add(addPointGridSizer, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	/**********************************************************************************/
	/* PAINÉL COM A CAIXA DE LISTAGEM E OS BOTÕES DE MANIPULAÇÃO DA CAIXA DE LISTAGEM */
	/**********************************************************************************/
	wxFlexGridSizer* coordinatesSizer = new wxFlexGridSizer(1, 2, 0, 0);
	coordinatesSizer->AddGrowableCol(0);
	wxStaticText* lblPointList = new wxStaticText(this, wxID_STATIC, wxT("Point list:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* lblSketch = new wxStaticText(this, wxID_STATIC, wxT("Sketch:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	pointList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, GetSheetCoordinates(), wxLB_SINGLE);
	up = new wxButton(this, wxID_ANY, "Up");
	down = new wxButton(this, wxID_ANY, "Down");
	del = new wxButton(this, wxID_ANY, "Del");
	delAll = new wxButton(this, wxID_ANY, "Del All");
	Connect(up->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetFrame::MoveCoordinateUp));
	Connect(down->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetFrame::MoveCoordinateDown));
	Connect(del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetFrame::DeleteCoordinate));
	Connect(delAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetFrame::DeleteAllCoordinates));
//	drawPolygon = new wxPanel(this);
	plotSketch = new mpWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);

	wxBoxSizer* moveCoordinatesSizer = new wxBoxSizer(wxVERTICAL);
	moveCoordinatesSizer->Add(up, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(down, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(del, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(delAll, 0, wxALL | wxALIGN_CENTER, 5);

	coordinatesSizer->Add(pointList, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	coordinatesSizer->Add(moveCoordinatesSizer, 0, wxALL | wxALIGN_LEFT, 5);

	wxFlexGridSizer* coordinatesAndDrawingPanelGridSizer = new wxFlexGridSizer(2, 2, 0, 0);
	coordinatesAndDrawingPanelGridSizer->AddGrowableCol(0);
	coordinatesAndDrawingPanelGridSizer->AddGrowableCol(1);
	coordinatesAndDrawingPanelGridSizer->Add(lblPointList, 0, wxALL | wxALIGN_LEFT, 5);
	coordinatesAndDrawingPanelGridSizer->Add(lblSketch, 0, wxALL | wxALIGN_LEFT, 5);
	coordinatesAndDrawingPanelGridSizer->Add(coordinatesSizer, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	coordinatesAndDrawingPanelGridSizer->Add(plotSketch, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	/*********************************************/
	/* PAINÉL COM BOTÕES OK E CANCELAR           */
	/*********************************************/
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER | wxEXPAND, 5);

	/****************************************/
	/* PAINÉL COM OS PAINÉIS ACIMA          */
	/****************************************/
//	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* topSizer = new wxFlexGridSizer(3, 1, 0, 0);
	topSizer->AddGrowableRow(1);
	topSizer->AddGrowableRow(2);
	topSizer->Add(topGridSizer,0,wxEXPAND);
	topSizer->Add(coordinatesAndDrawingPanelGridSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	/* Preenche os controles */
	UpdateControlsWithSheetInformation();

	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void GenericSheetFrame::UpdateControlsWithSheetInformation() {
	cout << "UpdateControlsWithSheetInformation" << endl;
	plane->SetValue(GetSelectedCut());
	cutAt->SetValue(Converter::DoubleToFormattedString_MaxPrecision(sheet.GetCutAt()));
	RebuildCoordinateList();

	ChangeLabels();
}
void GenericSheetFrame::RebuildCoordinateList() {
	pointList->Clear();
	wxArrayString coordinatesList = GetSheetCoordinates();
	if (coordinatesList.size() != 0) {
		pointList->Insert(coordinatesList, 0);
	}
	DrawPolygon();
}
void GenericSheetFrame::DrawPolygon() {
	cout << "DrawPolygon" << endl;
	vector<pair<double, double> > coord = sheet.GetCoordinates();
	plotSketch->DelAllLayers(true);

	if (coord.size() == 0)
		return;

	vector<double> vectorx, vectory;
	for (size_t i = 0; i < coord.size(); i++) {
		vectorx.push_back(coord[i].first);
		vectory.push_back(coord[i].second);
	}

	mpPolygon* dataLayer = new mpPolygon();
	dataLayer->ShowName(false);
	dataLayer->setPoints(vectorx, vectory);
	dataLayer->SetContinuity(true);

	wxPen vectorpen(wxColour(0,0,255), 1, wxSOLID);
	dataLayer->SetPen(vectorpen);
	dataLayer->SetDrawOutsideMargins(false);
	plotSketch->AddLayer(dataLayer);

	plotSketch->EnableDoubleBuffer(true);
	plotSketch->SetMPScrollbars(false);
	plotSketch->SetMargins(10, 10, 10, 10);
	plotSketch->Fit();
}

wxArrayString GenericSheetFrame::GetSheetCoordinates() {
	wxArrayString array;
	vector<pair<double, double> > coord = sheet.GetCoordinates();
	for (size_t i = 0; i < coord.size(); i++) {
		pair<double, double> point = coord[i];
		wxString str = "(";
		str.Append(Converter::DoubleToFormattedString(point.first, 2)).Append(" , ").
				Append(Converter::DoubleToFormattedString(point.second, 2)).Append(")");
		array.Add(str);
	}
	return array;
}
void GenericSheetFrame::DeleteAllCoordinates(wxCommandEvent& event) {
	sheet.SetCoordinates(vector<pair<double, double> >());
	RebuildCoordinateList();
}
void GenericSheetFrame::DeleteCoordinate(wxCommandEvent& event) {
	int index = pointList->GetSelection();

	if (index == wxNOT_FOUND) {
		UtilDialog::ShowErrorMessage("Select a point to delete", "Error");
		return;
	}
	vector<pair<double, double> > coord = sheet.GetCoordinates();
	vector<pair<double, double> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		if (i != index) {
			newCoordinates.push_back(coord[i]);
		}
	}
	sheet.SetCoordinates(newCoordinates);
	RebuildCoordinateList();
}
void GenericSheetFrame::MoveCoordinateUp(wxCommandEvent& event) {
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND && index != 0) {
		vector<pair<double, double> > coord = sheet.GetCoordinates();
		pair<double, double> posIndex = coord[index];
		pair<double, double> posIndexMinusOne = coord[index-1];
		coord[index] = posIndexMinusOne;
		coord[index-1] = posIndex;

		sheet.SetCoordinates(coord);
		RebuildCoordinateList();
	}
}
void GenericSheetFrame::MoveCoordinateDown(wxCommandEvent& event) {
	vector<pair<double, double> > coord = sheet.GetCoordinates();
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND && index != coord.size()-1) {
		pair<double, double> posIndex = coord[index];
		pair<double, double> posIndexPlusOne = coord[index+1];
		coord[index] = posIndexPlusOne;
		coord[index+1] = posIndex;

		sheet.SetCoordinates(coord);
		RebuildCoordinateList();
	}
}
void GenericSheetFrame::AddPoint(wxCommandEvent& event) {
	vector<pair<double, double> > coord = sheet.GetCoordinates();
	double c1 = Converter::FormattedStringToDouble(point1->GetValue());
	double c2 = Converter::FormattedStringToDouble(point2->GetValue());
	coord.push_back(pair<double, double>(c1, c2));

	sheet.SetCoordinates(coord);
	RebuildCoordinateList();
}
void GenericSheetFrame::ChangePoint(wxCommandEvent& event) {
	int index = pointList->GetSelection();

	if (index == wxNOT_FOUND) {
		UtilDialog::ShowErrorMessage("Select a point to change", "Error");
		return;
	}

	std::vector<std::pair<double, double> > coord = sheet.GetCoordinates();
	std::vector<std::pair<double, double> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		if (i != index) {
			newCoordinates.push_back(coord[i]);
		} else {
			double c1 = Converter::FormattedStringToDouble(point1->GetValue());
			double c2 = Converter::FormattedStringToDouble(point2->GetValue());
			newCoordinates.push_back(pair<double, double>(c1, c2));
		}
	}
	sheet.SetCoordinates(newCoordinates);
	RebuildCoordinateList();
}

void GenericSheetFrame::ChangeLabels() {
	if (plane->GetValue() == "X") {
		lblCutAt->SetLabel("x:");
		lblPoint->SetLabel("(y, z) = ");
	} else if (plane->GetValue() == "Y") {
		lblCutAt->SetLabel("y:");
		lblPoint->SetLabel("(x, z) = ");
	} else if (plane->GetValue() == "Z") {
		lblCutAt->SetLabel("z:");
		lblPoint->SetLabel("(x, y) = ");
	}
}
bool GenericSheetFrame::TransferDataFromWindow() {
	/*
	 * Precisa setar apenas o plano e o corte. As coordenadas já são gerenciadas usando
	 * o próprio plano.
	 */
	double d_cutAt = Converter::FormattedStringToDouble(cutAt->GetValue());

	if (plane->GetValue() == "X") {
		sheet.SetCutAtX(d_cutAt);
	} else if (plane->GetValue() == "Y") {
		sheet.SetCutAtY(d_cutAt);
	} else if (plane->GetValue() == "Z") {
		sheet.SetCutAtZ(d_cutAt);
	}
	return true;
}

void GenericSheetFrame::UserChangedSelectedPlane(wxCommandEvent& e) {
	ChangeLabels();
}
GenericSheet GenericSheetFrame::GetGenericSheet() {
	return sheet;
}

void GenericSheetFrame::SetGenericSheet(GenericSheet s) {
	sheet.Copy(&s);
	UpdateControlsWithSheetInformation();
}
wxArrayString GenericSheetFrame::GetAvailableCuts() {
	wxArrayString array;

	array.Add(wxT("X"));
	array.Add(wxT("Y"));
	array.Add(wxT("Z"));

	return array;
}
wxString GenericSheetFrame::GetSelectedCut() {
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
