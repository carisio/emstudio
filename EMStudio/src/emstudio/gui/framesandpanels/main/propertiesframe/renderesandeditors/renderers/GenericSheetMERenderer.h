/*
 * GenericSheetMERenderer.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETMERENDERER_H_
#define GENERICSHEETMERENDERER_H_

#include "wx/grid.h"

class GenericSheetMERenderer : public wxGridCellAutoWrapStringRenderer {
public:
	GenericSheetMERenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~GenericSheetMERenderer();
};

#endif /* GENERICSHEETMERENDERER_H_ */
