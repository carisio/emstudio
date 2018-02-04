/*
 * CurrentsMoMCore.h
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#ifndef CURRENTSMOMCORE_H_
#define CURRENTSMOMCORE_H_

#include "MoMElementCore.h"
#include "emstudio/dto/momapp/CurrentsDTO.h"
#include "emstudio/core/results/Result.h"
#include "wx/wx.h"

namespace mom {

class CurrentsMoMCore : public MoMElementCore {
private:
	CurrentsDTO dto;
public:
	CurrentsMoMCore();
	virtual ~CurrentsMoMCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
	virtual MoMElementCoreType GetType();
	virtual void SetProbe();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual wxString GetNECCommand();
};

} /* namespace mom */
#endif /* CURRENTSMOMCORE_H_ */
