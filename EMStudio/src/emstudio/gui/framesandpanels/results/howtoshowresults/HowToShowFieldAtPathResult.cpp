/*
 * HowToShowFieldAtPathResult.cpp
 *
 *  Created on: 26/09/2013
 *      Author: leandrocarisio
 */

#include "HowToShowFieldAtPathResult.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/BasicCopyPasteGrid.h"
#include "emstudio/util/constants/Constants.h"

HowToShowFieldAtPathResult::HowToShowFieldAtPathResult() : HowToShowResults() {

}

HowToShowFieldAtPathResult::~HowToShowFieldAtPathResult() {

}

SwitchCartesianChartPanel::DatasXYPerChart HowToShowFieldAtPathResult::GetDatasXYLinearDB(std::vector<int> selectedColumns) {
	cout << "\tGetDatasXYLinearDB" << endl;
	for (int i = 0; i < selectedColumns.size(); i++) {
		cout << "\t\t" << selectedColumns[i] << endl;
	}
	SwitchCartesianChartPanel::DatasXYPerChart datasXY;
	std::vector<CartesianChartBuilder::DataXY> dataXYLinear;
	std::vector<CartesianChartBuilder::DataXY> dataXYDB;

	ResultSmartPointer ptrToResult = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptrToResult.get());

	vector<double> vectorX = tableResult->GetData().GetColumn(0);
	for (size_t i = 0; i < selectedColumns.size(); i++) {
		vector<double> vectorYLinear = tableResult->GetData().GetColumn(selectedColumns[i]);
		vector<double> vectorYDB = ToDB(vectorYLinear, -150, 20);

		CartesianChartBuilder::DataXY vecXYLinear;
		vecXYLinear.first = vectorX;
		vecXYLinear.second = vectorYLinear;
		dataXYLinear.push_back(vecXYLinear);

		CartesianChartBuilder::DataXY vecXYDB;
		vecXYDB.first = vectorX;
		vecXYDB.second = vectorYDB;
		dataXYDB.push_back(vecXYDB);

	}

	datasXY.push_back(dataXYLinear);
	datasXY.push_back(dataXYDB);

	return datasXY;
}
SwitchCartesianChartPanel::DatasXYPerChart HowToShowFieldAtPathResult::GetDatasXYDegreeRadian(std::vector<int> selectedColumns) {
	cout << "\tGetDatasXYDegreeRadian" << endl;
	for (int i = 0; i < selectedColumns.size(); i++) {
		cout << "\t\t" << selectedColumns[i] << endl;
	}

	SwitchCartesianChartPanel::DatasXYPerChart datasXY;
	std::vector<CartesianChartBuilder::DataXY> dataXYRadian;
	std::vector<CartesianChartBuilder::DataXY> dataXYDegree;

	ResultSmartPointer ptrToResult = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptrToResult.get());

	vector<double> vectorX = tableResult->GetData().GetColumn(0);
	for (size_t i = 0; i < selectedColumns.size(); i++) {
		vector<double> vectorYRadian = tableResult->GetData().GetColumn(selectedColumns[i]);
		vector<double> vectorYDegree = ToDegree(vectorYRadian);

		CartesianChartBuilder::DataXY vecXYDegree;
		vecXYDegree.first = vectorX;
		vecXYDegree.second = vectorYDegree;
		dataXYDegree.push_back(vecXYDegree);

		CartesianChartBuilder::DataXY vecXYRadian;
		vecXYRadian.first = vectorX;
		vecXYRadian.second = vectorYRadian;
		dataXYRadian.push_back(vecXYRadian);

	}

	datasXY.push_back(dataXYDegree);
	datasXY.push_back(dataXYRadian);

	return datasXY;
}

SwitchCartesianChartPanel::PlotsLabelsPerChart HowToShowFieldAtPathResult::GetPlotLabels(std::vector<int> selectedColumns) {
	cout << "\tGetPlotLabels" << endl;
	for (int i = 0; i < selectedColumns.size(); i++) {
		cout << "\t\t" << selectedColumns[i] << endl;
	}
	/* Nesse caso, independente do gráfico, os labels são iguais.
	 * Por exemplo, se o usuário selecionar escala linear ou db, os valores não mudam.
	 * Então é necessário criar o vetor dos labels e depois inserir duas versões dela no plotsLabel, uma para escala linear, outra para db.
	 * (Ou uma para radiano, outra para graus).
	 */
	SwitchCartesianChartPanel::PlotsLabelsPerChart plotsLabels;
	std::vector<wxString> labelsPerChart;

	ResultSmartPointer ptrToResult = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptrToResult.get());

	for (size_t i = 0; i < selectedColumns.size(); i++) {
		/* Para mostrar os gráficos, pega só a informação do campo e desconsidera unidades. Unidades estaram presentes nos botões de escala */
		wxString label = tableResult->GetData().GetColumnsLabel()[selectedColumns[i]];
		label = label.Mid(0,2);

		labelsPerChart.push_back(label);
	}

	plotsLabels.push_back(labelsPerChart);
	plotsLabels.push_back(labelsPerChart);

	return plotsLabels;
}
std::vector<wxString> HowToShowFieldAtPathResult::GetAxisLabels(int nLabels) {
	ResultSmartPointer ptrToResult = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptrToResult.get());

	std::vector<wxString> labels;
	for (int i = 0; i < nLabels; i++)
		labels.push_back(tableResult->GetData().GetColumnsLabel()[0]);

	return labels;
}
/* Retorna o número de abas.
 */
