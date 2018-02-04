/*
 * FieldAtPath.h
 *
 *  Created on: 21/03/2012
 *      Author: Leandro
 */

#ifndef FIELDATPATH_H_
#define FIELDATPATH_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/ProbeType.h"
#include "emstudio/dto/fdtdapp/FieldAtPathDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class FieldAtPath : public ElementsWithFacets {
private:
	ColourWrapper colour;
	MathExpressionParser length;
	Point3DME positionBottom;
	Orientation orientation;
	BoolWrapper visible;
	MathExpressionParser initialFrequency;
	MathExpressionParser frequencyStep;
	IntMathExpressionParser nFrequency;

public:
	FieldAtPath();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

	virtual ~FieldAtPath();
};

#endif /* FIELDATPATH_H_ */
