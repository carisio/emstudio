/*
 * ABCRenderer.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef ABCRENDERER_H_
#define ABCRENDERER_H_

#include "wx/grid.h"

class ABCRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	ABCRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~ABCRenderer();
};

#endif /* ABCRENDERER_H_ */
