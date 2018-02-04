/*
 * UnitFrame.h
 *
 *  Created on: 23/09/2011
 *      Author: leandrocarisio
 */

#ifndef UNITFRAME_H_
#define UNITFRAME_H_

#include <list>
#include "wx/wx.h"
#include "wx/combobox.h"
#include "emstudio/units/Units.h"


class UnitFrame : public wxDialog {
private:
	wxComboBox* comboSpace;
	wxComboBox* comboTime;
	wxComboBox* comboFrequency;

	UnitsSmartPointer units;
	void CreateAndInsertControls();

public:
	UnitFrame(wxWindow* parent, UnitsSmartPointer u, wxWindowID id = wxID_ANY, const wxString& title = wxT("Units"));
	virtual bool TransferDataFromWindow();
	virtual ~UnitFrame();
};

#endif /* UNITFRAME_H_ */
