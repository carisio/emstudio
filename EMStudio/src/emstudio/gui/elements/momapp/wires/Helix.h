/*
 * Helix.h
 *
 *  Created on: 28/05/2014
 *      Author: leandrocarisio
 */

#ifndef MOM_HELIX_H_
#define MOM_HELIX_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/CircularTubeDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

namespace mom {

class Helix : public ElementsWithSegments {
private:
	MathExpressionParser wireRadius;
	MathExpressionParser helixRadiusTop, helixRadiusBottom, length, spaceBetweenTurns;
	IntMathExpressionParser numberOfSegments;

public:
	Helix();
	virtual ~Helix();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);

    virtual Segments BuildSegments();

    virtual bool IsAllPropertiesTogetherValid();
};

} /* namespace mom */
#endif /* MOM_HELIX_H_ */