int HowToShowFieldAtPathResult::GetNumberOfTabs() {
	int nTabs = 6;

	return nTabs;
}
wxString HowToShowFieldAtPathResult::GetTabName(int tabIndex) {
	wxString tabName;

	if (tabIndex == 0)
		tabName = "E - Amplitude";
	else if (tabIndex == 1)
		tabName = "E - Phase";
	else if (tabIndex == 2)
		tabName = "H - Amplitude";
	else if (tabIndex == 3)
		tabName = "H - Phase";
	else if (tabIndex == 4)
		tabName = "Table - Amplitude";
	else if (tabIndex == 5)
		tabName = "Table - Phase";
	return tabName;
}
/* Retorna a aba
 *
 * De acordo com FieldAtPathResult, os dados na tabela estão organizados da seguinte forma:
 * 0 - positionField
 * 1 - ExMag
 * 2 - EyMag
 * 3 - EzMag
 * 4 - HxMag
 * 5 - HyMag
 * 6 - HzMag
 * 7 - ExPhase
 * 8 - EyPhase
 * 9 - EzPhase
 * 10 - HxPhase
 * 11 - HyPhase
 * 12 - HzPhase
 */
wxWindow* HowToShowFieldAtPathResult::GetWindow(int tabIndex, wxWindow* parent) {
	std::vector<int> columnsEMag;
	std::vector<int> columnsEPhase;
	std::vector<int> columnsHMag;
	std::vector<int> columnsHPhase;
	std::vector<int> columnsEHMag; 		columnsEHMag.push_back(0);   // Pra mostrar na tabela tem que colocar também a coluna 0
	std::vector<int> columnsEHPhase;	columnsEHPhase.push_back(0); // Pra mostrar na tabela tem que colocar também a coluna 0

	for (int i = 1; i <= 3; i++) columnsEMag.push_back(i);
	for (int i = 7; i <= 9; i++) columnsEPhase.push_back(i);
	for (int i = 4; i <= 6; i++) columnsHMag.push_back(i);
	for (int i = 10; i <= 12; i++) columnsHPhase.push_back(i);
	for (int i = 1; i <= 6; i++) columnsEHMag.push_back(i);
	for (int i = 7; i <= 12; i++) columnsEHPhase.push_back(i);

	ResultSmartPointer ptrToResult = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptrToResult.get());
	wxWindow* ptr = 0;

	std::vector<wxString> buttonLabelLinearVMDB; buttonLabelLinearVMDB.push_back("Linear (V/m)"); buttonLabelLinearVMDB.push_back("dB");
	std::vector<wxString> buttonLabelLinearAMDB; buttonLabelLinearAMDB.push_back("Linear (A/m)"); buttonLabelLinearAMDB.push_back("dB");
	std::vector<wxString> buttonLabelDegreeRadian; buttonLabelDegreeRadian.push_back("Degree"); buttonLabelDegreeRadian.push_back("Radian");

	cout << "tabIndex = " << tabIndex << endl;
	switch(tabIndex) {
	case 0:
	{
		ptr = new SwitchCartesianChartPanel(parent, buttonLabelLinearVMDB, GetDatasXYLinearDB(columnsEMag), GetPlotLabels(columnsEMag), GetAxisLabels(columnsEMag.size()), tableResult->GetAvailableColors());
		break;
	}
	case 1:
	{
		ptr = new SwitchCartesianChartPanel(parent, buttonLabelDegreeRadian, GetDatasXYDegreeRadian(columnsEPhase), GetPlotLabels(columnsEPhase), GetAxisLabels(columnsEPhase.size()), tableResult->GetAvailableColors());
		break;
	}
	case 2:
	{
		ptr = new SwitchCartesianChartPanel(parent, buttonLabelLinearAMDB, GetDatasXYLinearDB(columnsHMag), GetPlotLabels(columnsHMag), GetAxisLabels(columnsHMag.size()), tableResult->GetAvailableColors());
		break;
	}
	case 3:
	{
		ptr = new SwitchCartesianChartPanel(parent, buttonLabelDegreeRadian, GetDatasXYDegreeRadian(columnsHPhase), GetPlotLabels(columnsHPhase), GetAxisLabels(columnsHPhase.size()), tableResult->GetAvailableColors());
		break;
	}
	case 4:
	{
		ptr = GenerateGridForGenericTable(parent, new TableBaseForGenericTable(GetResult(), false, columnsEHMag));
		break;
	}
	case 5:
	{
		ptr = GenerateGridForGenericTable(parent, new TableBaseForGenericTable(GetResult(), false, columnsEHPhase));
		break;
	}
	} // END SWITCH

	return ptr;
}

