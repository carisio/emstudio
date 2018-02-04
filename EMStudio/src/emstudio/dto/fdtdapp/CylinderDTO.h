/*
 * CylinderDTO.h
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#ifndef CYLINDERDTO_H_
#define CYLINDERDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"

class CylinderDTO : public ElementsWithFacetsDTO {
private:
	double x; double y; double z; double length; double outerRadius; double innerRadius;
	Orientation orientation;
public:
	CylinderDTO();

    double GetLength() const;
    Orientation GetOrientation() const;
    double GetOuterRadius() const;
    double GetInnerRadius() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetLength(double length);
    void SetOrientation(Orientation orientation);
    void SetOuterRadius(double radius);
    void SetInnerRadius(double radius);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

    virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();

	virtual ~CylinderDTO();
};

#endif /* CYLINDERDTO_H_ */
