/*
 * PlaneEditor.h
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#ifndef PLANEEDITOR_H_
#define PLANEEDITOR_H_

#include "emstudio/gui/basetypes/Plane.h"
#include "FixedComboBoxEditor.h"

class PlaneEditor : public FixedComboBoxEditor {
public:
	PlaneEditor();
	virtual FixedComboBoxEditor* DoClone() const;
	virtual ~PlaneEditor();
};

#endif /* PLANEEDITOR_H_ */
