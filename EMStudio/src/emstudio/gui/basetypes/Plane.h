/*
 * Plane.h
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "wx/wx.h"
#include "IntWrapper.h"
#include "wx/arrstr.h"

enum PlaneType{XY, XZ, YZ};

class Plane : public IntWrapper {
public:
	Plane();

	static wxArrayString GetPossibleOrientations();

	virtual wxString GetUserFriendlyStringRepresentation();
	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetBaseTypeClassName();

	virtual ~Plane();
};

#endif /* PLANE_H_ */
