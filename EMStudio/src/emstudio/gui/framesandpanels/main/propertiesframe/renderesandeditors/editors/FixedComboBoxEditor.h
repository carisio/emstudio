/*
 * FixedComboBoxEditor.h
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#ifndef FIXEDCOMBOBOXEDITOR_H_
#define FIXEDCOMBOBOXEDITOR_H_

#include "wx/grid.h"
#include "wx/arrstr.h"
#include "wx/combobox.h"

class FixedComboBoxEditor : public wxGridCellChoiceEditor {
private:
	wxArrayString options;
public:
	FixedComboBoxEditor(wxArrayString options);
	virtual wxGridCellEditor* Clone() const;
	virtual FixedComboBoxEditor* DoClone() const = 0;
	virtual ~FixedComboBoxEditor();
};

#endif /* FIXEDCOMBOBOXEDITOR_H_ */
