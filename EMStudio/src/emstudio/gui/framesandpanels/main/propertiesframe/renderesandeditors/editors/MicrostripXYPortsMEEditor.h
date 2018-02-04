/*
 * MicrostripXYPortMEEditor.h
 *
 *  Created on: 06/12/2013
 *      Author: leandrocarisio
 */

#ifndef MICROSTRIPXYPORTMEEDITOR_H_
#define MICROSTRIPXYPORTMEEDITOR_H_

#include "emstudio/gui/basetypes/MicrostripXYPortsME.h"
#include "editorsframes/MicrostripXYPortsMEFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class MicrostripXYPortsMEEditor : public wxGridCellEditor {
private:
	MicrostripXYPortsME ports;
public:
	MicrostripXYPortsMEEditor();
	virtual ~MicrostripXYPortsMEEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* MICROSTRIPXYPORTMEEDITOR_H_ */
