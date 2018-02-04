/*
 * HowToShowRadiationPatternResult.cpp
 *
 *  Created on: 18/04/2013
 *      Author: Leandro
 */

#include "HowToShowRadiationPatternResult.h"
#include "emstudio/util/wxmathplot/PolarChartBuilder.h"
#include "emstudio/core/results/RadiationPatternResult.h"
#include "emstudio/util/controls/UtilControls.h"
#include "emstudio/util/converters/Converter.h"

#include <iostream>
using namespace::std;

HowToShowRadiationPatternResult::HowToShowRadiationPatternResult() : HowToShowTableResult() {

}

HowToShowRadiationPatternResult::~HowToShowRadiationPatternResult() {
}

/* Retorna o número de abas. Troca as posições se comparada com o retorno de HowToShowTableResult
 */
int HowToShowRadiationPatternResult::GetNumberOfTabs() {
	int nTabs = 1;

	ResultSmartPointer ptr = GetResult();
	TableResult* result = static_cast<TableResult*>(ptr.get());

	if (result->CanBeInterpretedAsChart()) {
		nTabs = 3;
	}

	return nTabs;
}

wxString HowToShowRadiationPatternResult::GetTabName(int tabIndex) {
	ResultSmartPointer ptr = GetResult();
	TableResult* result = static_cast<TableResult*>(ptr.get());

	wxString tabName;
	if (result->CanBeInterpretedAsChart()) {
		if (tabIndex == 0) {
			tabName = "Polar";
		} else if (tabIndex == 1) {
			tabName = "Cartesian";
		} else if (tabIndex == 2) {
			tabName = "Table";
		}
	} else {
		tabName = "Table";
	}

	return tabName;
}

wxWindow* HowToShowRadiationPatternResult::GetWindow(int tabIndex, wxWindow* parent) {
	ResultSmartPointer ptrToResult = GetResult();
	TableResult* result = static_cast<TableResult*>(ptrToResult.get());

	wxWindow* ptr = 0;

	if (result->CanBeInterpretedAsChart()) {
		if (tabIndex == 0) {
			ptr = new ContainerRadiationDiagramPanel(parent, ptrToResult, result->GetAvailableColors());
		} else if (tabIndex == 1) {
			ptr = new ContainerRadiationDiagramCartesianPanel(parent, ptrToResult);
		} else if (tabIndex == 2) {
			ptr = HowToShowTableResult::GetWindow(1, parent);
		}
	} else {
		ptr = HowToShowTableResult::GetWindow(0, parent);
	}


	return ptr;
}

//mpWindow* HowToShowRadiationPatternResult::BuildPolarChart(wxWindow* parent) {
//	ResultSmartPointer ptr = GetResult();
//	TableResult* result = static_cast<TableResult*>(ptr.get());
//	GenericTable table = result->GetData();
//	vector<GenericTable::ColumnDataRepresentation> columns = table.GetColumns();
//	vector<wxString> columnsLabel = table.GetColumnsLabel();
//
//	mpWindow* plot = new mpWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
//	plot->SetMargins(30, 30, 50, 100);
//
//
//	/* Organiza os dados para construir o diagrama polar */
//	vector<PolarChartBuilder::DataXY> vecDataXY;
//    // A primeira coluna representa o ângulo e, por isso, é os dados em x
//    vector<double> vectorX = columns[0];
//
//    vector<wxColour> availableColors = GetAvailableColors();
//    size_t maxNumberOfColorsAvailable = availableColors.size();
//    vector<wxPen> vectorPen;
//    vector<wxString> vectorName;
//
//    for (size_t col = 1; col < columns.size(); col++) {
//    	vector<double> vectorY;
//
//    	for (size_t row = 0; row < vectorX.size(); row++) {
//    		vectorY.push_back(columns[col][row]);
//    	}
//
//        wxColour color = wxColor(255,255,255);
//        if (col < maxNumberOfColorsAvailable) {
//        	color = availableColors[col];
//        }
//
//    	PolarChartBuilder::DataXY dataxy(vectorX, vectorY);
//
//    	wxPen pen(color, 3, wxSOLID);
//    	vectorPen.push_back(pen);
//    	vectorName.push_back(columnsLabel[col]);
//
//    	vecDataXY.push_back(dataxy);
//    }
//
//    /* Agora constroí o builder e insere os layers no plot */
//    PolarChartBuilder builder;
//    builder.SetNumberOfCircles(6);
//    builder.SetMinimumDistanceYAxis(60);
//    builder.SetData(vecDataXY);
//    vector<mpLayer*> layersAxis = builder.CreateAxisLayer();
//    vector<mpLayer*> layersData = builder.CreateDataLayers(vectorName, vectorPen);
//
//    for (size_t i = 0; i < layersAxis.size(); i++) {
//    	plot->AddLayer(layersAxis[i]);
//    }
//
//    for (size_t i = 0; i < layersData.size(); i++) {
//    	layersData[i]->ShowName(false);
//		plot->AddToggleVisibleLayer(layersData[i]);
//	}
//
//    plot->LockAspect(true);
//
//    mpInfoLegend* leg;
//    plot->AddLayer(leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH));
//
//    plot->EnableDoubleBuffer(true);
//    plot->SetMPScrollbars(false);
//    plot->Fit();
//
//    return plot;
//}


