/*
 * ThinWire.h
 *
 *  Created on: 29/09/2011
 *      Author: Leandro
 */

#ifndef THINWIRE_H_
#define THINWIRE_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/ThinWireDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class ThinWire : public ElementsWithFacets {
private:
//	ColourWrapper colour;
	MathExpressionParser length, radius;
	Point3DME positionBottom;
	Orientation orientation;
	BoolWrapper showSolid;
	BoolWrapper visible;
public:
	ThinWire();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

	virtual ~ThinWire();
};

#endif /* THINWIRE_H_ */
