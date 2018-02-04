/*
 * DeltaGap.h
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#ifndef DELTAGAP_H_
#define DELTAGAP_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/SourceType.h"
#include "emstudio/dto/fdtdapp/DeltaGapDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class DeltaGap : public ElementsWithFacets {
private:
	ColourWrapper colour;
	ExcitationME excitation;
	Point3DME position;
//	MathExpressionParser resistance;
	Orientation orientation;
	MathExpressionParser initialFrequency;
	MathExpressionParser stepFrequency;
	IntMathExpressionParser nFrequency;
//	BoolWrapper resistiveSource;
	BoolWrapper visible;
public:
	DeltaGap();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual bool IsAllPropertiesTogetherValid();
    virtual void DoMove(Point3DME p);

	virtual ~DeltaGap();
};

#endif /* DELTAGAP_H_ */
