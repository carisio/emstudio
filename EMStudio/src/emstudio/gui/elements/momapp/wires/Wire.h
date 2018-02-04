/*
 * Wire.h
 *
 *  Created on: 27/05/2014
 *      Author: leandrocarisio
 */

#ifndef WIRE_H_
#define WIRE_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/WireType.h"
#include "emstudio/dto/momapp/WireDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

namespace mom {

class Wire : public ElementsWithSegments {
private:
	MathExpressionParser wireRadius;
	IntMathExpressionParser numberOfSegments;
	Point3DME bottomCenter, topCenter;
public:
	Wire();
	virtual ~Wire();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);

    virtual Segments BuildSegments();

    virtual bool IsAllPropertiesTogetherValid();
};

}
#endif /* WIRE_H_ */
