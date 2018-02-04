/*
 * PropertiesGridTable.h
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#ifndef PROPERTIESGRIDTABLE_H_
#define PROPERTIESGRIDTABLE_H_

#include "wx/wx.h"
#include "wx/grid.h"
#include "emstudio/gui/elements/Propertyable.h"
#include "emstudio/gui/elements/Property.h"

class PropertiesGridTable : public wxGridTableBase {
private:
	PropertyableSmartPointer object;
public:
	PropertiesGridTable(PropertyableSmartPointer propertyable);

	virtual int GetNumberRows();
	virtual int GetNumberCols();
	virtual bool IsEmptyCell( int row, int col );
	virtual wxString GetTypeName(int row, int col);

	/* Get and Set methods */
	virtual wxString GetValue( int row, int col );
	virtual void SetValue( int row, int col, const wxString& value);

	BaseType* GetValueAsBaseType(int row, int col);
	void SetValueAsBaseType(int row, int col, BaseType* value);

	/* Row and Col labels */
	virtual wxString GetRowLabelValue(int row);
	virtual wxString GetColLabelValue(int row);

	Propertyable::Iterator GetPropertyAtRow(int row);

	virtual ~PropertiesGridTable();
};

#endif /* PROPERTIESGRIDTABLE_H_ */
