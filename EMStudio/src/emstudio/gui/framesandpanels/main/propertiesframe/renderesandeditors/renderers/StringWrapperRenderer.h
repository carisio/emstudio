/*
 * StringWrapperRenderer.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#ifndef STRINGWRAPPERRENDERER_H_
#define STRINGWRAPPERRENDERER_H_

#include "wx/grid.h"

class StringWrapperRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	StringWrapperRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~StringWrapperRenderer();
};

#endif /* STRINGWRAPPERRENDERER_H_ */
