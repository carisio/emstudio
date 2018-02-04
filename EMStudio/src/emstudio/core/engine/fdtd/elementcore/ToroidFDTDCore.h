/*
 * ToroidFDTDCore.h
 *
 *  Created on: 08/05/2012
 *      Author: Leandro
 */

#ifndef TOROIDFDTDCORE_H_
#define TOROIDFDTDCORE_H_

#include "FDTDElementCore.h"

class ToroidFDTDCore : public FDTDElementCore {
public:
	ToroidFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual ~ToroidFDTDCore();
};

#endif /* TOROIDFDTDCORE_H_ */
