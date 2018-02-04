/*
 * GenericSheet.h
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEET_H_
#define GENERICSHEET_H_

#include "BaseType.h"
#include <vector>

class GenericSheet : public BaseType {
private:
	enum SheetCutAtPlane{XY, YZ, ZX};
	/* Representa o plano em que a placa est� */
	int plane;
	/* Representa as coordenadas da placa.
	 *
	 * As coordenadas s�o representadas da seguinte forma:
	 * Se o corte � em x, as coordenadas s�o dadas em (y, z);
	 * Se o corte � em y, as coordenadas s�o dadas em (x, z);
	 * Se o corte � em z, as coordenadas s�o dadas em (x, y);
	 */
	std::vector<std::pair<double, double> > coordinates;

	double cutAt;

public:
	GenericSheet();
	virtual ~GenericSheet();

	/* M�todos acessores para as coordenadas da placa */
	std::vector<std::pair<double, double> > GetCoordinates();
	void SetCoordinates(std::vector<std::pair<double, double> >);

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
};

#endif /* GENERICSHEET_H_ */
