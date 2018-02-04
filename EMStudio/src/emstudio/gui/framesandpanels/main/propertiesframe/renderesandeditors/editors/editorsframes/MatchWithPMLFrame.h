/*
 * MatchWithPMLFrame.h
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#ifndef MATCHWITHPMLFRAME_H_
#define MATCHWITHPMLFRAME_H_

#include "wx/wx.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"
#include "wx/checkbox.h"

class MatchWithPMLFrame : public wxDialog {
private:
	MatchWithPML matchWithPML;
	wxCheckBox *chkNegX, *chkNegY, *chkNegZ, *chkPosX, *chkPosY, *chkPosZ;

	void CreateEmptyControlsAndInsert();
	void UpdateControlsState();
public:
	MatchWithPMLFrame(wxWindow* parent = NULL, MatchWithPML e = MatchWithPML(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Match with PML"));
	virtual ~MatchWithPMLFrame();

	virtual bool TransferDataFromWindow();
	MatchWithPML GetMatchWithPML();
	void SetMatchWithPML(MatchWithPML e);
};

#endif /* MATCHWITHPMLFRAME_H_ */
