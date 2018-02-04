/*
 * DirectionPlaneWaveRenderer.cpp
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWaveRenderer.h"

DirectionPlaneWaveRenderer::DirectionPlaneWaveRenderer() {

}

DirectionPlaneWaveRenderer::~DirectionPlaneWaveRenderer() {
}
void DirectionPlaneWaveRenderer::Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rectCell, int row, int col, bool isSelected) {
	wxFont previousFont = attr.GetFont();
	int size = previousFont.GetPointSize();
	wxFont font(size, wxFONTFAMILY_ROMAN, wxNORMAL, wxNORMAL, false, "Symbol"/*, wxFONTENCODING_ISO8859_1*/);
	attr.SetFont(font);
	wxGridCellAutoWrapStringRenderer::Draw(grid,attr,dc,rectCell,row,col,isSelected);
	attr.SetFont(previousFont);
}
wxGridCellRenderer* DirectionPlaneWaveRenderer::Clone() const {
	return new DirectionPlaneWaveRenderer;
}
