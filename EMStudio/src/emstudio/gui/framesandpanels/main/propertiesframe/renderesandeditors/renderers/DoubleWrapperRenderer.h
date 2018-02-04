/*
 * DoubleWrapperRenderer.h
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#ifndef DOUBLEWRAPPERRENDERER_H_
#define DOUBLEWRAPPERRENDERER_H_

#include "wx/grid.h"
class DoubleWrapperRenderer : public wxGridCellFloatRenderer {
public:
	DoubleWrapperRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~DoubleWrapperRenderer();
};

#endif /* DOUBLEWRAPPERRENDERER_H_ */
