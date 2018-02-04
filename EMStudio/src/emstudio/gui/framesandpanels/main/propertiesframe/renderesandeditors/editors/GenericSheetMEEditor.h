/*
 * GenericSheetMEEditor.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETMEEDITOR_H_
#define GENERICSHEETMEEDITOR_H_

#include "emstudio/gui/basetypes/GenericSheetME.h"
#include "editorsframes/GenericSheetMEFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class GenericSheetMEEditor : public wxGridCellEditor {
private:
	GenericSheetME sheet;
public:
	GenericSheetMEEditor();
	virtual ~GenericSheetMEEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* GENERICSHEETMEEDITOR_H_ */
