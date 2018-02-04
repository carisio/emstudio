/*
 * DXFFileEditor.h
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#ifndef DXFFILEEDITOR_H_
#define DXFFILEEDITOR_H_

#include "emstudio/gui/basetypes/DXFFile.h"
#include "../../PropertiesGridTable.h"
#include "wx/wx.h"

class DXFFileEditor : public wxGridCellEditor {
private:
	DXFFile file;
	bool isEditionFinished;
public:
	DXFFileEditor();
	virtual ~DXFFileEditor();

	virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* DXFFILEEDITOR_H_ */
