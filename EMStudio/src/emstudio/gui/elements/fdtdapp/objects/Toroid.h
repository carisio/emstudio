/*
 * Toroid.h
 *
 *  Created on: 29/09/2011
 *      Author: Leandro
 */

#ifndef TOROID_H_
#define TOROID_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/ToroidDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class Toroid : public ElementsWithFacets {
private:
	Point3DME center;
	Point3DME rotateAxis;
	Point3DME translateTo;
	MathExpressionParser toroidRadius, wireRadius;
	Orientation orientation;
	BoolWrapper showSolid;
	BoolWrapper visible;
public:
	Toroid();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual void DoMove(Point3DME p);

    virtual vector<Facet> BuildFacets();

    virtual bool IsAllPropertiesTogetherValid();

	virtual ~Toroid();
};

#endif /* TOROID_H_ */
