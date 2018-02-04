/*
 * GenericSheetMEFrame.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETMEFRAME_H_
#define GENERICSHEETMEFRAME_H_

#include "emstudio/gui/basetypes/GenericSheetME.h"
#include "wx/wx.h"
#include "wx/combobox.h"
#include "wx/listbox.h"
#include "wx/arrstr.h"
#include "emstudio/util/wxmathplot/mathplot.h"

class GenericSheetMEFrame : public wxDialog {
private:
	GenericSheetME sheet;
	wxComboBox *plane;
	wxStaticText *lblCutAt, *lblPoint;
	wxTextCtrl *cutAt, *point1, *point2;
	MathParser cutAtParser, point1Parser, point2Parser;
	wxListBox *pointList;
	wxButton *addPoint, *changePoint, *up, *down, *del, *delAll;
//	wxPanel *drawPolygon;
	mpWindow* plotSketch;

	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	void CreateControlsAndInsert();
	void UpdateControlsWithSheetInformation();
	void ChangeLabels();

	wxArrayString GetAvailableCuts();
	wxString GetSelectedCut();

	void RebuildCoordinateList(int selectedIndex = wxNOT_FOUND);
	wxArrayString GetSheetCoordinates();
	void DrawPolygon();

	void CoordinateSelected(wxCommandEvent& event);
	void MoveCoordinateUp(wxCommandEvent& event);
	void MoveCoordinateDown(wxCommandEvent& event);
	void DeleteCoordinate(wxCommandEvent& event);
	void DeleteAllCoordinates(wxCommandEvent& event);
	void AddPoint(wxCommandEvent& event);
	void ChangePoint(wxCommandEvent& event);
public:
	GenericSheetMEFrame(wxWindow* parent = NULL, GenericSheetME sheet = GenericSheetME(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Generic Sheet"));
	virtual ~GenericSheetMEFrame();

	void UserChangedSelectedPlane(wxCommandEvent& event);
	virtual bool TransferDataFromWindow();

	void SetGenericSheetME(GenericSheetME s);
	GenericSheetME GetGenericSheetME();
};

#endif /* GENERICSHEETMEFRAME_H_ */
