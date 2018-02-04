/*
 * Point3DRenderer.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef POINT3DRENDERER_H_
#define POINT3DRENDERER_H_

#include "wx/grid.h"

class Point3DRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	Point3DRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~Point3DRenderer();
};

#endif /* POINT3DRENDERER_H_ */
