/*
 * SheetFrame.h
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#ifndef SHEETFRAME_H_
#define SHEETFRAME_H_

#include "wx/wx.h"
#include "wx/combobox.h"
#include "emstudio/gui/basetypes/Sheet.h"
#include "wx/arrstr.h"

class SheetFrame : public wxDialog {
private:
	Sheet sheet;
	wxComboBox *plane;
	wxStaticText *lblCutAt, *lbli0, *lbli1, *lblj0, *lblj1;
	wxTextCtrl *cutAt, *i0, *i1, *j0, *j1;

	void CreateControlsAndInsert();
	void UpdateControlsWithSheetInformation();
	void ChangeLabels();

	wxArrayString GetAvailableCuts();
	wxString GetSelectedCut();
public:
	SheetFrame(wxWindow* parent = NULL, Sheet sheet = Sheet(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Sheet"));
	virtual ~SheetFrame();

	void UserChangedSelectedPlane(wxCommandEvent& event);
	virtual bool TransferDataFromWindow();

	void SetSheet(Sheet s);
	Sheet GetSheet();
};

#endif /* SHEETFRAME_H_ */
