/*
 * FDTD.h
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#ifndef FDTD_H_
#define FDTD_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/MethodType.h"
#include "emstudio/dto/fdtdapp/FDTDDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class FDTD : public ElementsWithFacets {
private:
	Point3DME lowerBoundary, upperBoundary;
	IntMathExpressionParser xcells, ycells, zcells;
	IntMathExpressionParser timesteps;
//	DoubleWrapper deltaT;
	AbsorvingBoundaryCondition abc;
	ColourWrapper gridColour;
	BoolWrapper gridVisible;
//	BoolWrapper smoothMesh;
public:
	FDTD();
	virtual ~FDTD();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

	virtual bool IsAllPropertiesTogetherValid();
};

#endif /* FDTD_H_ */
