/*
 * PlaneEditor.cpp
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#include "PlaneEditor.h"

PlaneEditor::PlaneEditor()
	: FixedComboBoxEditor(Plane::GetPossibleOrientations()) {

}

PlaneEditor::~PlaneEditor() {

}

FixedComboBoxEditor* PlaneEditor::DoClone() const {
	return new PlaneEditor();
}
