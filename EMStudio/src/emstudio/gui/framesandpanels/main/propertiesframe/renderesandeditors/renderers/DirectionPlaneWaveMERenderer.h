/*
 * DirectionPlaneWaveMERenderer.h
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVEMERENDERER_H_
#define DIRECTIONPLANEWAVEMERENDERER_H_

#include "wx/grid.h"

class DirectionPlaneWaveMERenderer : public wxGridCellAutoWrapStringRenderer {
public:
	DirectionPlaneWaveMERenderer();
	virtual ~DirectionPlaneWaveMERenderer();
	virtual void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rectCell, int row, int col, bool isSelected);
	virtual wxGridCellRenderer* Clone() const;
};

#endif /* DIRECTIONPLANEWAVEMERENDERER_H_ */
