/*
 * FixedComboBoxEditor.cpp
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#include "FixedComboBoxEditor.h"

FixedComboBoxEditor::FixedComboBoxEditor(wxArrayString options)
	: wxGridCellChoiceEditor(options), options(options) {

}

FixedComboBoxEditor::~FixedComboBoxEditor() {

}

wxGridCellEditor* FixedComboBoxEditor::Clone() const {
	return DoClone();
}
