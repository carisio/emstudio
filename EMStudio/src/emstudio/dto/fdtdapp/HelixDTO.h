/*
 * HelixDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef HELIXDTO_H_
#define HELIXDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"

class HelixDTO : public ElementsWithFacetsDTO {
private:
	double length;
	double x; double y; double z;
	double turns; double turnSeparation;
	double startAngle;
	double helixRadius; double wireRadius;
	Orientation orientation;
public:
	HelixDTO();

	virtual wxString GetDTOClassName();
	virtual void DoUnnormalize(Units units);

	virtual ~HelixDTO();


    double GetHelixRadius() const;
    double GetLength() const;
    Orientation GetOrientation() const;
    double GetStartAngle() const;
    double GetTurnSeparation() const;
    double GetTurns() const;
    double GetWireRadius() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetHelixRadius(double helixRadius);
    void SetLength(double length);
    void SetOrientation(Orientation orientation);
    void SetStartAngle(double startAngle);
    void SetTurnSeparation(double turnSeparation);
    void SetTurns(double turns);
    void SetWireRadius(double wireRadius);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
};

#endif /* HELIXDTO_H_ */
