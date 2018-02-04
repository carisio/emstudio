/*
 * DirectionPlaneWaveMERenderer.cpp
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWaveMERenderer.h"

DirectionPlaneWaveMERenderer::DirectionPlaneWaveMERenderer() {

}

DirectionPlaneWaveMERenderer::~DirectionPlaneWaveMERenderer() {
}
void DirectionPlaneWaveMERenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rectCell, int row, int col, bool isSelected) {
	wxFont previousFont = attr.GetFont();
	int size = previousFont.GetPointSize();
	wxFont font(size, wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL, false, "Symbol"/*, wxFONTENCODING_ISO8859_1*/);
	attr.SetFont(font);
	wxGridCellAutoWrapStringRenderer::Draw(grid,attr,dc,rectCell,row,col,isSelected);
	attr.SetFont(previousFont);
}
wxGridCellRenderer* DirectionPlaneWaveMERenderer::Clone() const {
	return new DirectionPlaneWaveMERenderer;
}