ContainerRadiationDiagramPanel::ContainerRadiationDiagramPanel(wxWindow* parent, ResultSmartPointer result, std::vector<wxColour> availableColors)
		: wxPanel(parent), resultPtr(result) , availableColors(availableColors), radDiagramChart(0) {
	CreateAndInsertControls();
}
ContainerRadiationDiagramPanel::~ContainerRadiationDiagramPanel() {
}
void ContainerRadiationDiagramPanel::CreateAndInsertControls() {
	/*******************************************************/
	/* CONTROLE DE OPÇÕES DE FREQUENCIA                    */
	/*******************************************************/
	freqOptions = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, GetAvailableFrequencies(), wxCB_READONLY);
	freqOptions->SetSelection(0);
	/*******************************************************/
	/* CONTROLE DE OPÇÕES DE DIREÇÃO                       */
	/*******************************************************/
	wxBoxSizer* boxDirectionControl = new wxBoxSizer(wxVERTICAL);
	optClockwise = new wxRadioButton(this, wxID_ANY, "Clockwise");
	optCounterClockwise = new wxRadioButton(this, wxID_ANY, "Counterclockwise");
	boxDirectionControl->Add(optClockwise, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	boxDirectionControl->Add(optCounterClockwise, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);

	/*******************************************************/
	/* CONTROLE DE ROTAÇÃO DE EIXO                         */
	/*******************************************************/
	rotateAxis = new wxSpinCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxDefaultSize, wxSP_WRAP | wxSP_ARROW_KEYS, 0, 360);

	/*******************************************************/
	/* CONTROLE DE ROTAÇÃO DE EIXO                         */
	/*******************************************************/
	txtMinDistance = UtilControls::NewTextCtrlWithDoubleValidator(this);
	txtMinDistance->SetValue("60");
	btnRefresh = new wxButton(this, wxID_ANY, "Refresh");
	Connect(btnRefresh->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ContainerRadiationDiagramPanel::OnRefreshClicked));

	SetDefaultControlValues();

	/*******************************************************/
	/* PAINÉL COM O GRÁFICO COM A PRIMEIRA OPÇÃO           */
	/*******************************************************/
	radDiagramChart = BuildPolarChart(this);

	controlSizer = new wxBoxSizer(wxHORIZONTAL);
	controlSizer->Add(new wxStaticText(this, wxID_ANY, "Frequency:"), 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(freqOptions, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(new wxStaticText(this, wxID_ANY, "Direction:"), 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(boxDirectionControl, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(new wxStaticText(this, wxID_ANY, "Rotate axis:"), 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(rotateAxis, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(new wxStaticText(this, wxID_ANY, "Axis length:"), 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(txtMinDistance, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(btnRefresh, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(radDiagramChart, 95, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	topSizer->Add(controlSizer, 5, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
	topSizer->Layout();
}
wxArrayString ContainerRadiationDiagramPanel::GetAvailableFrequencies() {
	wxArrayString availableFrequencies;

	RadiationPatternResult* result = static_cast<RadiationPatternResult*>(resultPtr.get());
	GenericTable table = result->GetData();
	vector<wxString> columnsLabel = table.GetColumnsLabel();

	if (columnsLabel.size() <= 6) {
		availableFrequencies.Add("All");
	}
    for (size_t col = 1; col < columnsLabel.size(); col++) {
    	availableFrequencies.Add(columnsLabel[col]);
    }

    return availableFrequencies;
}
void ContainerRadiationDiagramPanel::UpdateChart() {
	// Apaga o gráfico polar existente e cria de novo.
	// Tira a janela do sizer
	wxSize previousSize = radDiagramChart->GetSize();
	cout << "previousSize = " << previousSize.x << "\t" << previousSize.y << endl;
	GetSizer()->Detach(radDiagramChart);
	// Destrói o diagrama antigo e cria um novo
	radDiagramChart->Destroy();
	radDiagramChart = BuildPolarChart(this);
	radDiagramChart->SetSize(previousSize);
	cout << "no meio do método = " << radDiagramChart->GetSize().x << "\t" << radDiagramChart->GetSize().y << endl;
	// Retira também o sizer de controle
	GetSizer()->Detach(controlSizer);

	// Adiciona novamente o gráfico e o sizer de controle
	GetSizer()->Add(radDiagramChart, 95, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	GetSizer()->Add(controlSizer, 5, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	// Chama Layout para rearrumar os troço tudo
//	GetSizer()->Fit(this);
//	GetSizer()->SetSizeHints(this);
	GetSizer()->Layout();

//	this->Layout();
	cout << "no fim do método = " << radDiagramChart->GetSize().x << "\t" << radDiagramChart->GetSize().y << endl;
}
void ContainerRadiationDiagramPanel::SetDefaultControlValues() {
	RadiationPatternResult* result = static_cast<RadiationPatternResult*>(resultPtr.get());

	txtMinDistance->SetValue("60");
	if (result->GetPlane().GetValue() == XY) {
		xLabel = "X";
		yLabel = "Y";

		optClockwise->SetValue(false);
		optCounterClockwise->SetValue(true);
		rotateAxis->SetValue(0);
	} else if (result->GetPlane().GetValue() == YZ) {
		xLabel = "Z";
		yLabel = "Y";

		optClockwise->SetValue(true);
		optCounterClockwise->SetValue(false);
		rotateAxis->SetValue(270);
	} else if (result->GetPlane().GetValue() == XZ) {
		xLabel = "Z";
		yLabel = "X";

		optClockwise->SetValue(true);
		optCounterClockwise->SetValue(false);
		rotateAxis->SetValue(270);
	}
}
void ContainerRadiationDiagramPanel::OnRefreshClicked(wxCommandEvent& event) {
	/* Apaga a tela e cria uma nova */
	UpdateChart();
}

mpWindow* ContainerRadiationDiagramPanel::BuildPolarChart(wxWindow* parent) {
	bool showAllFrequencies = freqOptions->GetValue() == "All";
	RadiationPatternResult* result = static_cast<RadiationPatternResult*>(resultPtr.get());
	GenericTable table = result->GetData();
	vector<GenericTable::ColumnDataRepresentation> columns = table.GetColumns();
	vector<wxString> columnsLabel = table.GetColumnsLabel();

	mpWindow* plot = new mpWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
	plot->SetMargins(30, 30, 50, 100);

	/* Organiza os dados para construir o diagrama polar */
	vector<PolarChartBuilder::DataXY> vecDataXY;
    // A primeira coluna representa o ângulo e, por isso, é os dados em x
    vector<double> vectorX = columns[0];

    size_t maxNumberOfColorsAvailable = availableColors.size();
    vector<wxPen> vectorPen;
    vector<wxString> vectorName;

    for (size_t col = 1; col < columns.size(); col++) {
    	if (showAllFrequencies || columnsLabel[col] == freqOptions->GetValue()) {
			vector<double> vectorY;

			for (size_t row = 0; row < vectorX.size(); row++) {
				vectorY.push_back(columns[col][row]);
			}

			wxColour color = wxColor(255,0,0);
			if (col <= maxNumberOfColorsAvailable) {
				color = availableColors[col-1];
			}

			PolarChartBuilder::DataXY dataxy(vectorX, vectorY);

			wxPen pen(color, 3, wxSOLID);
			vectorPen.push_back(pen);
			vectorName.push_back(columnsLabel[col]);

			vecDataXY.push_back(dataxy);
    	}
    }

    /* Agora constroí o builder e insere os layers no plot */
    PolarChartBuilder builder;
    builder.SetNumberOfCircles(6);
    if (Converter::FormattedStringToDouble(txtMinDistance->GetValue()) <= 0) {
    	txtMinDistance->SetValue("60");
    }
    builder.SetYAxisLength(Converter::FormattedStringToDouble(txtMinDistance->GetValue()));
    builder.SetData(vecDataXY);
    builder.SetAxisLabel(xLabel, yLabel);
    builder.SetAxisDirection(optClockwise->GetValue());
    builder.SetInitialAngle(rotateAxis->GetValue());
    vector<mpLayer*> layersAxis = builder.CreateAxisLayer();
    vector<mpLayer*> layersData = builder.CreateDataLayers(vectorName, vectorPen);

    for (size_t i = 0; i < layersAxis.size(); i++) {
    	plot->AddLayer(layersAxis[i]);
    }

    for (size_t i = 0; i < layersData.size(); i++) {
    	layersData[i]->ShowName(false);
		plot->AddToggleVisibleLayer(layersData[i]);
	}

    plot->LockAspect(true);

    mpInfoLegend* leg;
    plot->AddLayer(leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH));

    plot->EnableDoubleBuffer(true);
    plot->SetMPScrollbars(false);
    plot->Fit();

    return plot;
}





ContainerRadiationDiagramCartesianPanel::ContainerRadiationDiagramCartesianPanel(wxWindow* parent, ResultSmartPointer result)
		: wxPanel(parent), resultPtr(result), radDiagramChart(0) {
	CreateAndInsertControls();
}
ContainerRadiationDiagramCartesianPanel::~ContainerRadiationDiagramCartesianPanel() {
}
void ContainerRadiationDiagramCartesianPanel::CreateAndInsertControls() {
	/*******************************************************/
	/* CONTROLE DE OPÇÕES DE FREQUENCIA                    */
	/*******************************************************/
	controlSizer = new wxBoxSizer(wxHORIZONTAL);
	freqOptions = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, GetAvailableFrequencies(), wxCB_READONLY);
	freqOptions->SetSelection(0);

	btnRefresh = new wxButton(this, wxID_ANY, "Refresh");
	Connect(btnRefresh->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ContainerRadiationDiagramCartesianPanel::OnRefreshClicked));

	controlSizer->Add(new wxStaticText(this, wxID_ANY, "Frequency:"), 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(freqOptions, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	controlSizer->Add(btnRefresh, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);

	radDiagramChart = BuildCartesianChart();

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(radDiagramChart, 95, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	topSizer->Add(controlSizer, 5, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
	topSizer->Layout();
}
wxWindow* ContainerRadiationDiagramCartesianPanel::BuildCartesianChart() {
	wxWindow* cartesianPlot;
	if (freqOptions->GetValue() == "All")
		cartesianPlot = GeneratePlotForGenericTable(this, resultPtr, 0, true);
	else {
		RadiationPatternResult* result = static_cast<RadiationPatternResult*>(resultPtr.get());
		GenericTable table = result->GetData();
		vector<wxString> columnsLabel = table.GetColumnsLabel();
		vector<int> columns;
		columns.push_back(0);
	    for (size_t col = 1; col < columnsLabel.size(); col++) {
	    	cout << columnsLabel[col] << endl;
	    	if (columnsLabel[col] == freqOptions->GetValue()) {
	    		columns.push_back(col);
	    		break;
	    	}
    	}
	    cartesianPlot = GeneratePlotForGenericTable(this, resultPtr, 0, false, columns);
	}
	return cartesianPlot;
}

wxArrayString ContainerRadiationDiagramCartesianPanel::GetAvailableFrequencies() {
	wxArrayString availableFrequencies;

	RadiationPatternResult* result = static_cast<RadiationPatternResult*>(resultPtr.get());
	GenericTable table = result->GetData();
	vector<wxString> columnsLabel = table.GetColumnsLabel();

	if (columnsLabel.size() <= 6) {
		availableFrequencies.Add("All");
	}
    for (size_t col = 1; col < columnsLabel.size(); col++) {
    	availableFrequencies.Add(columnsLabel[col]);
    }

    return availableFrequencies;
}
void ContainerRadiationDiagramCartesianPanel::UpdateChart() {
	// Apaga o gráfico polar existente e cria de novo.
	// Tira a janela do sizer
	wxSize previousSize = radDiagramChart->GetSize();
	cout << "previousSize = " << previousSize.x << "\t" << previousSize.y << endl;
	GetSizer()->Detach(radDiagramChart);
	// Destrói o diagrama antigo e cria um novo
	radDiagramChart->Destroy();
	radDiagramChart = BuildCartesianChart();
	radDiagramChart->SetSize(previousSize);
	cout << "no meio do método = " << radDiagramChart->GetSize().x << "\t" << radDiagramChart->GetSize().y << endl;
	// Retira também o sizer de controle
	GetSizer()->Detach(controlSizer);

	// Adiciona novamente o gráfico e o sizer de controle
	GetSizer()->Add(radDiagramChart, 95, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	GetSizer()->Add(controlSizer, 5, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	// Chama Layout para rearrumar os troço tudo
//	GetSizer()->Fit(this);
//	GetSizer()->SetSizeHints(this);
	GetSizer()->Layout();

//	this->Layout();
	cout << "no fim do método = " << radDiagramChart->GetSize().x << "\t" << radDiagramChart->GetSize().y << endl;
}
void ContainerRadiationDiagramCartesianPanel::OnRefreshClicked(wxCommandEvent& event) {
	/* Apaga a tela e cria uma nova */
	UpdateChart();
}