SwitchCartesianChartPanel::SwitchCartesianChartPanel(wxWindow* parent, std::vector<wxString> buttonsLabels,
		DatasXYPerChart datas, PlotsLabelsPerChart plotLabels, std::vector<wxString> xAxisLabels, std::vector<wxColour> availableColors)
			: wxPanel(parent), buttonsLabels(buttonsLabels), datas(datas), plotLabels(plotLabels), xAxisLabels(xAxisLabels), availableColors(availableColors) {

	cout << "SwitchCartesianChartPanel" << endl;

	for (int i = 0; i < buttonsLabels.size(); i++)
		cout << "buttonsLabel: " << buttonsLabels[i] << endl;

	cout << "Datas.size = " << datas.size() << endl;
	for (int i = 0; i < datas.size(); i++) {
		cout << "\tdatas[i].size = " << datas[i].size() << endl;
	}
	cout << "plotlabels.size = " << plotLabels.size() << endl;
	for (int i = 0; i < plotLabels.size(); i++) {
		cout << "\tplotlabels[i].size = " << plotLabels[i].size() << endl;
	}
	cout << "xAxisLabels.size = " << xAxisLabels.size() << endl;

	CreateControlsAndInsert();
}
SwitchCartesianChartPanel::~SwitchCartesianChartPanel() {

}

void SwitchCartesianChartPanel::OptButtonChanged(wxCommandEvent& event) {
	visualizationChart->DelAllLayers(true, false);

	size_t buttonChecked = 0;
	for (buttonChecked = 0; buttonChecked < optButtons.size(); buttonChecked++) {
		if (optButtons[buttonChecked]->GetValue()) {
			break;
		}
	}

	GeneratePlotForGenericTable(this,
			datas[buttonChecked],
			xAxisLabels[buttonChecked],
			plotLabels[buttonChecked],
			visualizationChart,
			availableColors);

	visualizationChart->Update();
	visualizationChart->Refresh();
}

void SwitchCartesianChartPanel::CreateControlsAndInsert() {
	/*******************************************************/
	/* PAINÉL COM O GRÁFICO COM A PRIMEIRA OPÇÃO           */
	/*******************************************************/
	visualizationChart = GeneratePlotForGenericTable(this,
			datas[0],
			xAxisLabels[0],
			plotLabels[0],
			0,
			availableColors);

	/*******************************************************/
	/* CONTROLE DE OPÇÕES                                  */
	/*******************************************************/
	wxBoxSizer* boxScaleControl = new wxBoxSizer(wxVERTICAL);
	for (size_t i = 0; i < buttonsLabels.size(); i++) {
		wxRadioButton* opt = new wxRadioButton(this, wxID_ANY, buttonsLabels[i]);
		Connect(opt->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(SwitchCartesianChartPanel::OptButtonChanged));
		boxScaleControl->Add(opt, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
		optButtons.push_back(opt);
	}
	optButtons[0]->SetValue(true);

//	wxFlexGridSizer* topSizer = new wxFlexGridSizer(2, 1, 0, 0);
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(visualizationChart, 95, wxALL | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);
	topSizer->Add(boxScaleControl, 5, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxEXPAND, 5);

	/* Adequa o tamanho */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
	topSizer->Layout();
}

vector<double> ToDB(vector<double> linear, double minDB, double mult) {
	double minLinear = pow(10,minDB/20);
	vector<double> result;
	for (size_t i = 0; i < linear.size(); i++) {
		double value = linear[i];
		if (value < minLinear) value = minLinear;

		double valueDB = mult*log10(abs(value));
		result.push_back(valueDB);
	}
	return result;
}

vector<double> ToDegree(vector<double> rad) {
	vector<double> result;
	for (size_t i = 0; i < rad.size(); i++) {
		result.push_back(rad[i]*180/PI);
	}
	return result;
}
