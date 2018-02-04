/*
 * RectangularTubeGeometryMEEditor.h
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#ifndef RECTANGULARTUBEGEOMETRYMEEDITOR_H_
#define RECTANGULARTUBEGEOMETRYMEEDITOR_H_

#include "emstudio/gui/basetypes/RectangularTubeGeometryME.h"
#include "editorsframes/RectangularTubeGeometryMEFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class RectangularTubeGeometryMEEditor : public wxGridCellEditor {
private:
	RectangularTubeGeometryME geometry;

public:
	RectangularTubeGeometryMEEditor();
	virtual ~RectangularTubeGeometryMEEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* RECTANGULARTUBEGEOMETRYMEEDITOR_H_ */
