/*
 * ABCFrame.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef ABCFRAME_H_
#define ABCFRAME_H_

#include "wx/wx.h"
#include "wx/combobox.h"
#include "wx/arrstr.h"
#include "emstudio/gui/basetypes/AbsorvingBoundaryCondition.h"

class ABCFrame : public wxDialog {
private:
	AbsorvingBoundaryCondition abc;
	wxComboBox *chkNegX, *chkNegY, *chkNegZ, *chkPosX, *chkPosY, *chkPosZ;
	wxTextCtrl *txtNpml;

	/* Guarda o texto do controle selecionado */
	wxString negXCaption, negYCaption, negZCaption;
	wxString posXCaption, posYCaption, posZCaption;

	void CreateEmptyControlsAndInsert();
	void UpdateControlsState();
	void SelectABCType(wxCommandEvent& event);
	void ApplyRulesForComboBox(wxComboBox* changedComboBox, wxComboBox* theOtherComboBox, wxString& captionOfChangedComboBox);
public:
	ABCFrame(wxWindow* parent = NULL, AbsorvingBoundaryCondition e = AbsorvingBoundaryCondition(), wxWindowID id = wxID_ANY, const wxString& title = wxT("Absorving Boundary Condition"));

	virtual bool TransferDataFromWindow();
	AbsorvingBoundaryCondition GetABC();
	void SetABC(AbsorvingBoundaryCondition e);

	virtual ~ABCFrame();
};

#endif /* ABCFRAME_H_ */
