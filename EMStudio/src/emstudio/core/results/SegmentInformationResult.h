/*
 * SegmentInformationResult.h
 *
 *  Created on: 10/07/2014
 *      Author: leandrocarisio
 */

#ifndef MOM_SEGMENT_INFORMATION_RESULT_H_
#define MOM_SEGMENT_INFORMATION_RESULT_H_

#include "TableResult.h"

namespace mom {

class SegmentInformationResult : public TableResult {
private:
	StringWrapper freqUnit;
public:
	SegmentInformationResult(wxString title = "", GenericTable data = GenericTable());
	virtual ~SegmentInformationResult();

	void SetFrequencyUnit(wxString frequencyUnit);
	wxString GetFrequencyUnit();
	void SetData(GenericTable::ColumnDataRepresentation frequency,
			GenericTable::ColumnDataRepresentation x1, GenericTable::ColumnDataRepresentation y1, GenericTable::ColumnDataRepresentation z1,
			GenericTable::ColumnDataRepresentation x2, GenericTable::ColumnDataRepresentation y2, GenericTable::ColumnDataRepresentation z2,
			GenericTable::ColumnDataRepresentation radius,
			GenericTable::ColumnDataRepresentation infoReal, wxString infoRealLabel,
			GenericTable::ColumnDataRepresentation infoIamginary, wxString infoImagLabel,
			wxString unitFrequency, wxString unitLength);
	GenericTable::ColumnDataRepresentation GetFrequency();
	GenericTable::ColumnDataRepresentation GetX1();
	GenericTable::ColumnDataRepresentation GetY1();
	GenericTable::ColumnDataRepresentation GetZ1();
	GenericTable::ColumnDataRepresentation GetX2();
	GenericTable::ColumnDataRepresentation GetY2();
	GenericTable::ColumnDataRepresentation GetZ2();
	GenericTable::ColumnDataRepresentation GetRadius();
	GenericTable::ColumnDataRepresentation GetInfoReal();
	GenericTable::ColumnDataRepresentation GetInfoImag();

	virtual ResultSmartPointer NewResult();
	virtual wxString GetResultClassName();
	virtual bool ExportData(wxString fileName);
	virtual wxString GetMatlabFileContents(wxString dataFileName);
	virtual wxIcon GetIcon();
};

} /* namespace mom */
#endif /* MOM_SEGMENT_INFORMATION_RESULT_H_ */
