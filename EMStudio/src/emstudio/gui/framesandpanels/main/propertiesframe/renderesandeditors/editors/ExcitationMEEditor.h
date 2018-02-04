/*
 * ExcitationMEEditor.h
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#ifndef EXCITATIONMEEDITOR_H_
#define EXCITATIONMEEDITOR_H_

#include "emstudio/gui/basetypes/ExcitationME.h"
#include "editorsframes/ExcitationMEFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

using namespace::std;

class ExcitationMEEditor : public wxGridCellEditor {
private:
	ExcitationME excitation;
public:
	ExcitationMEEditor();
	virtual ~ExcitationMEEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};
#endif /* EXCITATIONMEEDITOR_H_ */
