/*
 * VoltageSourceMoMCore.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef VOLTAGESOURCEMOMCORE_H_
#define VOLTAGESOURCEMOMCORE_H_

#include "MoMElementCore.h"
#include "emstudio/dto/momapp/VoltageSourceDTO.h"
#include "emstudio/core/results/Result.h"
#include "wx/wx.h"

namespace mom {

class VoltageSourceMoMCore : public MoMElementCore {
private:
	VoltageSourceDTO dto;
	wxString necCommand;
public:
	VoltageSourceMoMCore();
	virtual ~VoltageSourceMoMCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
	virtual MoMElementCoreType GetType();
	virtual void SetSource();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual wxString GetNECCommand();
};

} /* namespace mom */
#endif /* VOLTAGESOURCEMOMCORE_H_ */
