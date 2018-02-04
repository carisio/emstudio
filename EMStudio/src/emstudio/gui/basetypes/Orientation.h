/*
 * Orientation.h
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include "IntWrapper.h"
#include "wx/wx.h"
#include "wx/arrstr.h"

enum OrientationType{X, Y, Z};

class Orientation : public IntWrapper {
public:
	Orientation();

	static wxArrayString GetPossibleOrientations();

	virtual wxString GetUserFriendlyStringRepresentation();
	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetBaseTypeClassName();

	virtual ~Orientation();
};

#endif /* ORIENTATION_H_ */
