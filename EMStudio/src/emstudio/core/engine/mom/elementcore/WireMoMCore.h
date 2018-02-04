/*
 * WireMoMCore.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef WIREMOMCORE_H_
#define WIREMOMCORE_H_

#include "emstudio/dto/momapp/WireDTO.h"
#include "MoMElementCore.h"
#include "wx/wx.h"

namespace mom {

class WireMoMCore : public MoMElementCore {
private:
	WireDTO dto;
	wxString necCommand;
public:
	WireMoMCore();
	virtual ~WireMoMCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
	virtual void SetGeometry(int tag_id);
	virtual MoMElementCoreType GetType();
	virtual wxString GetNECCommand();
};

} /* namespace mom */
#endif /* WIREMOMCORE_H_ */
