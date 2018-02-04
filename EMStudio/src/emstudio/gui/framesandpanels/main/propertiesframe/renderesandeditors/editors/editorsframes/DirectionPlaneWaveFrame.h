/*
 * DirectionPlaneWaveFrame.h
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVEFRAME_H_
#define DIRECTIONPLANEWAVEFRAME_H_

#include "wx/wx.h"
#include "emstudio/gui/basetypes/DirectionPlaneWave.h"

class DirectionPlaneWaveFrame : public wxDialog {
private:
	DirectionPlaneWave direction;

	wxTextCtrl *txtTheta, *txtPhi, *txtPsi;

	void CreateEmptyControlsAndInsert();
	void UpdateControlsState();
public:
	DirectionPlaneWaveFrame(wxWindow* parent = NULL, DirectionPlaneWave d = DirectionPlaneWave(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Direction"));
	virtual ~DirectionPlaneWaveFrame();

	virtual bool TransferDataFromWindow();

	DirectionPlaneWave GetDirection();
	void SetDirection(DirectionPlaneWave d);
};

#endif /* DIRECTIONPLANEWAVEFRAME_H_ */
