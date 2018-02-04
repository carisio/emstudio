/*
 * PlaneRenderer.h
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#ifndef PLANERENDERER_H_
#define PLANERENDERER_H_

#include "wx/grid.h"

class PlaneRenderer  : public wxGridCellAutoWrapStringRenderer {
public:
	PlaneRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~PlaneRenderer();
};

#endif /* PLANERENDERER_H_ */
