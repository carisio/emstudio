/*
 * RectangularTubeDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef RECTANGULARTUBEDTO_H_
#define RECTANGULARTUBEDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"

class RectangularTubeDTO : public ElementsWithFacetsDTO {
private:
	double x; double y; double z;
	double length;
	double baseInnerHeight; double baseOutterHeight; double baseInnerWidth; double baseOutterWidth;
	double topInnerHeight; double topOutterHeight; double topInnerWidth; double topOutterWidth;
	Orientation orientation;
public:
	RectangularTubeDTO();

	virtual wxString GetDTOClassName();
	virtual void DoUnnormalize(Units units);



	virtual ~RectangularTubeDTO();

    double GetBaseInnerHeight() const;
    double GetBaseInnerWidth() const;
    double GetBaseOutterHeight() const;
    double GetBaseOutterWidth() const;
    double GetLength() const;
    Orientation GetOrientation() const;
    double GetTopInnerHeight() const;
    double GetTopInnerWidth() const;
    double GetTopOutterHeight() const;
    double GetTopOutterWidth() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetBaseInnerHeight(double baseInnerHeight);
    void SetBaseInnerWidth(double baseInnerWidth);
    void SetBaseOutterHeight(double baseOutterHeight);
    void SetBaseOutterWidth(double baseOutterWidth);
    void SetLength(double length);
    void SetOrientation(Orientation orientation);
    void SetTopInnerHeight(double topInnerHeight);
    void SetTopInnerWidth(double topInnerWidth);
    void SetTopOutterHeight(double topOutterHeight);
    void SetTopOutterWidth(double topOutterWidth);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
};

#endif /* RECTANGULARTUBEDTO_H_ */
