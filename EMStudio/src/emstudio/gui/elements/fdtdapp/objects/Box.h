/*
 * Cube.h
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#ifndef BOX_H_
#define BOX_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/BoxDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class Box : public ElementsWithFacets {
private:
	Point3DME lowerBoundary, upperBoundary;
	Point3DME rotateAxis;
	Point3DME translateTo;
//	ColourWrapper colour;
	BoolWrapper showSolid;
	BoolWrapper visible;
	MatchWithPML matchWithPML;
public:
	Box();
	virtual ~Box();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);

    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

    virtual vector<Facet> BuildFacets();

    virtual bool IsAllPropertiesTogetherValid();
};

#endif /* BOX_H_ */
