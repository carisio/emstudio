/*
 * CircularPECSheet.h
 *
 *  Created on: 20/11/2013
 *      Author: leandrocarisio
 */

#ifndef CIRCULARPECSHEET_H_
#define CIRCULARPECSHEET_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object2DType.h"
#include "emstudio/dto/fdtdapp/GenericPECSheetsDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"
#include "emstudio/includes/dtos.h"
#include <vector>

class CircularPECSheet : public ElementsWithFacets {
private:
	Plane plane;
	Point3DME center;
	MathExpressionParser initialAngle;
	MathExpressionParser finalAngle;
	MathExpressionParser outerRadius;
	MathExpressionParser innerRadius;
	BoolWrapper showSolid;
	BoolWrapper visible;

	std::vector<GenericSheet> GetGenericSheets();
public:
	CircularPECSheet();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsAllPropertiesTogetherValid();
	virtual void DoMove(Point3DME p);

	virtual ~CircularPECSheet();
};

#endif /* CIRCULARPECSHEET_H_ */
