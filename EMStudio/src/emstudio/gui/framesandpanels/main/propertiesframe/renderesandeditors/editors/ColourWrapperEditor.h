/*
 * ColourWrapperEditor.h
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#ifndef COLOURWRAPPEREDITOR_H_
#define COLOURWRAPPEREDITOR_H_

#include "emstudio/gui/basetypes/ColourWrapper.h"
#include "../../PropertiesGridTable.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/wx.h"

class ColourWrapperEditor : public wxGridCellEditor {
private:
	ColourWrapper value;
	wxColour GetNegative(wxColour c);
	bool isEditionFinished;
public:
	ColourWrapperEditor();
	virtual ~ColourWrapperEditor();

	virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* COLOURWRAPPEREDITOR_H_ */
