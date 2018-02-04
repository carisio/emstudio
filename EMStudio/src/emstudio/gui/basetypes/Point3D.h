/*
 * Point3D.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include "BaseType.h"

class Point3D : public BaseType {
private:
	double x, y, z;
public:
	Point3D();
	virtual ~Point3D();

	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);
	double GetX() const;
	double GetY() const;
	double GetZ() const;

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* POINT3D_H_ */
