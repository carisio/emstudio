/*
 * PriorityEditor.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "PriorityEditor.h"

PriorityEditor::PriorityEditor()
	: FixedComboBoxEditor(Priority::GetPossiblePriorities()) {

}

PriorityEditor::~PriorityEditor() {

}

FixedComboBoxEditor* PriorityEditor::DoClone() const {
	return new PriorityEditor();
}
