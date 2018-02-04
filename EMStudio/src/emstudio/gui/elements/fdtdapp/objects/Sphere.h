/*
 * Sphere.h
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/SphereDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"


class Sphere : public ElementsWithFacets {
private:
	Point3DME center;
	MathExpressionParser innerRadius, outerRadius;
	BoolWrapper showSolid;
	BoolWrapper visible;

	vector<Facet> GetFacet(double radius);
public:
	Sphere();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual void DoMove(Point3DME p);

    virtual vector<Facet> BuildFacets();

    virtual bool IsAllPropertiesTogetherValid();

	virtual ~Sphere();
};

#endif /* SPHERE_H_ */
