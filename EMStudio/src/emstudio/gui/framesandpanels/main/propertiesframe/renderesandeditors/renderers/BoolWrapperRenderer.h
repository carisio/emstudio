/*
 * BoolWrapperRenderer.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#ifndef BOOLWRAPPERRENDERER_H_
#define BOOLWRAPPERRENDERER_H_

#include "wx/grid.h"

class BoolWrapperRenderer : public wxGridCellBoolRenderer {
public:
	BoolWrapperRenderer();
	virtual ~BoolWrapperRenderer();
	virtual wxGridCellRenderer* Clone() const;
};

#endif /* BOOLWRAPPERRENDERER_H_ */
