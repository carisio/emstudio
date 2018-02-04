/*
 * SheetEditor.h
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#ifndef SHEETEDITOR_H_
#define SHEETEDITOR_H_

#include "emstudio/gui/basetypes/Sheet.h"
#include "editorsframes/SheetFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class SheetEditor : public wxGridCellEditor {
private:
	Sheet sheet;
public:
	SheetEditor();
	virtual ~SheetEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* SHEETEDITOR_H_ */
