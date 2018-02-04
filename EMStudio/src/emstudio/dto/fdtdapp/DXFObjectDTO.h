/*
 * DXFObjectDTO.h
 *
 *  Created on: 09/05/2013
 *      Author: leandrocarisio
 */

#ifndef DXFOBJECTDTO_H_
#define DXFOBJECTDTO_H_

#include "ElementsWithFacetsDTO.h"

class DXFObjectDTO : public ElementsWithFacetsDTO {
public:
	DXFObjectDTO();
	virtual ~DXFObjectDTO();
	virtual wxString GetDTOClassName();
};

#endif /* DXFOBJECTDTO_H_ */
