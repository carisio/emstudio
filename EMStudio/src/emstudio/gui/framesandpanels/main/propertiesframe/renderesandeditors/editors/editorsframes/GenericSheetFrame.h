/*
 * GenericSheetFrame.h
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETFRAME_H_
#define GENERICSHEETFRAME_H_

#include "wx/wx.h"
#include "wx/combobox.h"
#include "wx/listbox.h"
#include "emstudio/gui/basetypes/GenericSheet.h"
#include "wx/arrstr.h"
#include "emstudio/util/wxmathplot/mathplot.h"

class GenericSheetFrame : public wxDialog {
private:
	GenericSheet sheet;
	wxComboBox *plane;
	wxStaticText *lblCutAt, *lblPoint;
	wxTextCtrl *cutAt, *point1, *point2;
	wxListBox *pointList;
	wxButton *addPoint, *changePoint, *up, *down, *del, *delAll;
//	wxPanel *drawPolygon;
	mpWindow* plotSketch;

	void CreateControlsAndInsert();
	void UpdateControlsWithSheetInformation();
	void ChangeLabels();

	wxArrayString GetAvailableCuts();
	wxString GetSelectedCut();

	void RebuildCoordinateList();
	wxArrayString GetSheetCoordinates();
	void DrawPolygon();

	void MoveCoordinateUp(wxCommandEvent& event);
	void MoveCoordinateDown(wxCommandEvent& event);
	void DeleteCoordinate(wxCommandEvent& event);
	void DeleteAllCoordinates(wxCommandEvent& event);
	void AddPoint(wxCommandEvent& event);
	void ChangePoint(wxCommandEvent& event);

public:
	GenericSheetFrame(wxWindow* parent = NULL, GenericSheet sheet = GenericSheet(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Generic Sheet"));
	virtual ~GenericSheetFrame();

	void UserChangedSelectedPlane(wxCommandEvent& event);
	virtual bool TransferDataFromWindow();

	void SetGenericSheet(GenericSheet s);
	GenericSheet GetGenericSheet();
};

#endif /* GENERICSHEETFRAME_H_ */
