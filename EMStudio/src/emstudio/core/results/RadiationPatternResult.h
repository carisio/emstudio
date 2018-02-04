/*
 * RadiationPatternResult.h
 *
 *  Created on: 18/04/2013
 *      Author: Leandro
 */

#ifndef RADIATIONPATTERNRESULT_H_
#define RADIATIONPATTERNRESULT_H_

#include "TableResult.h"
#include "emstudio/gui/basetypes/Plane.h"

/* Os diagramas de radia��o s�o guardados em um TableResult. � necess�rio diferenciar apenas para
 * conseguir visualiz�-lo d euma forma diferente (diagrama polar).
 */

class RadiationPatternResult : public TableResult {
private:
	Plane plane;
public:
	RadiationPatternResult(wxString title = "", GenericTable data = GenericTable(), BoolWrapper canBeInterpretedAsChart = BoolWrapper(), Plane plane = Plane());
	virtual ~RadiationPatternResult();

	void SetPlane(Plane p);
	Plane GetPlane();
	virtual ResultSmartPointer NewResult();
	virtual wxString GetResultClassName();
	virtual bool ExportData(wxString fileName);
	virtual wxString GetInfoFileContents();
};

#endif /* RADIATIONPATTERNRESULT_H_ */
