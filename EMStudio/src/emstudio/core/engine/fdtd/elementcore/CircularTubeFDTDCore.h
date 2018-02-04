/*
 * CircularTubeFDTDCore.h
 *
 *  Created on: 07/05/2012
 *      Author: Leandro
 */

#ifndef CIRCULARTUBEFDTDCORE_H_
#define CIRCULARTUBEFDTDCORE_H_

#include "FDTDElementCore.h"

class CircularTubeFDTDCore : public FDTDElementCore {
public:
	CircularTubeFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual ~CircularTubeFDTDCore();
};

#endif /* CIRCULARTUBEFDTDCORE_H_ */
