/*
 * Sheet.h
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#ifndef SHEET_H_
#define SHEET_H_

#include "BaseType.h"

class Sheet : public BaseType {
private:
	enum SheetCutAtPlane{XY, YZ, ZX};
	/* Representa o plano em que a placa está */
	int plane;
	/* Representa as coordenadas da placa. */
	double x0, y0, z0, x1, y1, z1;

public:
	Sheet();

	/* Métodos acessores para as coordenadas da placa */
	double GetX0();
	double GetY0();
	double GetZ0();
	double GetX1();
	double GetY1();
	double GetZ1();
	void SetX0(double x);
	void SetY0(double y);
	void SetZ0(double z);
	void SetX1(double x);
	void SetY1(double y);
	void SetZ1(double z);
	bool IsCutAtX();
	bool IsCutAtY();
	bool IsCutAtZ();
	void SetCutAtX(double x);
	void SetCutAtY(double y);
	void SetCutAtZ(double z);
	double GetCutAt();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	virtual ~Sheet();
};

#endif /* SHEET_H_ */
