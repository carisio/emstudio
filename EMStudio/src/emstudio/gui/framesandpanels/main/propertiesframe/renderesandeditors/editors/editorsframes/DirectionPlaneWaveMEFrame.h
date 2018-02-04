/*
 * DirectionPlaneWaveMEFrame.h
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVEMEFRAME_H_
#define DIRECTIONPLANEWAVEMEFRAME_H_

#include "wx/wx.h"
#include "emstudio/gui/basetypes/DirectionPlaneWaveME.h"

class DirectionPlaneWaveMEFrame : public wxDialog {
private:
	DirectionPlaneWaveME direction;

	wxTextCtrl *txtTheta, *txtPhi, *txtPsi;

	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	void CreateEmptyControlsAndInsert();
	void UpdateControlsState();
public:
	DirectionPlaneWaveMEFrame(wxWindow* parent = NULL, DirectionPlaneWaveME d = DirectionPlaneWaveME(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Direction"));
	virtual ~DirectionPlaneWaveMEFrame();

	virtual bool TransferDataFromWindow();

	DirectionPlaneWaveME GetDirection();
	void SetDirection(DirectionPlaneWaveME d);
};

#endif /* DIRECTIONPLANEWAVEMEFRAME_H_ */
