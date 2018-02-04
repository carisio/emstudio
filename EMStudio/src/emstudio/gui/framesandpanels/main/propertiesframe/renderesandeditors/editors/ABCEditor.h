/*
 * ABCEditor.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef ABCEDITOR_H_
#define ABCEDITOR_H_

#include "emstudio/gui/basetypes/AbsorvingBoundaryCondition.h"
#include "editorsframes/ABCFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class ABCEditor : public wxGridCellEditor {
private:
	AbsorvingBoundaryCondition abc;
public:
	ABCEditor();
	virtual ~ABCEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* ABCEDITOR_H_ */
