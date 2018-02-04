/*
 * PriorityRenderer.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef PRIORITYRENDERER_H_
#define PRIORITYRENDERER_H_

#include "wx/grid.h"

class PriorityRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	PriorityRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~PriorityRenderer();
};

#endif /* PRIORITYRENDERER_H_ */
