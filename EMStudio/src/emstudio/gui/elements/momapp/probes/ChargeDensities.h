/*
 * ChargeDensities.h
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#ifndef CHARGEDENSITIES_H_
#define CHARGEDENSITIES_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/types/ProbeType.h"
#include "emstudio/dto/momapp/ChargeDensitiesDTO.h"

namespace mom {

class ChargeDensities : public ElementsWithSegments {
private:
public:
	ChargeDensities();
	virtual ~ChargeDensities();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);

    virtual bool IsAllPropertiesTogetherValid();
};

} /* namespace mom */
#endif /* CHARGEDENSITIES_H_ */
