/*
 * MatchWithPMLRenderer.h
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#ifndef MATCHWITHPMLRENDERER_H_
#define MATCHWITHPMLRENDERER_H_

#include "wx/grid.h"

class MatchWithPMLRenderer : public wxGridCellBoolRenderer {
public:
	MatchWithPMLRenderer();
	virtual ~MatchWithPMLRenderer();
	virtual wxGridCellRenderer* Clone() const;
};

#endif /* MATCHWITHPMLRENDERER_H_ */
