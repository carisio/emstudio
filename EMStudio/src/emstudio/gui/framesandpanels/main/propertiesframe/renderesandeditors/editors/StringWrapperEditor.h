/*
 * StringWrapperEditor.h
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "wx/grid.h"

#ifndef STRINGWRAPPEREDITOR_H_
#define STRINGWRAPPEREDITOR_H_

class StringWrapperEditor : public wxGridCellTextEditor {
public:
	StringWrapperEditor();
	virtual ~StringWrapperEditor();
};

#endif /* STRINGWRAPPEREDITOR_H_ */
