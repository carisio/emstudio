/*
 * SphereDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef SPHEREDTO_H_
#define SPHEREDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Material.h"

class SphereDTO : public ElementsWithFacetsDTO {
private:
	double x; double y; double z; double outerRadius; double innerRadius;
public:
	SphereDTO();

    double GetOuterRadius() const;
    double GetInnerRadius() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetOuterRadius(double radius);
    void SetInnerRadius(double radius);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

    virtual void DoUnnormalize(Units units);
    virtual wxString GetDTOClassName();

	virtual ~SphereDTO();
};

#endif /* SPHEREDTO_H_ */
