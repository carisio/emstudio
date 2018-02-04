/*
 * GenericSheetRenderer.h
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETRENDERER_H_
#define GENERICSHEETRENDERER_H_

#include "wx/grid.h"

class GenericSheetRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	GenericSheetRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~GenericSheetRenderer();
};

#endif /* GENERICSHEETRENDERER_H_ */
