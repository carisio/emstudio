/*
 * GenericSheetEditor.h
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETEDITOR_H_
#define GENERICSHEETEDITOR_H_

#include "emstudio/gui/basetypes/GenericSheet.h"
#include "editorsframes/GenericSheetFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class GenericSheetEditor : public wxGridCellEditor {
private:
	GenericSheet sheet;
public:
	GenericSheetEditor();
	virtual ~GenericSheetEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* GENERICSHEETEDITOR_H_ */
