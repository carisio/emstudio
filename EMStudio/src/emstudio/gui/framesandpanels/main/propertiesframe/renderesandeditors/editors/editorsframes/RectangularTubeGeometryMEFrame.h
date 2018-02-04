/*
 * RectangularTubeGeometryMEFrame.h
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#ifndef RECTANGULARTUBEGEOMETRYMEFRAME_H_
#define RECTANGULARTUBEGEOMETRYMEFRAME_H_

#include "emstudio/gui/basetypes/RectangularTubeGeometryME.h"
#include "wx/wx.h"
#include "wx/combobox.h"
#include "wx/arrstr.h"

class RectangularTubeGeometryMEFrame : public wxDialog {
private:
	RectangularTubeGeometryME geometry;

	wxComboBox *cboOrientation;
	// BASE //
	wxStaticText *lblBaseCutAt;
	wxStaticText *lblBaseCoord1Begin, *lblBaseCoord1End, *lblBaseCoord1Thickness;
	wxStaticText *lblBaseCoord2Begin, *lblBaseCoord2End, *lblBaseCoord2Thickness;
	wxTextCtrl *txtBaseCutAt;
	wxTextCtrl *txtBaseCoord1Begin, *txtBaseCoord1End, *txtBaseCoord1Thickness;
	wxTextCtrl *txtBaseCoord2Begin, *txtBaseCoord2End, *txtBaseCoord2Thickness;

	// BASE //
	wxStaticText *lblTopCutAt;
	wxStaticText *lblTopCoord1Begin, *lblTopCoord1End, *lblTopCoord1Thickness;
	wxStaticText *lblTopCoord2Begin, *lblTopCoord2End, *lblTopCoord2Thickness;
	wxTextCtrl *txtTopCutAt;
	wxTextCtrl *txtTopCoord1Begin, *txtTopCoord1End, *txtTopCoord1Thickness;
	wxTextCtrl *txtTopCoord2Begin, *txtTopCoord2End, *txtTopCoord2Thickness;

	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	void CreateControlsAndInsert();
	void UpdateControlsWithGeometryInformation();
	void ChangeLabels();

	void UserChangedOrientation(wxCommandEvent& event);

	wxArrayString GetAvailableOrientation();
	wxString GetSelectedOrientation();
public:
	RectangularTubeGeometryMEFrame(wxWindow* parent = NULL, RectangularTubeGeometryME sheet = RectangularTubeGeometryME(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Geometry"));
	virtual ~RectangularTubeGeometryMEFrame();

	virtual bool TransferDataFromWindow();

	void SetRectangularTubeGeometryME(RectangularTubeGeometryME g);
	RectangularTubeGeometryME GetRectangularTubeGeometryME();
};

#endif /* RECTANGULARTUBEGEOMETRYMEFRAME_H_ */
