/*
 * FileEditor.h
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#ifndef FILEEDITOR_H_
#define FILEEDITOR_H_

#include "emstudio/gui/basetypes/File.h"
#include "../../PropertiesGridTable.h"
#include "wx/wx.h"

class FileEditor : public wxGridCellEditor {
private:
	File file;
	bool isEditionFinished;
public:
	FileEditor();
	virtual ~FileEditor();

	virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* FILEEDITOR_H_ */
