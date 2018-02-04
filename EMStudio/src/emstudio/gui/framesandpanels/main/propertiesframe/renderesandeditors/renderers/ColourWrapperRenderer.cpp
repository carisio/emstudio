/*
 * ColourWrapperRenderer.cpp
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#include "ColourWrapperRenderer.h"

ColourWrapperRenderer::ColourWrapperRenderer() {

}

ColourWrapperRenderer::~ColourWrapperRenderer() {

}

void ColourWrapperRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected) {
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid.GetTable());
	ColourWrapper color = *(static_cast<ColourWrapper*>(table->GetValueAsBaseType(row, col)));

	wxBrush brush = wxBrush(color.GetValue());
	dc.SetBrush(brush);
	dc.DrawRectangle(rect);

//	dc.SetTextForeground(GetNegative(color.GetValue()));
//	dc.DrawLabel(color.ToString(), rect, wxALIGN_CENTER);
}

wxColour ColourWrapperRenderer::GetNegative(wxColour c) {
	char r = c.Red();
	char g = c.Green();
	char b = c.Blue();
	return wxColour(255-r, 255-g, 255-b);
}

wxGridCellRenderer* ColourWrapperRenderer::Clone() const {
	ColourWrapperRenderer* clone = new ColourWrapperRenderer;

	return clone;
}
