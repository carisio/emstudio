/*
 * Helix.h
 *
 *  Created on: 29/09/2011
 *      Author: Leandro
 */

#ifndef HELIX_H_
#define HELIX_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/HelixDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

namespace fdtd {

class Helix  : public ElementsWithFacets {
private:
//	ColourWrapper color;
	MathExpressionParser startLength;
	Point3DME center;
	Point3DME rotateAxis;
	Point3DME translateTo;
	MathExpressionParser turns, turnSeparation;
	MathExpressionParser startAngle;
	MathExpressionParser helixRadius, wireRadius;
	Orientation orientation;
	BoolWrapper showSolid;
	BoolWrapper visible;
public:
	Helix();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual void DoMove(Point3DME p);

	virtual vector<Facet> BuildFacets();

	virtual bool IsAllPropertiesTogetherValid();

	virtual ~Helix();
};

}
#endif /* HELIX_H_ */
