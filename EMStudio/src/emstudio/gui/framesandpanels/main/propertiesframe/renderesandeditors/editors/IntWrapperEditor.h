/*
 * IntWrapperEditor.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#ifndef INTWRAPPEREDITOR_H_
#define INTWRAPPEREDITOR_H_

#include "emstudio/gui/basetypes/IntWrapper.h"
#include "../../PropertiesGridTable.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/grid.h"
#include "wx/wx.h"

class IntWrapperEditor : public wxGridCellTextEditor {
private:
	IntWrapper value;
public:
	IntWrapperEditor();
	virtual ~IntWrapperEditor();

	virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* INTWRAPPEREDITOR_H_ */
