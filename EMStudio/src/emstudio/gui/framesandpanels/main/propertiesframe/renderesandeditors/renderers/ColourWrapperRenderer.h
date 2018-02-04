/*
 * ColourWrapperRenderer.h
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#ifndef COLOURWRAPPERRENDERER_H_
#define COLOURWRAPPERRENDERER_H_

#include "wx/wx.h"
#include "wx/grid.h"
#include "../../PropertiesGridTable.h"
#include "emstudio/gui/basetypes/ColourWrapper.h"

class ColourWrapperRenderer : public wxGridCellStringRenderer {
public:
	ColourWrapperRenderer();
	virtual ~ColourWrapperRenderer();
	virtual void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected);
	wxColour GetNegative(wxColour c);
	virtual wxGridCellRenderer* Clone() const;
};

#endif /* COLOURWRAPPERRENDERER_H_ */
