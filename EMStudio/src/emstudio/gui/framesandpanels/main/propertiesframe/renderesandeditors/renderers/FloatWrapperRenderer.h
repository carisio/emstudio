/*
 * FloatWrapperRenderer.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#ifndef FLOATWRAPPERRENDERER_H_
#define FLOATWRAPPERRENDERER_H_

#include "wx/grid.h"

class FloatWrapperRenderer  : public wxGridCellFloatRenderer {
public:
	FloatWrapperRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~FloatWrapperRenderer();
};

#endif /* FLOATWRAPPERRENDERER_H_ */
