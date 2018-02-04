/*
 * CircularTube.h
 *
 *  Created on: 29/09/2011
 *      Author: Leandro
 */

#ifndef CIRCULARTUBE_H_
#define CIRCULARTUBE_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/CircularTubeDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class CircularTube : public ElementsWithFacets {
private:
	MathExpressionParser bottomRadius, topRadius, thickness;
	Point3DME bottomCenter, topCenter;
	BoolWrapper showSolid;
	BoolWrapper visible;
public:
	CircularTube();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

    virtual vector<Facet> BuildFacets();

    virtual bool IsAllPropertiesTogetherValid();

	virtual ~CircularTube();
};


#endif /* CIRCULARTUBE_H_ */
