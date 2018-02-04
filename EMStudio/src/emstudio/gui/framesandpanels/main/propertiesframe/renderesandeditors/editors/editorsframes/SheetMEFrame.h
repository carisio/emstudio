/*
 * SheetMEFrame.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef SHEETMEFRAME_H_
#define SHEETMEFRAME_H_

#include "emstudio/gui/basetypes/SheetME.h"
#include "wx/wx.h"
#include "wx/combobox.h"
#include "wx/arrstr.h"

class SheetMEFrame : public wxDialog {
private:
	SheetME sheet;
	wxComboBox *plane;
	wxStaticText *lblCutAt, *lbli0, *lbli1, *lblj0, *lblj1;
	wxTextCtrl *cutAt, *i0, *i1, *j0, *j1;
	MathParser cutAtParser, i0Parser, i1Parser, j0Parser, j1Parser;

	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	void CreateControlsAndInsert();
	void UpdateControlsWithSheetInformation();
	void ChangeLabels();

	wxArrayString GetAvailableCuts();
	wxString GetSelectedCut();
public:
	SheetMEFrame(wxWindow* parent = NULL, SheetME sheet = SheetME(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Sheet"));
	virtual ~SheetMEFrame();

	void UserChangedSelectedPlane(wxCommandEvent& event);
	virtual bool TransferDataFromWindow();

	void SetSheetME(SheetME s);
	SheetME GetSheetME();

};

#endif /* SHEETMEFRAME_H_ */
