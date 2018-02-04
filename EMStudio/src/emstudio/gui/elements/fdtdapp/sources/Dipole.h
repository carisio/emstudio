/*
 * Dipole.h
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#ifndef DIPOLE_H_
#define DIPOLE_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/SourceType.h"
#include "emstudio/dto/fdtdapp/DipoleDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class Dipole : public ElementsWithFacets {
private:
	ExcitationME excitation;
	MathExpressionParser length;
	Point3DME positionCenter;
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
	Dipole();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

	virtual ~Dipole();
};

#endif /* DIPOLE_H_ */
