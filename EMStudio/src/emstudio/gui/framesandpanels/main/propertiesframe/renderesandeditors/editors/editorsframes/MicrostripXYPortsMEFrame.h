/*
 * MicrostripXYPortsMEFrame.h
 *
 *  Created on: 06/12/2013
 *      Author: leandrocarisio
 */

#ifndef MICROSTRIPXYPORTSMEFRAME_H_
#define MICROSTRIPXYPORTSMEFRAME_H_

#include "emstudio/gui/basetypes/MicrostripXYPortsME.h"
#include "wx/wx.h"
#include "wx/listbox.h"
#include "wx/arrstr.h"

class MicrostripXYPortsMEFrame : public wxDialog {
private:
	MicrostripXYPortsME ports;
	wxTextCtrl *xCoor, *yCoor;
	MathParser xParser, yParser;
	wxListBox *pointList;
	wxButton *addPoint, *changePoint, *up, *down, *del, *delAll;

	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	void CreateControlsAndInsert();
	void UpdateControlsWithPortsInformation();

	void RebuildCoordinateList(int selectedIndex = wxNOT_FOUND);
	wxArrayString GetPortsCoordinates();

	void CoordinateSelected(wxCommandEvent& event);
	void MoveCoordinateUp(wxCommandEvent& event);
	void MoveCoordinateDown(wxCommandEvent& event);
	void DeleteCoordinate(wxCommandEvent& event);
	void DeleteAllCoordinates(wxCommandEvent& event);
	void AddPoint(wxCommandEvent& event);
	void ChangePoint(wxCommandEvent& event);
public:
	MicrostripXYPortsMEFrame(wxWindow* parent = NULL, MicrostripXYPortsME ports = MicrostripXYPortsME(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Ports"));
	virtual ~MicrostripXYPortsMEFrame();

	virtual bool TransferDataFromWindow();

	void SetMicrostripXYPortsME(MicrostripXYPortsME m);
	MicrostripXYPortsME GetMicrostripXYPortsME();
};

#endif /* MICROSTRIPXYPORTSMEFRAME_H_ */
