/*
 * MicrostripXYPortsMERenderer.h
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#ifndef MICROSTRIPXYPORTSMERENDERER_H_
#define MICROSTRIPXYPORTSMERENDERER_H_

#include "wx/grid.h"

class MicrostripXYPortsMERenderer : public wxGridCellAutoWrapStringRenderer {
public:
	MicrostripXYPortsMERenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~MicrostripXYPortsMERenderer();
};

#endif /* MICROSTRIPXYPORTSMERENDERER_H_ */
