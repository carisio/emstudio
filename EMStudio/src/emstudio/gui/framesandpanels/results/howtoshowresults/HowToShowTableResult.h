/*
 * HowToShowTableData.h
 *
 *  Created on: 13/03/2012
 *      Author: leandrocarisio
 */

#ifndef HOWTOSHOWTABLEDATA_H_
#define HOWTOSHOWTABLEDATA_H_

#include "HowToShowResults.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/core/results/TableResult.h"

#include "emstudio/util/converters/Converter.h"

#include "wx/grid.h"
#include "wx/wx.h"

#include "emstudio/util/wxmathplot/mathplot.h"
#include "emstudio/util/wxmathplot/CartesianChartBuilder.h"
#include <vector>
using namespace::std;

class HowToShowTableResult : public HowToShowResults {
public:
	HowToShowTableResult();
	virtual ~HowToShowTableResult();

	virtual int GetNumberOfTabs();
	virtual wxString GetTabName(int tabIndex);
	virtual wxWindow* GetWindow(int tabIndex, wxWindow* parent);
};

class TableBaseForGenericTable : public wxGridTableBase {
private:
	ResultSmartPointer result;
	bool showAllColumns;
	std::vector<int> columnsNumbers;
public:
	// Se showAllColumns == true, mostra todas as colunas.
	// Caso contrário, mostra apenas as columnas indicadas no vetor columnsNumbers
	TableBaseForGenericTable(ResultSmartPointer result, bool showAllColumns = true, std::vector<int> columnsNumbers = std::vector<int>());
	virtual ~TableBaseForGenericTable();

	// Métodos herdados de wxGridTableBase e usados para retirar os dados do Grid
	virtual int GetNumberRows();
	virtual int GetNumberCols();
	virtual wxString GetValue (int row, int col);
	virtual void SetValue(int row, int col, const wxString &value);
	virtual wxString GetColLabelValue(int col);
};

wxGrid* GenerateGridForGenericTable(wxWindow* parent, TableBaseForGenericTable* tableBase);
mpWindow* GeneratePlotForGenericTable(wxWindow* parent, ResultSmartPointer result, mpWindow* plot = 0, bool showAllColumns = true, std::vector<int> columnsNumbers = std::vector<int>());
mpWindow* GeneratePlotForGenericTable(wxWindow* parent, vector<CartesianChartBuilder::DataXY> vecDataXY, wxString xAxisLabel, std::vector<wxString> columnsName, mpWindow* plot, std::vector<wxColour> availableColors);

#endif /* HOWTOSHOWTABLEDATA_H_ */
