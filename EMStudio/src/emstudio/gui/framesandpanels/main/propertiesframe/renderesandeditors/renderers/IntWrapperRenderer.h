/*
 * IntWrapperRenderer.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#ifndef INTWRAPPERRENDERER_H_
#define INTWRAPPERRENDERER_H_

#include "wx/grid.h"

class IntWrapperRenderer : public wxGridCellNumberRenderer {
public:
	IntWrapperRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~IntWrapperRenderer();
};

#endif /* INTWRAPPERRENDERER_H_ */
