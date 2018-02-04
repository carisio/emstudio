/*
 * LongWrapperRenderer.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#ifndef LONGWRAPPERRENDERER_H_
#define LONGWRAPPERRENDERER_H_

#include "wx/grid.h"

class LongWrapperRenderer : public wxGridCellNumberRenderer {
public:
	virtual wxGridCellRenderer* Clone() const;
	LongWrapperRenderer();
	virtual ~LongWrapperRenderer();
};

#endif /* LONGWRAPPERRENDERER_H_ */
