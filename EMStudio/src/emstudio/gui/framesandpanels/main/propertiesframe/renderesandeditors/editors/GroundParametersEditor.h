/*
 * GroundParametersEditor.h
 *
 *  Created on: 18/03/2015
 *      Author: Leandro
 */

#ifndef SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_PROPERTIESFRAME_RENDERESANDEDITORS_EDITORS_GROUNDPARAMETERSEDITOR_H_
#define SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_PROPERTIESFRAME_RENDERESANDEDITORS_EDITORS_GROUNDPARAMETERSEDITOR_H_

#include "emstudio/gui/basetypes/GroundParameters.h"
#include "editorsframes/GroundParametersFrame.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/wx.h"

namespace mom {

class GroundParametersEditor : public wxGridCellEditor {
private:
	GroundParameters groundParameters;
public:
	GroundParametersEditor();
	virtual ~GroundParametersEditor();

    virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

} /* namespace mom */

#endif /* SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_PROPERTIESFRAME_RENDERESANDEDITORS_EDITORS_GROUNDPARAMETERSEDITOR_H_ */
