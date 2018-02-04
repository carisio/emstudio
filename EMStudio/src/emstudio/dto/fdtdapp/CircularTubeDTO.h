/*
 * CircularTubeDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef CIRCULARTUBEDTO_H_
#define CIRCULARTUBEDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"

class CircularTubeDTO : public ElementsWithFacetsDTO {
private:
	double x; double y; double z; double length;  double bottomRadius; double topRadius; double thickness;
	Orientation orientation;
public:
	CircularTubeDTO();
	virtual wxString GetDTOClassName();


	virtual void DoUnnormalize(Units units);
	virtual ~CircularTubeDTO();


    double GetBottomRadius() const;
    double GetLength() const;
    Orientation GetOrientation() const;
    double GetThickness() const;
    double GetTopRadius() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetBottomRadius(double bottomRadius);
    void SetLength(double length);
    void SetOrientation(Orientation orientation);
    void SetThickness(double thickness);
    void SetTopRadius(double topRadius);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
};

#endif /* CIRCULARTUBEDTO_H_ */
