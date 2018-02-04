/*
 * RadiationPattern.h
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#ifndef RADIATIONPATTERN_H_
#define RADIATIONPATTERN_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/ProbeType.h"
#include "emstudio/dto/fdtdapp/RadiationPatternDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

#include "emstudio/util/resources/UtilResource.h"

class RadiationPattern : public ElementsWithFacets {
private:
	Point3DME lowerBoundary, upperBoundary;
	MathExpressionParser initialFrequency;
	MathExpressionParser frequencyStep;
	IntMathExpressionParser nFrequency;
	BoolWrapper visible;
	ColourWrapper colour;

public:
	RadiationPattern();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

    virtual bool IsAllPropertiesTogetherValid();

	virtual ~RadiationPattern();
};

#endif /* RADIATIONPATTERN_H_ */
