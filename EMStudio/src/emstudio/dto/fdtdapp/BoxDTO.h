/*
 * CubeDTO.h
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#ifndef BOXDTO_H_
#define BOXDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"

class BoxDTO : public ElementsWithFacetsDTO {
private:
	double x1;
	double y1;
	double z1;
	double x2;
	double y2;
	double z2;
	MatchWithPML matchWithPML;

public:
	BoxDTO();

	virtual wxString GetDTOClassName();
	virtual void DoUnnormalize(Units units);

    double GetX1() const;
    double GetX2() const;
    double GetY1() const;
    double GetY2() const;
    double GetZ1() const;
    double GetZ2() const;
    MatchWithPML GetMatchWithPML();

    void SetX1(double x1);
    void SetX2(double x2);
    void SetY1(double y1);
    void SetY2(double y2);
    void SetZ1(double z1);
    void SetZ2(double z2);
    void SetMatchWithPML(MatchWithPML m);

    virtual ~BoxDTO();
};

#endif /* BOXDTO_H_ */
