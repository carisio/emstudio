/*
 * FieldAtPathResult.h
 *
 *  Created on: 26/09/2013
 *      Author: leandrocarisio
 */

#ifndef FIELDATPATHRESULT_H_
#define FIELDATPATHRESULT_H_

#include "TableResult.h"

/*
 * O campo no caminho é guardado em um TableResult.
 *
 * A extensão de TableResult é necessário para visualizá-la corretamente
 * (possibilitando, por exemplo, visualização dos dados em escala dB ou linear).
 *
 */
class FieldAtPathResult : public TableResult {
public:
	FieldAtPathResult(wxString title = "", GenericTable data = GenericTable(), BoolWrapper canBeInterpretedAsChart = BoolWrapper());
	virtual ~FieldAtPathResult();

	void SetField(GenericTable::ColumnDataRepresentation positionField, wxString positionTitle,
			GenericTable::ColumnDataRepresentation ExMag, GenericTable::ColumnDataRepresentation EyMag,
			GenericTable::ColumnDataRepresentation EzMag, GenericTable::ColumnDataRepresentation HxMag,
			GenericTable::ColumnDataRepresentation HyMag, GenericTable::ColumnDataRepresentation HzMag,
			GenericTable::ColumnDataRepresentation ExPhase, GenericTable::ColumnDataRepresentation EyPhase,
			GenericTable::ColumnDataRepresentation EzPhase, GenericTable::ColumnDataRepresentation HxPhase,
			GenericTable::ColumnDataRepresentation HyPhase, GenericTable::ColumnDataRepresentation HzPhase);

	wxString GetPositionTitle();
	GenericTable::ColumnDataRepresentation GetPosition();
	GenericTable::ColumnDataRepresentation GetExMag();
	GenericTable::ColumnDataRepresentation GetEyMag();
	GenericTable::ColumnDataRepresentation GetEzMag();
	GenericTable::ColumnDataRepresentation GetHxMag();
	GenericTable::ColumnDataRepresentation GetHyMag();
	GenericTable::ColumnDataRepresentation GetHzMag();
	GenericTable::ColumnDataRepresentation GetExPhase();
	GenericTable::ColumnDataRepresentation GetEyPhase();
	GenericTable::ColumnDataRepresentation GetEzPhase();
	GenericTable::ColumnDataRepresentation GetHxPhase();
	GenericTable::ColumnDataRepresentation GetHyPhase();
	GenericTable::ColumnDataRepresentation GetHzPhase();

	virtual ResultSmartPointer NewResult();
	virtual wxString GetResultClassName();
	virtual bool ExportData(wxString fileName);
	virtual wxString GetMatlabFileContents(wxString dataFileName);
};

#endif /* FIELDATPATHRESULT_H_ */
