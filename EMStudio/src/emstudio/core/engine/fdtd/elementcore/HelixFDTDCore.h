/*
 * HelixFDTDCore.h
 *
 *  Created on: 07/05/2012
 *      Author: Leandro
 */

#ifndef HELIXFDTDCORE_H_
#define HELIXFDTDCORE_H_

#include "FDTDElementCore.h"

class HelixFDTDCore : public FDTDElementCore {
public:
	HelixFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual ~HelixFDTDCore();
};

#endif /* HELIXFDTDCORE_H_ */
