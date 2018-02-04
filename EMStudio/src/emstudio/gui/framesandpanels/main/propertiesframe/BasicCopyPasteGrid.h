/*
 * BasicCopyPasteGrid.h
 *
 *  Created on: 10/02/2012
 *      Author: leandrocarisio
 */

#ifndef BASICCOPYPASTEGRID_H_
#define BASICCOPYPASTEGRID_H_

#include "wx/wx.h"
#include "wx/grid.h"
#include "wx/clipbrd.h"

class BasicCopyPasteGrid : public wxGrid {
private:
	bool showPasteInPopup;

	void Copy();
	void Paste();

	void Copy(wxCommandEvent& event);
	void Paste(wxCommandEvent& event);
	void OnRightMouseDown(wxGridEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	int GetRows() { return GetTable()->GetRowsCount(); }
	int GetCols() { return GetTable()->GetColsCount(); }
public:
	BasicCopyPasteGrid(wxWindow *parent, wxWindowID id = wxID_ANY, bool showPasteInPopup = true, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	virtual ~BasicCopyPasteGrid();

private:
       DECLARE_EVENT_TABLE()
};

#endif /* BASICCOPYPASTEGRID_H_ */
