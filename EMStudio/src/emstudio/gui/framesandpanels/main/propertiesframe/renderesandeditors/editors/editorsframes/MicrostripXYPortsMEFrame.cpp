/*
 * MicrostripXYPortsMEFrame.cpp
 *
 *  Created on: 06/12/2013
 *      Author: leandrocarisio
 */

#include "MicrostripXYPortsMEFrame.h"

#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/controls/UtilControls.h"
#include "emstudio/util/dialogs/UtilDialog.h"

MicrostripXYPortsMEFrame::MicrostripXYPortsMEFrame(wxWindow* parent, MicrostripXYPortsME m, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title), ports(m) {

	CreateControlsAndInsert();
	UpdateControlsWithPortsInformation();
}

MicrostripXYPortsMEFrame::~MicrostripXYPortsMEFrame() {

}

void MicrostripXYPortsMEFrame::OnSetFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == xCoor->GetId()) {
		xCoor->SetValue(xParser.GetExpression());
		xCoor->SelectAll();
	} else if (event.GetId() == yCoor->GetId()) {
		yCoor->SetValue(yParser.GetExpression());
		yCoor->SelectAll();
	}

	event.Skip();
}
void MicrostripXYPortsMEFrame::OnLostFocusEvent(wxFocusEvent& event) {
	if (event.GetId() == xCoor->GetId()) {
		xParser.SetExpression(xCoor->GetValue());
		wxString value = xParser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(xParser.Eval(), 2) : "Invalid expression";
		xCoor->SetValue(value);
	} else if (event.GetId() == yCoor->GetId()) {
		yParser.SetExpression(yCoor->GetValue());
		wxString value = yParser.DefineConstantsAndCheckIfIsValid() ? Converter::DoubleToFormattedString(yParser.Eval(), 2) : "Invalid expression";
		yCoor->SetValue(value);
	}
	event.Skip();
}
void MicrostripXYPortsMEFrame::CreateControlsAndInsert() {
	/**********************************************************/
	/* PAINÉL PRO USUÁRIO ESCOLHER ENTRAR COM AS PORTAS       */
	/**********************************************************/
	wxStaticText* lblPoint = new wxStaticText(this, wxID_STATIC, wxT("(x, y) = "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	xCoor = UtilControls::NewTextCtrlForMathExpression(this);
	xCoor->Bind(wxEVT_SET_FOCUS, &MicrostripXYPortsMEFrame::OnSetFocusEvent, this);
	xCoor->Bind(wxEVT_KILL_FOCUS, &MicrostripXYPortsMEFrame::OnLostFocusEvent, this);
	wxStaticText* lblComma = new wxStaticText(this, wxID_STATIC, wxT(", "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	yCoor = UtilControls::NewTextCtrlForMathExpression(this);
	yCoor->Bind(wxEVT_SET_FOCUS, &MicrostripXYPortsMEFrame::OnSetFocusEvent, this);
	yCoor->Bind(wxEVT_KILL_FOCUS, &MicrostripXYPortsMEFrame::OnLostFocusEvent, this);

	addPoint = new wxButton(this, wxID_ANY, "Add");
	Connect(addPoint->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MicrostripXYPortsMEFrame::AddPoint));
	changePoint = new wxButton(this, wxID_ANY, "Change");
	Connect(changePoint->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MicrostripXYPortsMEFrame::ChangePoint));

	wxFlexGridSizer* addPointGridSizer = new wxFlexGridSizer(1, 6, 0, 0);
	addPointGridSizer->AddGrowableCol(1);
	addPointGridSizer->AddGrowableCol(3);
	addPointGridSizer->Add(lblPoint, 0, wxALL | wxALIGN_LEFT, 5);
	addPointGridSizer->Add(xCoor, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	addPointGridSizer->Add(lblComma, 0, wxALL | wxALIGN_LEFT, 5);
	addPointGridSizer->Add(yCoor, 0, wxALL | wxALIGN_LEFT | wxEXPAND, 5);
	addPointGridSizer->Add(addPoint, 0, wxALL | wxALIGN_LEFT, 5);
	addPointGridSizer->Add(changePoint, 0, wxALL | wxALIGN_LEFT, 5);
	/**********************************************************************************/
	/* PAINÉL COM A CAIXA DE LISTAGEM E OS BOTÕES DE MANIPULAÇÃO DA CAIXA DE LISTAGEM */
	/**********************************************************************************/
//	wxFlexGridSizer* portsGrid = new wxFlexGridSizer(2,2,0,0);
	wxBoxSizer* portsGrid = new wxBoxSizer(wxHORIZONTAL);
//	portsGrid->AddGrowableCol(0);
//	portsGrid->AddGrowableCol(1);

	wxStaticText* lblPointList = new wxStaticText(this, wxID_STATIC, wxT("Ports:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
//	portsGrid->Add(lblPointList, 0, wxALL | wxALIGN_LEFT | wxEXPAND , 5);
//	portsGrid->Add(new wxStaticText(this, wxID_STATIC, wxT("")));

	pointList = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, GetPortsCoordinates(), wxLB_SINGLE | wxLB_HSCROLL | wxLB_NEEDED_SB);
	Connect(pointList->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(MicrostripXYPortsMEFrame::CoordinateSelected));
	up = new wxButton(this, wxID_ANY, "Up");
	down = new wxButton(this, wxID_ANY, "Down");
	del = new wxButton(this, wxID_ANY, "Del");
	delAll = new wxButton(this, wxID_ANY, "Del All");
	Connect(up->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MicrostripXYPortsMEFrame::MoveCoordinateUp));
	Connect(down->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MicrostripXYPortsMEFrame::MoveCoordinateDown));
	Connect(del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MicrostripXYPortsMEFrame::DeleteCoordinate));
	Connect(delAll->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MicrostripXYPortsMEFrame::DeleteAllCoordinates));

	wxBoxSizer* moveCoordinatesSizer = new wxBoxSizer(wxVERTICAL);
	moveCoordinatesSizer->Add(up, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(down, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(del, 0, wxALL | wxALIGN_CENTER, 5);
	moveCoordinatesSizer->Add(delAll, 0, wxALL | wxALIGN_CENTER, 5);

//	portsGrid->Add(pointList, 2, wxALL | wxALIGN_LEFT | wxEXPAND , 5);
//	portsGrid->Add(moveCoordinatesSizer, 1);
	portsGrid->Add(pointList, 1, wxALL | wxALIGN_LEFT | wxEXPAND , 5);
	portsGrid->Add(moveCoordinatesSizer);
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
	topSizer->AddGrowableRow(0);
	topSizer->AddGrowableRow(1);
	topSizer->Add(addPointGridSizer,0,wxEXPAND);
	topSizer->Add(lblPointList, 0, wxALL | wxALIGN_LEFT | wxEXPAND);
	topSizer->Add(portsGrid,0,wxEXPAND);
	topSizer->Add(buttonSizer,0,wxALIGN_CENTER);

	/* Preenche os controles */
	UpdateControlsWithPortsInformation();

	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}
void MicrostripXYPortsMEFrame::UpdateControlsWithPortsInformation() {
	RebuildCoordinateList();
}

void MicrostripXYPortsMEFrame::CoordinateSelected(wxCommandEvent& event) {
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND) {
		xCoor->SetValue(ports.GetCoordinates()[index].first);
		xParser.SetExpression(xCoor->GetValue());
		yCoor->SetValue(ports.GetCoordinates()[index].second);
		yParser.SetExpression(yCoor->GetValue());
	}
}
void MicrostripXYPortsMEFrame::RebuildCoordinateList(int selectedIndex) {
	pointList->Clear();
	wxArrayString coordinatesList = GetPortsCoordinates();
	if (coordinatesList.size() != 0) {
		pointList->Insert(coordinatesList, 0);
	}
	if (selectedIndex != wxNOT_FOUND && selectedIndex < coordinatesList.size()) {
		pointList->SetSelection(selectedIndex);
	}
}
wxArrayString MicrostripXYPortsMEFrame::GetPortsCoordinates() {
	wxArrayString array;
	std::vector<std::pair<wxString, wxString> > coord = ports.GetCoordinates();
	for (size_t i = 0; i < coord.size(); i++) {
		std::pair<wxString, wxString> point = coord[i];

		wxString str = "#";
		str.Append(Converter::IntToFormattedString(i+2)).    // Começa a contar a partir da porta 2
				Append(" = (").
				Append(point.first).Append(" , ").
				Append(point.second).Append(")");
		array.Add(str);
	}
	return array;
}
void MicrostripXYPortsMEFrame::DeleteAllCoordinates(wxCommandEvent& event) {
	ports.SetCoordinates(std::vector<std::pair<wxString, wxString> >());
	RebuildCoordinateList();
}
void MicrostripXYPortsMEFrame::DeleteCoordinate(wxCommandEvent& event) {
	int index = pointList->GetSelection();

	if (index == wxNOT_FOUND) {
		UtilDialog::ShowErrorMessage("Select a point to delete", "Error");
		return;
	}
	std::vector<std::pair<wxString, wxString> > coord = ports.GetCoordinates();
	std::vector<std::pair<wxString, wxString> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		if (i != index) {
			newCoordinates.push_back(coord[i]);
		}
	}
	ports.SetCoordinates(newCoordinates);
	RebuildCoordinateList();
}
void MicrostripXYPortsMEFrame::MoveCoordinateUp(wxCommandEvent& event) {
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND && index != 0) {
		std::vector<std::pair<wxString, wxString> > coord = ports.GetCoordinates();
		std::pair<wxString, wxString> posIndex = coord[index];
		std::pair<wxString, wxString> posIndexMinusOne = coord[index-1];
		coord[index] = posIndexMinusOne;
		coord[index-1] = posIndex;

		ports.SetCoordinates(coord);
		RebuildCoordinateList(index-1);
	}
}
void MicrostripXYPortsMEFrame::MoveCoordinateDown(wxCommandEvent& event) {
	std::vector<std::pair<wxString, wxString> > coord = ports.GetCoordinates();
	int index = pointList->GetSelection();
	if (index != wxNOT_FOUND && index != coord.size()-1) {
		std::pair<wxString, wxString> posIndex = coord[index];
		std::pair<wxString, wxString> posIndexPlusOne = coord[index+1];
		coord[index] = posIndexPlusOne;
		coord[index+1] = posIndex;

		ports.SetCoordinates(coord);
		RebuildCoordinateList(index+1);
	}
}
void MicrostripXYPortsMEFrame::AddPoint(wxCommandEvent& event) {
	std::vector<std::pair<wxString, wxString> > coord = ports.GetCoordinates();
	if (xParser.DefineConstantsAndCheckIfIsValid() && yParser.DefineConstantsAndCheckIfIsValid()) {
		coord.push_back(std::pair<wxString, wxString>(xParser.GetExpression(), yParser.GetExpression()));

		ports.SetCoordinates(coord);
		RebuildCoordinateList();
	} else {
		UtilDialog::ShowErrorMessage("Point has invalid expression", "Invalid expression");
	}
}
void MicrostripXYPortsMEFrame::ChangePoint(wxCommandEvent& event) {
	int index = pointList->GetSelection();

	if (index == wxNOT_FOUND) {
		UtilDialog::ShowErrorMessage("Select a point to change", "Error");
		return;
	}
	if (!(xParser.DefineConstantsAndCheckIfIsValid() && yParser.DefineConstantsAndCheckIfIsValid())) {
		UtilDialog::ShowErrorMessage("Point has invalid expression", "Invalid expression");
		return;
	}

	std::vector<std::pair<wxString, wxString> > coord = ports.GetCoordinates();
	std::vector<std::pair<wxString, wxString> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		if (i != index) {
			newCoordinates.push_back(coord[i]);
		} else {
			newCoordinates.push_back(std::pair<wxString, wxString>(xParser.GetExpression(), yParser.GetExpression()));
		}
	}
	ports.SetCoordinates(newCoordinates);
	RebuildCoordinateList();
}
bool MicrostripXYPortsMEFrame::TransferDataFromWindow() {
	/*
	 * Precisa apenar retornar true. As coordenadas já são gerenciadas usando a variável ports.
	 */
	return true;
}

MicrostripXYPortsME MicrostripXYPortsMEFrame::GetMicrostripXYPortsME() {
	return ports;
}

void MicrostripXYPortsMEFrame::SetMicrostripXYPortsME(MicrostripXYPortsME m) {
	ports.Copy(&m);
	UpdateControlsWithPortsInformation();
}
