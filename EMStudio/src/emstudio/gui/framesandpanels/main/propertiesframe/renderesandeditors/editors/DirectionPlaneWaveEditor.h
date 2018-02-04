/*
 * DirectionPlaneWaveEditor.h
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVEEDITOR_H_
#define DIRECTIONPLANEWAVEEDITOR_H_

#include "emstudio/gui/basetypes/DirectionPlaneWave.h"
#include "editorsframes/DirectionPlaneWaveFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class DirectionPlaneWaveEditor : public wxGridCellEditor {
private:
	DirectionPlaneWave direction;
public:
	DirectionPlaneWaveEditor();
	virtual ~DirectionPlaneWaveEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* DIRECTIONPLANEWAVEEDITOR_H_ */
