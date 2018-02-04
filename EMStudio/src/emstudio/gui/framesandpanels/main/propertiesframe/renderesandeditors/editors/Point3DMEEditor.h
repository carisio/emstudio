/*
 * Point3DMEEditor.h
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#ifndef POINT3DMEEDITOR_H_
#define POINT3DMEEDITOR_H_

#include "emstudio/gui/basetypes/Point3DME.h"
#include "editorsframes/Point3DMEFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class Point3DMEEditor : public wxGridCellEditor {
private:
	Point3DME point;
public:
	Point3DMEEditor();
	virtual ~Point3DMEEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* POINT3DMEEDITOR_H_ */
