/*
 * HowToShowTableResult.cpp
 *
 *  Created on: 13/03/2012
 *      Author: leandrocarisio
 */

#include "HowToShowTableResult.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/BasicCopyPasteGrid.h"
#include "emstudio/util/wxmathplot/CartesianChartBuilder.h"
#include <iostream>
using namespace::std;

HowToShowTableResult::HowToShowTableResult() : HowToShowResults() {
}

HowToShowTableResult::~HowToShowTableResult() {
}


/* Retorna o número de abas.
 * Se a tabela puder ser visualizada como gráfico, são 2 abas.
 * Caso contrário, apenas uma aba contendo os gráficos será visível.
 */
int HowToShowTableResult::GetNumberOfTabs() {
	int nTabs = 1;
	ResultSmartPointer ptr = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptr.get());
	if (tableResult->CanBeInterpretedAsChart()) {
		nTabs = 2;
	}

	return nTabs;
}

wxString HowToShowTableResult::GetTabName(int tabIndex) {
	ResultSmartPointer ptr = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptr.get());

	wxString tabName;
	if (tabIndex == 0 && tableResult->CanBeInterpretedAsChart()) {
		tabName = "Chart";
	} else if (tabIndex == 0 || tabIndex == 1) {
		tabName = "Table";
	}

	return tabName;
}
/* Retorna a aba */
wxWindow* HowToShowTableResult::GetWindow(int tabIndex, wxWindow* parent) {
	ResultSmartPointer ptrToResult = GetResult();
	TableResult* tableResult = static_cast<TableResult*>(ptrToResult.get());

	wxWindow* ptr = 0;

	wxString tabName;
	if (tabIndex == 0 && tableResult->CanBeInterpretedAsChart()) {
		ptr = GeneratePlotForGenericTable(parent, GetResult(), 0, true);
	} else if (tabIndex == 0 || tabIndex == 1) {
		TableBaseForGenericTable* tableBase = new TableBaseForGenericTable(GetResult(), true);
		wxGrid* grid = GenerateGridForGenericTable(parent, tableBase);
		ptr = grid;
	}


	return ptr;
}

TableBaseForGenericTable::TableBaseForGenericTable(ResultSmartPointer result, bool showAllColumns, std::vector<int> columnsNumbers)
		: result(result), showAllColumns(showAllColumns), columnsNumbers(columnsNumbers) {

}
TableBaseForGenericTable::~TableBaseForGenericTable() {

}
int TableBaseForGenericTable::GetNumberRows() {
	GenericTable table = static_cast<TableResult*>(result.get())->GetData();

	if (table.GetColumns().size() == 0) {
		return 0;
	}
	else {
		return table.GetColumn(0).size();
	}
}
int TableBaseForGenericTable::GetNumberCols() {
	GenericTable table = static_cast<TableResult*>(result.get())->GetData();

	if (showAllColumns)
		return table.GetColumns().size();
	else
		return columnsNumbers.size();
}
wxString TableBaseForGenericTable::GetValue(int row, int col) {
	wxString text = "";

	GenericTable table = static_cast<TableResult*>(result.get())->GetData();

	double val;
	if (showAllColumns)
		val = table.GetColumn(col)[row];
	else
		val = table.GetColumn(columnsNumbers[col])[row];

	if (abs(val) < 0.001 && val != 0) {
		text = Converter::DoubleToScientificNotationString(val);
	} else {
		text = Converter::DoubleToFormattedString(val);
	}
	return text;
}
void TableBaseForGenericTable::SetValue(int row, int col, const wxString &value) {
	// Não faz nada. A ideia é apenas apresentar os resultados
}

wxString TableBaseForGenericTable::GetColLabelValue(int col) {
	wxString text;

	vector<wxString> colsLabel = static_cast<TableResult*>(result.get())->GetData().GetColumnsLabel();

	if (showAllColumns)
		text = colsLabel[col];
	else
		text = colsLabel[columnsNumbers[col]];

	return text;
}

