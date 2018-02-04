/*
 * Point3DMEFrame.h
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#ifndef POINT3DMEFRAME_H_
#define POINT3DMEFRAME_H_

#include "emstudio/gui/basetypes/Point3DME.h"
#include "wx/wx.h"

class Point3DMEFrame : public wxDialog {
private:
	Point3DME point;
	wxTextCtrl *txtX, *txtY, *txtZ;

	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	void CreateControlsAndInsert();
	void UpdateControls();
public:
	Point3DMEFrame(wxWindow* parent = NULL, Point3DME point = Point3DME(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Edit"));
	virtual ~Point3DMEFrame();

	virtual bool TransferDataFromWindow();

	void SetPoint3DME(Point3DME p);
	Point3DME GetPoint3DME();
};

#endif /* POINT3DMEFRAME_H_ */
