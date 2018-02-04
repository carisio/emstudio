/*
 * ChargeDensitiesDTO.h
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#ifndef CHARGEDENSITIESDTO_H_
#define CHARGEDENSITIESDTO_H_

#include "ElementsWithSegmentsDTO.h"

namespace mom {

class ChargeDensitiesDTO : public ElementsWithSegmentsDTO {
public:
	ChargeDensitiesDTO();
	virtual ~ChargeDensitiesDTO();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
};

} /* namespace mom */
#endif /* CHARGEDENSITIESDTO_H_ */
