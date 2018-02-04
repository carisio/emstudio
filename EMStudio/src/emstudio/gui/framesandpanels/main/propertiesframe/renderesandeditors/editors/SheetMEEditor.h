/*
 * SheetMEEditor.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef SHEETMEEDITOR_H_
#define SHEETMEEDITOR_H_

#include "emstudio/gui/basetypes/SheetME.h"
#include "editorsframes/SheetMEFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"


class SheetMEEditor : public wxGridCellEditor {
private:
	SheetME sheet;
public:
	SheetMEEditor();
	virtual ~SheetMEEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* SHEETMEEDITOR_H_ */
