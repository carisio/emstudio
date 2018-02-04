/*
 * RadiationPatternMoMCore.h
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#ifndef RADIATIONPATTERNMOMCORE_H_
#define RADIATIONPATTERNMOMCORE_H_

#include "MoMElementCore.h"
#include "emstudio/dto/momapp/RadiationPatternDTO.h"
#include "emstudio/core/results/Result.h"
#include "wx/wx.h"

namespace mom {

class RadiationPatternMoMCore : public MoMElementCore {
private:
	wxString necCommand;
	ElementResults elementResults;
	RadiationPatternDTO dto;

public:
	RadiationPatternMoMCore();
	virtual ~RadiationPatternMoMCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
	virtual MoMElementCoreType GetType();
	virtual void SetExecutionCard();

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual wxString GetNECCommand();
};

} /* namespace mom */
#endif /* RADIATIONPATTERNMOMCORE_H_ */
