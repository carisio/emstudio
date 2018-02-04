/*
 * ExcitationMERenderer.h
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#ifndef EXCITATIONMERENDERER_H_
#define EXCITATIONMERENDERER_H_

#include "wx/grid.h"

class ExcitationMERenderer : public wxGridCellAutoWrapStringRenderer {
public:
	ExcitationMERenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~ExcitationMERenderer();
};

#endif /* EXCITATIONMERENDERER_H_ */
