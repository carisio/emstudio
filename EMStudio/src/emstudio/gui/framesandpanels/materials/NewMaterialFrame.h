/*
 * NewMaterialFrame.h
 *
 *  Created on: 23/09/2011
 *      Author: leandrocarisio
 */

#ifndef NEWMATERIALFRAME_H_
#define NEWMATERIALFRAME_H_

#include <list>
#include "wx/wx.h"
#include "wx/combobox.h"
#include "wx/arrstr.h"
#include "wx/valnum.h"
#include "emstudio/gui/basetypes/Material.h"

class NewMaterialFrame : public wxDialog {
private:
	Material material;
	wxTextCtrl *description;
	wxComboBox *type;
	wxTextCtrl *ex, *ey, *ez;
	wxTextCtrl *ux, *uy, *uz;
	wxTextCtrl *sx, *sy, *sz;
	wxTextCtrl *rho;
	wxStaticText *textex, *textey, *textez;
	wxStaticText *textux, *textuy, *textuz;
	wxStaticText *textsx, *textsy, *textsz;
	wxStaticText *textrho;
	wxButton *color;

	void CreateAndInsertControls();
	wxString GetType();
	wxArrayString GetAvailableTypes();
	void ChangeState();
	void ChangeColor(wxCommandEvent& event);
public:
	NewMaterialFrame(wxWindow* parent, Material m = Material(), wxWindowID id = wxID_ANY, const wxString& title = wxT("New Material"));
	void SelectMaterialType(wxCommandEvent& event);
	Material GetMaterial();
	virtual bool TransferDataFromWindow();
	virtual ~NewMaterialFrame();
};

#endif /* NEWMATERIALFRAME_H_ */
