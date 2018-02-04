/*
 * Point3DEditor.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef POINT3DEDITOR_H_
#define POINT3DEDITOR_H_

#include "emstudio/gui/basetypes/Point3D.h"
#include "editorsframes/Point3DFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class Point3DEditor : public wxGridCellEditor {
private:
	Point3D point;
public:
	Point3DEditor();
	virtual ~Point3DEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* POINT3DEDITOR_H_ */
