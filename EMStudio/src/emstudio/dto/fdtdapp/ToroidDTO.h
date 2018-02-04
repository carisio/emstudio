/*
 * ToroidDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef TOROIDDTO_H_
#define TOROIDDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"

class ToroidDTO : public ElementsWithFacetsDTO {
private:
	double x; double y; double z;
	double toroidRadius; double wireRadius;
	Orientation orientation;

public:
	ToroidDTO();

	virtual wxString GetDTOClassName();
	virtual void DoUnnormalize(Units units);

	double GetToroidRadius() const;
	Orientation GetOrientation() const;
	double GetWireRadius() const;
	double GetX() const;
	double GetY() const;
	double GetZ() const;
	void SetToroidRadius(double toroidRadius);
	void SetOrientation(Orientation orientation);
	void SetWireRadius(double wireRadius);
	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);


	virtual ~ToroidDTO();
};

#endif /* TOROIDDTO_H_ */
