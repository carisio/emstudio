/*
 * DirectionPlaneWaveMEEditor.h
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVEMEEDITOR_H_
#define DIRECTIONPLANEWAVEMEEDITOR_H_

#include "emstudio/gui/basetypes/DirectionPlaneWaveME.h"
#include "editorsframes/DirectionPlaneWaveMEFrame.h"
#include "../../PropertiesGridTable.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/grid.h"
#include "wx/wx.h"

class DirectionPlaneWaveMEEditor : public wxGridCellEditor {
private:
	DirectionPlaneWaveME direction;
public:
	DirectionPlaneWaveMEEditor();
	virtual ~DirectionPlaneWaveMEEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* DIRECTIONPLANEWAVEMEEDITOR_H_ */