wxGrid* GenerateGridForGenericTable(wxWindow* parent, TableBaseForGenericTable* tableBase) {
	wxGrid* grid = new BasicCopyPasteGrid(parent, wxID_ANY, false);
	grid->SetTable(tableBase, false);
	grid->HideRowLabels(); // Os rótulos da linha são exibidos como dados.
	grid->EnableDragGridSize(false);
	grid->EnableDragCell(false);
	grid->EnableEditing(false);
//		Se esta linha for habilitada, todos os dados terão que ser carregados antes de mostrar o grid, gerando atraso.
//		grid->Fit();
	int w = grid->GetParent()->GetClientSize().GetWidth();
	int total_col = grid->GetNumberCols();
	for (int i = 0; i < total_col; i++) {
		grid->AutoSizeColLabelSize(i);
		int colWidth = grid->GetColSize(i);
		if (colWidth < w/(2*total_col))
			grid->SetColSize(i, w/(2*total_col));
	}
	return grid;
}
mpWindow* GeneratePlotForGenericTable(wxWindow* parent, ResultSmartPointer result, mpWindow* plot, bool showAllColumns, std::vector<int> columnsNumbers) {
	/* Pega a tabela, as colunas e os rótulos das colunas */
	TableResult* tableResult = static_cast<TableResult*>(result.get());
	GenericTable table = tableResult->GetData();
	vector<GenericTable::ColumnDataRepresentation> columns = table.GetColumns();
	vector<wxString> columnsLabel = table.GetColumnsLabel();

	/* */
	if (showAllColumns) {
		columnsNumbers.clear();
		for (size_t i = 0; i < columns.size(); i++)
			columnsNumbers.push_back(i);
	}

	/* Label no eixo X */
	wxString xAxisLabel = columnsLabel[columnsNumbers[0]];
	/* Label das outras colunas */
    vector<wxString> vectorName;

    // Considera que a primeira coluna (índice 0) representa o label das linhas
    vector<CartesianChartBuilder::DataXY> vecDataXY;
    vector<double> vectorx = columns[columnsNumbers[0]];

    /* Itera na tabela e cria vetor com os dados (vecDataXY) */
    for (size_t col = 1; col < columnsNumbers.size(); col++) {
    	std::vector<double> vectory;
    	vectory = columns[columnsNumbers[col]];
//    	for (size_t row = 0; row < vectorx.size(); row++) {
//    		vectory.push_back(columns[columnsNumbers[col]][row]);
//    	}

        CartesianChartBuilder::DataXY dataxy(vectorx, vectory);
    	vectorName.push_back(columnsLabel[columnsNumbers[col]]);
    	vecDataXY.push_back(dataxy);
    }

    /* Após a preparação dos dados, constrói o builder e insere os layers no plot*/
    return GeneratePlotForGenericTable(parent, vecDataXY, xAxisLabel, vectorName, plot, tableResult->GetAvailableColors());
}


mpWindow* GeneratePlotForGenericTable(wxWindow* parent, vector<CartesianChartBuilder::DataXY> vecDataXY, wxString xAxisLabel, std::vector<wxString> columnsName, mpWindow* plot, std::vector<wxColour> availableColors) {
	size_t maxNumberOfColorsAvailable = availableColors.size();

	/* Cria a janela com o gráfico */
	if (plot == 0) {
		plot = new mpWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
	}
	plot->SetMargins(30, 30, 50, 100);
	/* Canetas usadas no desenho dos layers */
    vector<wxPen> vectorPen;

    /* Itera na tabela e cria o vetor de cores */
    for (size_t col = 0; col < columnsName.size(); col++) {
        wxColour color = wxColor(0,0,0);
        if (col < maxNumberOfColorsAvailable) {
        	color = availableColors[col];
        }
    	wxPen pen(color, 3, wxSOLID);
    	vectorPen.push_back(pen);
    }

    /* Após a preparação dos dados, constrói o builder e insere os layers no plot*/
	CartesianChartBuilder chartBuilder;
	chartBuilder.SetXAxisLabel(xAxisLabel);
	chartBuilder.SetYAxisLabel("");
	chartBuilder.SetData(vecDataXY);
	std::vector<mpLayer*> layersAxis = chartBuilder.CreateAxisLayer();
	vector<mpLayer*> layersData = chartBuilder.CreateDataLayers(columnsName, vectorPen);

    for (size_t i = 0; i < layersAxis.size(); i++) {
    	plot->AddLayer(layersAxis[i]);
    }

    for (size_t i = 0; i < layersData.size(); i++) {
    	layersData[i]->ShowName(false);
		plot->AddToggleVisibleLayer(layersData[i]);
	}

    mpInfoLegend* leg;
    plot->AddLayer(leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH));


    plot->EnableDoubleBuffer(true);
    plot->SetMPScrollbars(false);
    plot->Fit();

    return plot;
}



