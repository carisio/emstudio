/*
 * PriorityEditor.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef PRIORITYEDITOR_H_
#define PRIORITYEDITOR_H_

#include "emstudio/gui/basetypes/Priority.h"
#include "FixedComboBoxEditor.h"

class PriorityEditor : public FixedComboBoxEditor {
public:
	PriorityEditor();
	virtual ~PriorityEditor();
	virtual FixedComboBoxEditor* DoClone() const;
};

#endif /* PRIORITYEDITOR_H_ */
