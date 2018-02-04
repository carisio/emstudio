/*
 * GroundParametersFrame.h
 *
 *  Created on: 18/03/2015
 *      Author: Leandro
 */

#ifndef SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_PROPERTIESFRAME_RENDERESANDEDITORS_EDITORS_EDITORSFRAMES_GROUNDPARAMETERSFRAME_H_
#define SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_PROPERTIESFRAME_RENDERESANDEDITORS_EDITORS_EDITORSFRAMES_GROUNDPARAMETERSFRAME_H_

#include "emstudio/gui/basetypes/GroundParameters.h"
#include "wx/wx.h"
#include "wx/listbox.h"
#include "wx/arrstr.h"
#include "wx/combobox.h"

namespace mom {

class GroundParametersFrame : public wxDialog {
private:
	GroundParameters gp;
	wxComboBox *cboMedium1, *cboCurrentOnSegmentsTouchingGround, *cboMedium2, *cboCliffType;
	wxCheckBox *chkGround2Exists;
	wxTextCtrl *txtDistanceBelowGround, *txtDistanceFromOrigin, *txtNumberOfWires, *txtWireLength, *txtWireRadius;
	MathParser distanceBelowGroundParser;
	MathParser distanceFromOriginParser;
	MathParser numberOfWiresParser;
	MathParser wireLengthParser;
	MathParser wireRadiusParser;

	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	void GroundCommandEvent(wxCommandEvent& event);
	void CreateControlsAndInsert();
	void UpdateControlsWithGroundParametersInformation();

	wxArrayString GetCliffTypes();
	wxArrayString GetCurrentsExpansionTypes();
public:
	GroundParametersFrame(wxWindow* parent = NULL, GroundParameters g = GroundParameters(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Ground parameters"));
	virtual ~GroundParametersFrame();

	virtual bool TransferDataFromWindow();

	void SetGroundParameters(GroundParameters g);
	GroundParameters GetGroundParameters();
};

} /* namespace mom */

#endif /* SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_PROPERTIESFRAME_RENDERESANDEDITORS_EDITORS_EDITORSFRAMES_GROUNDPARAMETERSFRAME_H_ */
