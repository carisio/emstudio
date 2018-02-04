/*
 * RectangularTube.h
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#ifndef RECTANGULARTUBE_H_
#define RECTANGULARTUBE_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/RectangularTubeDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class RectangularTube : public ElementsWithFacets {
private:
	RectangularTubeGeometryME geometry;
	BoolWrapper showSolid;
	BoolWrapper visible;
	Point3DME rotateAxis;
	Point3DME translateTo;
public:
	RectangularTube();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual void DoMove(Point3DME p);

	virtual vector<Facet> BuildFacets();

	virtual bool IsAllPropertiesTogetherValid();

	virtual ~RectangularTube();
};

#endif /* RECTANGULARTUBE_H_ */
