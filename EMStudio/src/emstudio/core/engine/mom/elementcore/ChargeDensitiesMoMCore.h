/*
 * ChargeDensitiesMoMCore.h
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#ifndef CHARGEDENSITIESMOMCORE_H_
#define CHARGEDENSITIESMOMCORE_H_

#include "MoMElementCore.h"
#include "emstudio/dto/momapp/ChargeDensitiesDTO.h"
#include "emstudio/core/results/Result.h"
#include "wx/wx.h"

namespace mom {

class ChargeDensitiesMoMCore  : public MoMElementCore {
private:
	ChargeDensitiesDTO dto;
public:
	ChargeDensitiesMoMCore();
	virtual ~ChargeDensitiesMoMCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
	virtual MoMElementCoreType GetType();
	virtual void SetProbe();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual wxString GetNECCommand();
};


} /* namespace mom */
#endif /* CHARGEDENSITIESMOMCORE_H_ */
