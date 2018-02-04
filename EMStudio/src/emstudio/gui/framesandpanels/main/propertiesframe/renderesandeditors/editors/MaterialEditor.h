/*
 * MaterialEditor.h
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#ifndef MATERIALEDITOR_H_
#define MATERIALEDITOR_H_

#include "emstudio/gui/basetypes/Material.h"
#include "emstudio/gui/basetypes/MaterialLibrary.h"
#include "../../PropertiesGridTable.h"
#include "wx/grid.h"
#include "wx/arrstr.h"
#include "wx/combobox.h"

class MaterialEditor : public wxGridCellChoiceEditor {
private:
	MaterialLibrarySmartPointer library;
//	Material value;
public:
	MaterialEditor(MaterialLibrarySmartPointer library);
	virtual ~MaterialEditor();

	virtual void BeginEdit (int row, int col, wxGrid *grid);
	virtual wxGridCellEditor* Clone() const;
//	virtual bool EndEdit(int row, int col, const wxGrid *grid, const wxString &oldval, wxString *newval);
	virtual void ApplyEdit(int row, int col, wxGrid *grid);
//	virtual void Create(wxWindow *parent, wxWindowID id, wxEvtHandler *evtHandler);
//	virtual void Reset();
//	virtual wxString GetValue() const;
};

//class MaterialEditor : public wxGridCellChoiceEditor {
//private:
//	MaterialLibrary* library;
////	Material value;
//public:
//	MaterialEditor(MaterialLibrary* library);
//	virtual wxGridCellEditor* Clone() const;
//	virtual ~MaterialEditor();
//};

#endif /* MATERIALEDITOR_H_ */
