/*
 * RectangularTubeGeometryMERenderer.h
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#ifndef RECTANGULARTUBEGEOMETRYMERENDERER_H_
#define RECTANGULARTUBEGEOMETRYMERENDERER_H_

#include "wx/grid.h"

class RectangularTubeGeometryMERenderer : public wxGridCellAutoWrapStringRenderer {
public:
	RectangularTubeGeometryMERenderer();
	virtual ~RectangularTubeGeometryMERenderer();
	wxGridCellRenderer* Clone() const;
};

#endif /* RECTANGULARTUBEGEOMETRYMERENDERER_H_ */
