/*
 * GenericTable.h
 *
 *  Created on: 13/03/2012
 *      Author: leandrocarisio
 */

#ifndef GENERICTABLE_H_
#define GENERICTABLE_H_

#include "wx/wx.h"
#include "BaseType.h"
#include <vector>


class GenericTable : public BaseType {
public:
	typedef std::vector<double> ColumnDataRepresentation;

private:
	std::vector<wxString> dataLabel;
	std::vector<ColumnDataRepresentation> data;
public:
	GenericTable();
	virtual ~GenericTable();

	virtual void Copy(BaseType* b);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();
	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	std::vector<wxString>& GetColumnsLabel();
	std::vector<ColumnDataRepresentation>& GetColumns();
    ColumnDataRepresentation& GetColumn(int col);
    void AppendInColumn(int col, double val);
    void AddColumn(ColumnDataRepresentation column);
    void SetTableData(std::vector<ColumnDataRepresentation> v);
    void SetColumnsLabel(std::vector<wxString> colLabels);
};

#endif /* GENERICTABLE_H_ */
