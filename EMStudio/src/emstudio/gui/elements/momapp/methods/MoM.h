/*
 * MoM.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef MOM_H_
#define MOM_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/MethodType.h"
#include "emstudio/dto/momapp/MoMDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

#include "emstudio/util/facet/Facet.h"
#include <vector>

namespace mom {

class MoM : public ElementsWithSegments {
private:
	MathExpressionParser initialFrequency;
	MathExpressionParser frequencyStep;
	IntMathExpressionParser nFrequency;
	GroundParameters groundParameters;
	BoolWrapper extendedThinWire;

	std::vector<Facet> circularCliffGround1;
	std::vector<Facet> circularCliffGround2;
	std::vector<Facet> BuildCircularTube(double innerRadius, double outerRadius, double zMin, double zMax);
public:
	MoM();
	virtual ~MoM();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool IsAllPropertiesTogetherValid();
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
};

} /* namespace mom */
#endif /* MOM_H_ */
