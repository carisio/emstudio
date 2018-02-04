/*
 * FieldAtPoint.h
 *
 *  Created on: 02/03/2012
 *      Author: Administrador
 */

#ifndef FIELDATPOINT_H_
#define FIELDATPOINT_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/ProbeType.h"
#include "emstudio/dto/fdtdapp/FieldAtPointDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class FieldAtPoint : public ElementsWithFacets {
private:
	Point3DME point;
	ColourWrapper color;
	BoolWrapper visible;
	BoolWrapper timeResponse;
	MathExpressionParser initialFrequency;
	MathExpressionParser frequencyStep;
	IntMathExpressionParser nFrequency;

public:
	FieldAtPoint();
	virtual ~FieldAtPoint();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);
};

#endif /* FIELDATPOINT_H_ */
