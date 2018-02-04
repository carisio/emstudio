/*
 * SelectFieldEditor.h
 *
 *  Created on: 25/04/2013
 *      Author: Leandro
 */

#ifndef SELECTFIELDEDITOR_H_
#define SELECTFIELDEDITOR_H_

#include "emstudio/gui/basetypes/SelectField.h"
#include "FixedComboBoxEditor.h"

class SelectFieldEditor : public FixedComboBoxEditor {
public:
	SelectFieldEditor();
	virtual ~SelectFieldEditor();
	virtual FixedComboBoxEditor* DoClone() const;
};

#endif /* SELECTFIELDEDITOR_H_ */
