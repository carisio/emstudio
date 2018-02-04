/*
 * DirectionPlaneWaveRenderer.h
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVERENDERER_H_
#define DIRECTIONPLANEWAVERENDERER_H_

#include "wx/grid.h"

class DirectionPlaneWaveRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	DirectionPlaneWaveRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rectCell, int row, int col, bool isSelected);
	virtual ~DirectionPlaneWaveRenderer();
};

#endif /* DIRECTIONPLANEWAVERENDERER_H_ */
