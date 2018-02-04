/*
 * TransmissionLineMoMCore.h
 *
 *  Created on: 06/06/2014
 *      Author: leandrocarisio
 */

#ifndef TRANSMISSIONLINEMOMCORE_H_
#define TRANSMISSIONLINEMOMCORE_H_


#include "MoMElementCore.h"
#include "emstudio/dto/momapp/TransmissionLineDTO.h"
#include "emstudio/core/results/Result.h"
#include "wx/wx.h"

namespace mom {

class TransmissionLineMoMCore : public MoMElementCore {
private:
	wxString necCommand;
	TransmissionLineDTO dto;
public:
	TransmissionLineMoMCore();
	virtual ~TransmissionLineMoMCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
	virtual MoMElementCoreType GetType();
	virtual void SetConnection();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual wxString GetNECCommand();
};

} /* namespace mom */
#endif /* TRANSMISSIONLINEMOMCORE_H_ */
