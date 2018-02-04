/*
 * GenericSheetMEFrame.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetMEFrame.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"
#include "emstudio/util/dialogs/UtilDialog.h"

GenericSheetMEFrame::GenericSheetMEFrame(wxWindow* parent, GenericSheetME s, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), sheet(s) {

	CreateControlsAndInsert();
	UpdateControlsWithSheetInformation();
//	Fit();
}

GenericSheetMEFrame::~GenericSheetMEFrame() {
}
void GenericSheetMEFrame::OnSetFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == cutAt->GetId()) {
		cutAt->SetValue(cutAtParser.GetExpression());
		cutAt->SelectAll();
	} else if (event.GetId() == point1->GetId()) {
		point1->SetValue(point1Parser.GetExpression());
		point1->SelectAll();
	} else if (event.GetId() == point2->GetId()) {
		point2->SetValue(point2Parser.GetExpression());
		point2->SelectAll();
	}

	event.Skip();
}
void GenericSheetMEFrame::OnLostFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == cutAt->GetId()) {
		cutAtParser.SetExpression(cutAt->GetValue());
		wxString value = cutAtParser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(cutAtParser.Eval(), 2) : "Invalid expression";
		cutAt->SetValue(value);
	} else if (event.GetId() == point1->GetId()) {
		point1Parser.SetExpression(point1->GetValue());
		wxString value = point1Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(point1Parser.Eval(), 2) : "Invalid expression";
		point1->SetValue(value);
	} else if (event.GetId() == point2->GetId()) {
		point2Parser.SetExpression(point2->GetValue());
		wxString value = point2Parser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(point2Parser.Eval(), 2) : "Invalid expression";
		point2->SetValue(value);
	}
	event.Skip();
}
void GenericSheetMEFrame::CreateControlsAndInsert() {
	/*********************************************/
	/* PAINÉL PRO USUÁRIO ESCOLHER O PLANO       */
	/*********************************************/
	wxFlexGridSizer* topGridSizer = new wxFlexGridSizer(3, 2, 0, 0);
	topGridSizer->AddGrowableCol(1);

	wxStaticText* lblSelectedPlane = new wxStaticText(this, wxID_STATIC, wxT("Cut at plane:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	plane = new wxComboBox(this, wxID_ANY, GetSelectedCut(), wxDefaultPosition, wxDefaultSize, GetAvailableCuts(), wxCB_READONLY);
	Connect(plane->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(GenericSheetMEFrame::UserChangedSelectedPlane));
	topGridSizer->Add(lblSelectedPlane, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(plane, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	lblCutAt = new wxStaticText(this, wxID_STATIC, GetSelectedCut() + ":", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	cutAt = UtilControls::NewTextCtrlForMathExpression(this);
	cutAt->Bind(wxEVT_SET_FOCUS, &GenericSheetMEFrame::OnSetFocusEvent, this);
	cutAt->Bind(wxEVT_KILL_FOCUS, &GenericSheetMEFrame::OnLostFocusEvent, this);
	topGridSizer->Add(lblCutAt, 0, wxALL | wxALIGN_LEFT, 5);
	topGridSizer->Add(cutAt, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);

	lblPoint = new wxStaticText(this, wxID_STATIC, wxT("Point:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	point1 = UtilControls::NewTextCtrlForMathExpression(this);
	point1->Bind(wxEVT_SET_FOCUS, &GenericSheetMEFrame::OnSetFocusEvent, this);
	point1->Bind(wxEVT_KILL_FOCUS, &GenericSheetMEFrame::OnLostFocusEvent, this);
	wxStaticText* lblComma = new wxStaticText(this, wxID_STATIC, wxT(", "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	point2 = UtilControls::NewTextCtrlForMathExpression(this);
	point2->Bind(wxEVT_SET_FOCUS, &GenericSheetMEFrame::OnSetFocusEvent, this);
	point2->Bind(wxEVT_KILL_FOCUS, &GenericSheetMEFrame::OnLostFocusEvent, this);
	addPoint = new wxButton(this, wxID_ANY, "Add");
	Connect(addPoint->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetMEFrame::AddPoint));
	changePoint = new wxButton(this, wxID_ANY, "Change");
	Connect(changePoint->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetMEFrame::ChangePoint));
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
	wxGridSizer* labelsSizer = new wxGridSizer(1,3,0,0);
	wxStaticText* lblPointList = new wxStaticText(this, wxID_STATIC, wxT("Point list:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* lblSketch = new wxStaticText(this, wxID_STATIC, wxT("Sketch:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	labelsSizer->Add(lblPointList, 0, wxALL | wxALIGN_LEFT | wxEXPAND , 5);
	labelsSizer->Add(new wxStaticText(this, wxID_STATIC, wxT("")));
	labelsSizer->Add(lblSketch, 0, wxALL | wxALIGN_LEFT | wxEXPAND , 5);

	pointList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, GetSheetCoordinates(), wxLB_SINGLE | wxLB_HSCROLL | wxLB_NEEDED_SB);
	Connect(pointList->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(GenericSheetMEFrame::CoordinateSelected));
	up = new wxButton(this, wxID_ANY, "Up");
	down = new wxButton(this, wxID_ANY, "Down");
	del = new wxButton(this, wxID_ANY, "Del");
	delAll = new wxButton(this, wxID_ANY, "Del All");
	Connect(up->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetMEFrame::MoveCoordinateUp));
	Connect(down->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetMEFrame::MoveCoordinateDown));
	Connect(del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetMEFrame::DeleteCoordinate));
	Connect(delAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GenericSheetMEFrame::DeleteAllCoordinates));
	plotSketch = new mpWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);

	wxBoxSizer* moveCoordinatesSizer = new wxBoxSizer(wxVERTICAL);
	moveCoordinatesSizer->Add(up, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(down, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(del, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(delAll, 0, wxALL | wxALIGN_CENTER, 5);

	wxGridSizer* coordinatesControlsAndDrawingPanelSizer = new wxGridSizer(1, 3, 0, 0);
	coordinatesControlsAndDrawingPanelSizer->Add(pointList, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	coordinatesControlsAndDrawingPanelSizer->Add(moveCoordinatesSizer, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);
	coordinatesControlsAndDrawingPanelSizer->Add(plotSketch, 0, wxALL | wxALIGN_CENTER | wxEXPAND , 5);

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
	wxFlexGridSizer* topSizer = new wxFlexGridSizer(4, 1, 0, 0);
	topSizer->AddGrowableRow(1);
	topSizer->AddGrowableRow(2);
	topSizer->Add(topGridSizer,0,wxEXPAND);
	topSizer->Add(labelsSizer,0,wxEXPAND);
	topSizer->Add(coordinatesControlsAndDrawingPanelSizer,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	/* Preenche os controles */
	UpdateControlsWithSheetInformation();

	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void GenericSheetMEFrame::UpdateControlsWithSheetInformation() {
	cout << "UpdateControlsWithSheetInformation" << endl;
	plane->SetValue(GetSelectedCut());
	wxString cutAtStr = cutAtParser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(cutAtParser.Eval(), 2) : "Invalid expression";
	cutAt->SetValue(cutAtStr);
	RebuildCoordinateList();

	ChangeLabels();
}
void GenericSheetMEFrame::CoordinateSelected(wxCommandEvent& event) {
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND) {
		point1->SetValue(sheet.GetCoordinates()[index].first);
		point1Parser.SetExpression(point1->GetValue());
		point2->SetValue(sheet.GetCoordinates()[index].second);
		point2Parser.SetExpression(point2->GetValue());
	}
}
void GenericSheetMEFrame::RebuildCoordinateList(int selectedIndex) {
	pointList->Clear();
	wxArrayString coordinatesList = GetSheetCoordinates();
	if (coordinatesList.size() != 0) {
		pointList->Insert(coordinatesList, 0);
	}
	if (selectedIndex != wxNOT_FOUND && selectedIndex < coordinatesList.size()) {
		pointList->SetSelection(selectedIndex);
	}
	DrawPolygon();
}
void GenericSheetMEFrame::DrawPolygon() {
	cout << "DrawPolygon" << endl;
	plotSketch->DelAllLayers(true);

	if (! sheet.IsGenericSheetValid()) {
		return;
	}

	GenericSheet gs = sheet.ConvertToGenericSheet(true);

	vector<pair<double, double> > coord = gs.GetCoordinates();

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

wxArrayString GenericSheetMEFrame::GetSheetCoordinates() {
	wxArrayString array;
	std::vector<std::pair<wxString, wxString> > coord = sheet.GetCoordinates();
	for (size_t i = 0; i < coord.size(); i++) {
		std::pair<wxString, wxString> point = coord[i];
		wxString str = "(";
		str.Append(point.first).Append(" , ").
				Append(point.second).Append(")");
		array.Add(str);
	}
	return array;
}
void GenericSheetMEFrame::DeleteAllCoordinates(wxCommandEvent& event) {
	sheet.SetCoordinates(std::vector<std::pair<wxString, wxString> >());
	RebuildCoordinateList();
}
void GenericSheetMEFrame::DeleteCoordinate(wxCommandEvent& event) {
	int index = pointList->GetSelection();

	if (index == wxNOT_FOUND) {
		UtilDialog::ShowErrorMessage("Select a point to delete", "Error");
		return;
	}
	std::vector<std::pair<wxString, wxString> > coord = sheet.GetCoordinates();
	std::vector<std::pair<wxString, wxString> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		if (i != index) {
			newCoordinates.push_back(coord[i]);
		}
	}
	sheet.SetCoordinates(newCoordinates);
	RebuildCoordinateList();
}
void GenericSheetMEFrame::MoveCoordinateUp(wxCommandEvent& event) {
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND && index != 0) {
		std::vector<std::pair<wxString, wxString> > coord = sheet.GetCoordinates();
		std::pair<wxString, wxString> posIndex = coord[index];
		std::pair<wxString, wxString> posIndexMinusOne = coord[index-1];
		coord[index] = posIndexMinusOne;
		coord[index-1] = posIndex;

		sheet.SetCoordinates(coord);
		RebuildCoordinateList(index-1);
	}
}
void GenericSheetMEFrame::MoveCoordinateDown(wxCommandEvent& event) {
	std::vector<std::pair<wxString, wxString> > coord = sheet.GetCoordinates();
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND && index != coord.size()-1) {
		std::pair<wxString, wxString> posIndex = coord[index];
		std::pair<wxString, wxString> posIndexPlusOne = coord[index+1];
		coord[index] = posIndexPlusOne;
		coord[index+1] = posIndex;

		sheet.SetCoordinates(coord);
		RebuildCoordinateList(index+1);
	}
}
void GenericSheetMEFrame::AddPoint(wxCommandEvent& event) {
	std::vector<std::pair<wxString, wxString> > coord = sheet.GetCoordinates();
	if (point1Parser.DefineConstantsAndCheckIfIsValid() && point2Parser.DefineConstantsAndCheckIfIsValid()) {
		coord.push_back(std::pair<wxString, wxString>(point1Parser.GetExpression(), point2Parser.GetExpression()));

		sheet.SetCoordinates(coord);
		RebuildCoordinateList();
	} else {
		UtilDialog::ShowErrorMessage("Point has invalid expression", "Invalid expression");
	}
}
void GenericSheetMEFrame::ChangePoint(wxCommandEvent& event) {
	int index = pointList->GetSelection();

	if (index == wxNOT_FOUND) {
		UtilDialog::ShowErrorMessage("Select a point to change", "Error");
		return;
	}
	if (!(point1Parser.DefineConstantsAndCheckIfIsValid() && point2Parser.DefineConstantsAndCheckIfIsValid())) {
		UtilDialog::ShowErrorMessage("Point has invalid expression", "Invalid expression");
		return;
	}

	std::vector<std::pair<wxString, wxString> > coord = sheet.GetCoordinates();
	std::vector<std::pair<wxString, wxString> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		if (i != index) {
			newCoordinates.push_back(coord[i]);
		} else {
			newCoordinates.push_back(std::pair<wxString, wxString>(point1Parser.GetExpression(), point2Parser.GetExpression()));
		}
	}
	sheet.SetCoordinates(newCoordinates);
	RebuildCoordinateList();
}
void GenericSheetMEFrame::ChangeLabels() {
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
bool GenericSheetMEFrame::TransferDataFromWindow() {
	/*
	 * Precisa setar apenas o plano e o corte. As coordenadas já são gerenciadas usando
	 * o próprio plano.
	 */
	if (plane->GetValue() == "X") {
		sheet.SetCutAtX(cutAtParser.GetExpression());
	} else if (plane->GetValue() == "Y") {
		sheet.SetCutAtY(cutAtParser.GetExpression());
	} else if (plane->GetValue() == "Z") {
		sheet.SetCutAtZ(cutAtParser.GetExpression());
	}
	return true;
}

void GenericSheetMEFrame::UserChangedSelectedPlane(wxCommandEvent& e) {
	ChangeLabels();
}
GenericSheetME GenericSheetMEFrame::GetGenericSheetME() {
	return sheet;
}

void GenericSheetMEFrame::SetGenericSheetME(GenericSheetME s) {
	sheet.Copy(&s);
	cutAtParser.SetExpression(sheet.GetCutAtExpression());
	UpdateControlsWithSheetInformation();
}
wxArrayString GenericSheetMEFrame::GetAvailableCuts() {
	wxArrayString array;

	array.Add(wxT("X"));
	array.Add(wxT("Y"));
	array.Add(wxT("Z"));

	return array;
}
wxString GenericSheetMEFrame::GetSelectedCut() {
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

