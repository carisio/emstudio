/*
 * RadiationPattern.h
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#ifndef MOMRADIATIONPATTERN_H_
#define MOMRADIATIONPATTERN_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/types/ProbeType.h"
#include "emstudio/dto/momapp/RadiationPatternDTO.h"
#include "emstudio/includes/basetypevalidators.h"
#include "emstudio/includes/basetypes.h"


namespace mom {

class RadiationPattern : public ElementsWithSegments {
private:
	MathExpressionParser initialFrequency;
	MathExpressionParser frequencyStep;
	IntMathExpressionParser nFrequency;
public:
	RadiationPattern();
	virtual ~RadiationPattern();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);
};

} /* namespace mom */
#endif /* MOMRADIATIONPATTERN_H_ */
