/*
 * Monopole.h
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#ifndef MONOPOLE_H_
#define MONOPOLE_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/SourceType.h"
#include "emstudio/dto/fdtdapp/MonopoleDTO.h"
#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class Monopole : public ElementsWithFacets {
private:
	ExcitationME excitation;
	MathExpressionParser length;
	Point3DME positionBottom;
	Orientation orientation;
	IntWrapper linePoints;
	IntWrapper sourcePoints;
	MathExpressionParser wireRadius;
	MathExpressionParser lineImpedance;
//	DoubleWrapper velocityFactor;
	MathExpressionParser initialFrequency;
	MathExpressionParser frequencyStep;
	IntMathExpressionParser nFrequency;
//	ColourWrapper colour;
	BoolWrapper showSolid;
	BoolWrapper visible;
public:
	Monopole();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

    virtual ~Monopole();
};

#endif /* MONOPOLE_H_ */
