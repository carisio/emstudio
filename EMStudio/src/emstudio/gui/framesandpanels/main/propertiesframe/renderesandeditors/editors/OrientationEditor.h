/*
 * OrientationEditor.h
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#ifndef ORIENTATIONEDITOR_H_
#define ORIENTATIONEDITOR_H_

#include "emstudio/gui/basetypes/Orientation.h"
#include "FixedComboBoxEditor.h"

class OrientationEditor : public FixedComboBoxEditor {
public:
	OrientationEditor();
	virtual ~OrientationEditor();
	virtual FixedComboBoxEditor* DoClone() const;
};

#endif /* ORIENTATIONEDITOR_H_ */
