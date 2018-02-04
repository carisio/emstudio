/*
 * MaterialRenderer.h
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#ifndef MATERIALRENDERER_H_
#define MATERIALRENDERER_H_

#include "wx/grid.h"

class MaterialRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	MaterialRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~MaterialRenderer();
};

#endif /* MATERIALRENDERER_H_ */
