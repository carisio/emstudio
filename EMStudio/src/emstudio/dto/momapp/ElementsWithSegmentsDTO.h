/*
 * ElementsWithSegmentsDTO.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef ELEMENTSWITHSEGMENTSDTO_H_
#define ELEMENTSWITHSEGMENTSDTO_H_

#include "../ElementDTO.h"
#include "emstudio/util/nec/Segment.h"

#include "wx/wx.h"

namespace mom {

class ElementsWithSegmentsDTO;

typedef std::tr1::shared_ptr<ElementsWithSegmentsDTO> ElementsWithSegmentsDTOSmartPointer;

class ElementsWithSegmentsDTO : public ElementDTO {
private:
	/* Variáveis usadas para representar um objeto que segmentos */
	Segments segments;
public:
	ElementsWithSegmentsDTO();
	virtual ~ElementsWithSegmentsDTO();

	virtual void Unnormalize(Units units);
	virtual void DoUnnormalize(Units units);

    bool HasSegments();
    void SetSegments(Segments s);
    Segments GetSegments();
};

} /* namespace mom */
#endif /* ELEMENTSWITHSEGMENTSDTO_H_ */
