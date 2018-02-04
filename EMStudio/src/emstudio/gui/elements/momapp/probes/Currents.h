/*
 * Currents.h
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#ifndef CURRENTS_H_
#define CURRENTS_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/types/ProbeType.h"
#include "emstudio/dto/momapp/CurrentsDTO.h"

namespace mom {

class Currents : public ElementsWithSegments {
private:
public:
	Currents();
	virtual ~Currents();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);

    virtual bool IsAllPropertiesTogetherValid();
};
} /* namespace mom */
#endif /* CURRENTS_H_ */
