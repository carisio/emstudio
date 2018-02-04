/*
 * DXFObjectFDTDCore.h
 *
 *  Created on: 09/05/2013
 *      Author: Leandro
 */

#ifndef DXFOBJECTFDTDCORE_H_
#define DXFOBJECTFDTDCORE_H_

#include "FDTDElementCore.h"

class DXFObjectFDTDCore : public FDTDElementCore {
public:
	DXFObjectFDTDCore();
	virtual ~DXFObjectFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);
};

#endif /* DXFOBJECTFDTDCORE_H_ */
