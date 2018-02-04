/*
 * TableResult.h
 *
 *  Created on: 13/03/2012
 *      Author: leandrocarisio
 */

#ifndef TABLERESULT_H_
#define TABLERESULT_H_

#include "Result.h"
#include "emstudio/gui/basetypes/StringWrapper.h"
#include "emstudio/gui/basetypes/BoolWrapper.h"
#include "emstudio/gui/basetypes/GenericTable.h"

#include <list>
using namespace::std;

class TableResult : public Result {
private:
	GenericTable data;
	BoolWrapper canBeInterpretedAsChart;
//	StringWrapper title;
public:
	TableResult(wxString title = "", GenericTable data = GenericTable(), BoolWrapper canBeInterpretedAsChart = BoolWrapper());

	virtual ResultSmartPointer NewResult();
    virtual wxIcon GetIcon();
    virtual wxString GetResultClassName();
    virtual bool ExportData(wxString fileName);
    virtual wxString GetDataFileContents();
    virtual wxString GetInfoFileContents();
    virtual wxString GetMatlabFileContents(wxString dataFileName);

    wxString GetTitle();
    void SetTitle(wxString title);
    GenericTable& GetData();
    void SetData(GenericTable& table);
    void SetCanBeInterpretedAsChart(bool b);
    bool CanBeInterpretedAsChart();

    std::vector<wxColour> GetAvailableColors();

	virtual ~TableResult();
};

#endif /* TABLERESULT_H_ */
