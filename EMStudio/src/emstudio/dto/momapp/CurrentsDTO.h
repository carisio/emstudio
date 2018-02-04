/*
 * CurrentsDTO.h
 *
 *  Created on: 11/06/2014
 *      Author: leandrocarisio
 */

#ifndef CURRENTSDTO_H_
#define CURRENTSDTO_H_

#include "ElementsWithSegmentsDTO.h"

namespace mom {

class CurrentsDTO : public ElementsWithSegmentsDTO {
public:
	CurrentsDTO();
	virtual ~CurrentsDTO();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
};

} /* namespace mom */
#endif /* CURRENTSDTO_H_ */
