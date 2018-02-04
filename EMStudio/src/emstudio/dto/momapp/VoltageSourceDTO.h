/*
 * VoltageSourceDTO.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef VOLTAGESOURCEDTO_H_
#define VOLTAGESOURCEDTO_H_

#include "ElementsWithSegmentsDTO.h"

namespace mom {

class VoltageSourceDTO : public ElementsWithSegmentsDTO {
private:
	double realPart, imagPart;
	double x, y, z;
public:
	VoltageSourceDTO();
	virtual ~VoltageSourceDTO();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();

	void SetRealPart(double r);
	void SetImagPart(double i);
	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);
	double GetRealPart();
	double GetImagPart();
	double GetX();
	double GetY();
	double GetZ();
};

} /* namespace mom */
#endif /* VOLTAGESOURCEDTO_H_ */