//mpWindow* GeneratePlotForGenericTable(wxWindow* parent, ResultSmartPointer result, mpWindow* plot, bool showAllColumns, std::vector<int> columnsNumbers) {
//	/* Cores padrão */
//	vector<wxColour> availableColors;
//	availableColors.push_back(wxColour(0,0,255));
//	availableColors.push_back(wxColour(255,0,0));
//	availableColors.push_back(wxColour(34,177,76));
//	availableColors.push_back(wxColour(198,13,193));
//	availableColors.push_back(wxColour(224,107,37));
//	size_t maxNumberOfColorsAvailable = availableColors.size();
//
//	/* Pega a tabela, as colunas e os rótulos das colunas */
//	TableResult* tableResult = static_cast<TableResult*>(result.get());
//	GenericTable table = tableResult->GetData();
//	vector<GenericTable::ColumnDataRepresentation> columns = table.GetColumns();
//	vector<wxString> columnsLabel = table.GetColumnsLabel();
//
//	/* */
//	if (showAllColumns) {
//		columnsNumbers.clear();
//		for (size_t i = 0; i < columns.size(); i++)
//			columnsNumbers.push_back(i);
//	}
//
//	/* Cria a janela com o gráfico */
//	if (plot == 0) {
//		plot = new mpWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
//	}
//	plot->SetMargins(30, 30, 50, 100);
//	/* Canetas usadas no desenho dos layers */
//    vector<wxPen> vectorPen;
//    vector<wxString> vectorName;
//
//    // Considera que a primeira coluna (índice 0) representa o label das linhas
//    vector<CartesianChartBuilder::DataXY> vecDataXY;
//    vector<double> vectorx = columns[columnsNumbers[0]];
//
//    /* Itera na tabela e cria os layers */
//    for (size_t col = 1; col < columnsNumbers.size(); col++) {
//    	std::vector<double> vectory;
//    	for (size_t row = 0; row < vectorx.size(); row++) {
//    		vectory.push_back(columns[columnsNumbers[col]][row]);
//    	}
//
//        wxColour color = wxColor(255,255,255);
//        if (col < maxNumberOfColorsAvailable) {
//        	color = availableColors[col];
//        }
//        CartesianChartBuilder::DataXY dataxy(vectorx, vectory);
//    	wxPen pen(color, 3, wxSOLID);
//    	vectorPen.push_back(pen);
//    	vectorName.push_back(columnsLabel[columnsNumbers[col]]);
//
//    	vecDataXY.push_back(dataxy);
//    }
//
//    /* Após a preparação dos dados, constrói o builder e insere os layers no plot*/
//	CartesianChartBuilder chartBuilder;
//	chartBuilder.SetXAxisLabel(columnsLabel[columnsNumbers[0]]);
//	chartBuilder.SetYAxisLabel("");
//	chartBuilder.SetData(vecDataXY);
//	std::vector<mpLayer*> layersAxis = chartBuilder.CreateAxisLayer();
//	vector<mpLayer*> layersData = chartBuilder.CreateDataLayers(vectorName, vectorPen);
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
//    mpInfoLegend* leg;
//    plot->AddLayer(leg = new mpInfoLegend(wxRect(200,20,40,40), wxTRANSPARENT_BRUSH));
//
//
//    plot->EnableDoubleBuffer(true);
//    plot->SetMPScrollbars(false);
//    plot->Fit();
//
//    return plot;
//}
