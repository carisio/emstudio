/*
 * SelectFieldRenderer.h
 *
 *  Created on: 25/04/2013
 *      Author: Leandro
 */

#ifndef SELECTFIELDRENDERER_H_
#define SELECTFIELDRENDERER_H_

#include "wx/grid.h"

class SelectFieldRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	SelectFieldRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~SelectFieldRenderer();
};

#endif /* SELECTFIELDRENDERER_H_ */
