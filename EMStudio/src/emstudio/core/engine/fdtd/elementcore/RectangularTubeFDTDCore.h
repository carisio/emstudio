/*
 * RectangularTubeFDTDCore.h
 *
 *  Created on: 07/05/2012
 *      Author: Leandro
 */

#ifndef RECTANGULARTUBEFDTDCORE_H_
#define RECTANGULARTUBEFDTDCORE_H_

#include "FDTDElementCore.h"

class RectangularTubeFDTDCore : public FDTDElementCore {
public:
	RectangularTubeFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual ~RectangularTubeFDTDCore();
};

#endif /* RECTANGULARTUBEFDTDCORE_H_ */
