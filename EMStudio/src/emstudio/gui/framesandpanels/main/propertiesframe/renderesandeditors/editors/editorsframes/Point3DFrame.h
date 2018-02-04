/*
 * Point3DFrame.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef POINT3DFRAME_H_
#define POINT3DFRAME_H_

#include "wx/wx.h"
#include "emstudio/gui/basetypes/Point3D.h"

class Point3DFrame : public wxDialog {
private:
	Point3D point;
	wxTextCtrl *txtX, *txtY, *txtZ;

	void CreateControlsAndInsert();
	void UpdateControls();
public:
	Point3DFrame(wxWindow* parent = NULL, Point3D point = Point3D(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Point 3D"));
	virtual ~Point3DFrame();

	virtual bool TransferDataFromWindow();

	void SetPoint3D(Point3D p);
	Point3D GetPoint3D();
};

#endif /* POINT3DFRAME_H_ */
