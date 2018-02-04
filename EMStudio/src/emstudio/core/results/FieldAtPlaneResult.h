/*
 * FieldAtPlaneResult.h
 *
 *  Created on: 24/04/2013
 *      Author: Leandro
 */

#ifndef FIELDATPLANERESULT_H_
#define FIELDATPLANERESULT_H_

#include "Result.h"
#include "emstudio/gui/basetypes/StringWrapper.h"
#include "emstudio/gui/basetypes/DoubleVector.h"
#include "emstudio/gui/basetypes/DoubleMatrix3D.h"
#include "emstudio/gui/basetypes/Sheet.h"
#include "emstudio/util/resources/UtilResource.h"

#include <list>

class FieldAtPlaneResult : public Result {
private:
	DoubleVector positionDim1;
	DoubleVector positionDim2;
	Sheet plane;
	DoubleVector timeVector;
	StringWrapper timeUnit;
	StringWrapper spaceUnit;
	DoubleMatrix3D field;
public:
	FieldAtPlaneResult(wxString fieldName = "",
			DoubleVector positionDim1 = DoubleVector(),
			DoubleVector positionDim2 = DoubleVector(),
			wxString spaceUnit = "",
			Sheet plane = Sheet(),
			DoubleVector timeVector = DoubleVector(),
			wxString timeUnit = "",
			DoubleMatrix3D field = DoubleMatrix3D());
	virtual ~FieldAtPlaneResult();

	virtual ResultSmartPointer NewResult();
    virtual wxIcon GetIcon();
    virtual bool ExportData(wxString fileName);
    virtual wxString GetResultClassName();

	wxString GetFieldName();
	DoubleVector GetPositionDim1();
	DoubleVector GetPositionDim2();
	wxString GetSpaceUnit();
	Sheet GetPlane();
	DoubleVector GetTimeVector();
	wxString GetTimeUnit();
	DoubleMatrix3D GetField();
};

#endif /* FIELDATPLANERESULT_H_ */
