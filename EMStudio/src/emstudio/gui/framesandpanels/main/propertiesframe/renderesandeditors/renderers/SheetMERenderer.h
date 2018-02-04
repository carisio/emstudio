/*
 * SheetMERenderer.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef SHEETMERENDERER_H_
#define SHEETMERENDERER_H_

#include "wx/grid.h"

class SheetMERenderer : public wxGridCellAutoWrapStringRenderer {
public:
	SheetMERenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~SheetMERenderer();
};

#endif /* SHEETMERENDERER_H_ */
