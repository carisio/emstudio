/*
 * SimpleTextResult.h
 *
 *  Created on: 30/09/2015
 *      Author: Leandro
 */

#ifndef EMSTUDIO_CORE_RESULTS_SIMPLETEXTRESULT_H_
#define EMSTUDIO_CORE_RESULTS_SIMPLETEXTRESULT_H_

#include "Result.h"
#include "emstudio/gui/basetypes/StringWrapper.h"

class SimpleTextResult  : public Result {
private:
	StringWrapper contents;
public:
	SimpleTextResult(wxString resultName = "", wxString contents = "");
	virtual ~SimpleTextResult();

	virtual ResultSmartPointer NewResult();
    virtual wxIcon GetIcon();
    virtual wxString GetResultClassName();
    virtual bool ExportData(wxString fileName);

    wxString GetContents();
    void SetContents(wxString contents);
};

#endif /* EMSTUDIO_CORE_RESULTS_SIMPLETEXTRESULT_H_ */
