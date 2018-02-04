/*
 * WireDTO.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef WIREDTO_H_
#define WIREDTO_H_

#include "ElementsWithSegmentsDTO.h"
#include "emstudio/util/vector/Rvector3.h"

namespace mom {

class WireDTO : public ElementsWithSegmentsDTO {
private:
	Rvector3 p1, p2;
	double radius;
	int numberOfSegments;
public:
	WireDTO();
	virtual ~WireDTO();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();

	void SetP1(Rvector3 p1);
	void SetP2(Rvector3 p2);
	void SetRadius(double radius);
	void SetNumberOfSegments(int numberOfSegments);
	Rvector3 GetP1();
	Rvector3 GetP2();
	double GetRadius();
	int GetNumberOfSegments();
};

} /* namespace mom */
#endif /* WIREDTO_H_ */
