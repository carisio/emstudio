/*
 * BoolWrapperEditor.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#ifndef BOOLWRAPPEREDITOR_H_
#define BOOLWRAPPEREDITOR_H_

#include "emstudio/gui/basetypes/BoolWrapper.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"

class BoolWrapperEditor : public wxGridCellBoolEditor {
private:
	BoolWrapper value;
public:
	BoolWrapperEditor();
	virtual ~BoolWrapperEditor();

	virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* BOOLWRAPPEREDITOR_H_ */
