/*
 * SelectFieldEditor.cpp
 *
 *  Created on: 25/04/2013
 *      Author: Leandro
 */

#include "SelectFieldEditor.h"

SelectFieldEditor::SelectFieldEditor()
	: FixedComboBoxEditor(SelectField::GetPossiblePriorities()) {

}

SelectFieldEditor::~SelectFieldEditor() {
}

FixedComboBoxEditor* SelectFieldEditor::DoClone() const {
	return new SelectFieldEditor();
}
