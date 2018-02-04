/*
 * RectangularSheetDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef PECSHEETDTO_H_
#define PECSHEETDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"

class RectangularPECSheetDTO : public ElementsWithFacetsDTO {
private:
	bool cutAtX, cutAtY, cutAtZ;
	double cutAt, x0, y0, z0, x1, y1, z1;
	MatchWithPML matchWithPML;

public:
	RectangularPECSheetDTO();

	void SetCutAtX(bool b);
	void SetCutAtY(bool b);
	void SetCutAtZ(bool b);
	void SetCutAt(double d);
	void SetX0(double d);
	void SetY0(double d);
	void SetZ0(double d);
	void SetX1(double d);
	void SetY1(double d);
	void SetZ1(double d);
	void SetMatchWithPML(MatchWithPML m);

	bool IsCutAtX();
	bool IsCutAtY();
	bool IsCutAtZ();
	double GetCutAt();
	double GetX0();
	double GetY0();
	double GetZ0();
	double GetX1();
	double GetY1();
	double GetZ1();
	MatchWithPML GetMatchWithPML();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual Priority GetPriority();

	virtual ~RectangularPECSheetDTO();

//	Material GetMaterial();
//  void SetMaterial(Material material);
};

#endif /* PECSHEETDTO_H_ */
