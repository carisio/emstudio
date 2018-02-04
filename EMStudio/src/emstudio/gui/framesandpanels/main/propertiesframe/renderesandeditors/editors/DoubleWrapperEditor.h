/*
 * DoubleWrapperEditor.h
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#ifndef DOUBLEWRAPPEREDITOR_H_
#define DOUBLEWRAPPEREDITOR_H_

#include "emstudio/gui/basetypes/DoubleWrapper.h"
#include "../../PropertiesGridTable.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/grid.h"
#include "wx/wx.h"

/*
 * A classe foi escrita para herdar de wxGridCellEditor. Mas como apresenta alguns problemas no posicionamento da
 * caixa texto, a classe será herdada de wxGridCellTextEditor. Isso é necessário pois o método wxGridCellTextEditor::SetSize
 * corrige esses problemas de posicionamento.
 **/
class DoubleWrapperEditor : public wxGridCellTextEditor {
private:
	DoubleWrapper value;
public:
	DoubleWrapperEditor();
	virtual ~DoubleWrapperEditor();

	virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
	virtual void Reset();
	virtual wxString GetValue() const;
};

#endif /* DOUBLEWRAPPEREDITOR_H_ */
