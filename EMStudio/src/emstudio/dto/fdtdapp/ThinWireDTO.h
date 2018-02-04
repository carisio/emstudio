/*
 * ThinWireDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef THINWIREDTO_H_
#define THINWIREDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"

class ThinWireDTO : public ElementsWithFacetsDTO {
private:
	double x; double y; double z; double length; double radius;
	Orientation orientation;
public:
	ThinWireDTO();

    double GetLength() const;
    Orientation GetOrientation() const;
    double GetRadius() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetLength(double length);
    void SetOrientation(Orientation orientation);
    void SetRadius(double radius);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

    virtual Priority GetPriority();
    virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual ~ThinWireDTO();
};

#endif /* THINWIREDTO_H_ */
