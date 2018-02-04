/*
 * MatchWithPMLEditor.h
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#ifndef MATCHWITHPMLEDITOR_H_
#define MATCHWITHPMLEDITOR_H_

#include "emstudio/gui/basetypes/MatchWithPML.h"
#include "editorsframes/MatchWithPMLFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

class MatchWithPMLEditor : public wxGridCellEditor {
private:
	MatchWithPML matchWithPML;
public:
	MatchWithPMLEditor();
	virtual ~MatchWithPMLEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* MATCHWITHPMLEDITOR_H_ */
