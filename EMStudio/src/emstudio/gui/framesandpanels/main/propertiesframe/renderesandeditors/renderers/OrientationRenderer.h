/*
 * OrientationRenderer.h
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#ifndef ORIENTATIONRENDERER_H_
#define ORIENTATIONRENDERER_H_

#include "wx/grid.h"

class OrientationRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	OrientationRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~OrientationRenderer();
};

#endif /* ORIENTATIONRENDERER_H_ */
