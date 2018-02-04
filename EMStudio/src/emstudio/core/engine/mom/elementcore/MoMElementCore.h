/*
 * MoMElementCore.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef MOMELEMENTCORE_H_
#define MOMELEMENTCORE_H_

#include "emstudio/core/ElementCore.h"
#include "emstudio/util/nec/Segment.h"

namespace mom {

class MoMElementCore;

enum MoMElementCoreType{GEOMETRY, SOURCE, CONNECTIONS, EXECUTION_CARDS, PROBES};

class MoMElementCore : public ElementCore {
public:
	MoMElementCore();
	virtual ~MoMElementCore();

	Segments GetSegments();

	virtual ElementCoreSmartPointer NewElementCore() = 0;
	virtual void DoConfigure(ElementDTOSmartPointer dto) = 0;
	virtual MoMElementCoreType GetType() = 0;
	virtual void SetGeometry(int tag_id);
	virtual void SetSource();
	virtual void SetConnection();
	virtual void SetProbe();
	virtual void SetExecutionCard();

	virtual wxString GetNECCommand() = 0;
};

} /* namespace mom */
#endif /* MOMELEMENTCORE_H_ */
