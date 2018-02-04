/*
 * SheetRenderer.h
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#ifndef SHEETRENDERER_H_
#define SHEETRENDERER_H_

#include "wx/grid.h"

class SheetRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	SheetRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~SheetRenderer();
};

#endif /* SHEETRENDERER_H_ */
