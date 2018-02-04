/*
 * Point3DMERenderer.h
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#ifndef POINT3DMERENDERER_H_
#define POINT3DMERENDERER_H_

#include "wx/grid.h"

class Point3DMERenderer : public wxGridCellAutoWrapStringRenderer {
public:
	Point3DMERenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~Point3DMERenderer();
};

#endif /* POINT3DMERENDERER_H_ */
