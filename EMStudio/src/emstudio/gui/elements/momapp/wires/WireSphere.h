/*
 * Sphere.h
 *
 *  Created on: 15/07/2014
 *      Author: leandrocarisio
 */

#ifndef MOMSPHERE_H_
#define MOMSPHERE_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/WireType.h"
#include "emstudio/dto/momapp/WireDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

namespace mom {

class WireSphere : public ElementsWithSegments {
private:
	MathExpressionParser wireRadius, sphereRadius;
	IntMathExpressionParser numberOfSegments;
	Point3DME center;
public:
	WireSphere();
	virtual ~WireSphere();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);

    virtual Segments BuildSegments();

    virtual bool IsAllPropertiesTogetherValid();
};

} /* namespace mom */
#endif /* MOMSPHERE_H_ */
