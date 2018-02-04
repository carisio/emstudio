/*
 * ExcitationMEFrame.h
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#ifndef EXCITATIONMEFRAME_H_
#define EXCITATIONMEFRAME_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include <vector>
#include "emstudio/util/converters/Converter.h"
#include "wx/wx.h"
#include "wx/combobox.h"
#include "wx/arrstr.h"
#include "wx/valnum.h"
#include "emstudio/gui/basetypes/ExcitationME.h"

class ExcitationMEFrame : public wxDialog {
private:
	ExcitationME excitation;
	wxComboBox *type;
	std::vector< std::pair<wxStaticText*, wxTextCtrl*> > textCtrls;
	std::vector< std::pair<wxTextCtrl*, MathParser> > parsers;

	void CreateEmptyControlsAndInsert();
	void UpdateControlsState();
	void OnSetFocusEvent(wxFocusEvent& event);
	void OnLostFocusEvent(wxFocusEvent& event);
	MathParser& GetParser(wxTextCtrl* txt);
public:
	ExcitationMEFrame(wxWindow* parent = NULL, ExcitationME e = ExcitationME(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Excitation"));

	void SelectExcitationMEType(wxCommandEvent& event);
	virtual bool TransferDataFromWindow();
	ExcitationME GetExcitationME();
	void SetExcitationME(ExcitationME e);

	virtual ~ExcitationMEFrame();
};
#endif /* EXCITATIONMEFRAME_H_ */
