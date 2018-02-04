/*
 * DirectionPlaneWave.h
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVE_H_
#define DIRECTIONPLANEWAVE_H_

#include "BaseType.h"

class DirectionPlaneWave : public BaseType {
private:
	double theta;
	double phi;
	double psi;
public:
	DirectionPlaneWave();
	virtual ~DirectionPlaneWave();

	double GetTheta();
	double GetPhi();
	double GetPsi();
	void SetTheta(double d);
	void SetPhi(double d);
	void SetPsi(double d);

	virtual void Copy(BaseType* b);
	virtual wxString  GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* DIRECTIONPLANEWAVE_H_ */
