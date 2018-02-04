/*
 * MaterialCoefficients.h
 *
 *  Created on: 23/04/2012
 *      Author: leandrocarisio
 */

#ifndef MATERIALCOEFFICIENTS_H_
#define MATERIALCOEFFICIENTS_H_

#include "emstudio/gui/basetypes/Material.h"
#include "wx/wx.h"

class MaterialCoefficients {
private:
	Material material;

	double gax;
	double gay;
	double gaz;

	double gbx;
	double gby;
	double gbz;
public:
	MaterialCoefficients(Material& m, double deltaT);
	virtual ~MaterialCoefficients();

	const double& GetGax() const;
	const double& GetGay() const;
	const double& GetGaz() const;
	const double& GetGbx() const;
	const double& GetGby() const;
	const double& GetGbz() const;

	const Material& GetMaterial() const;
	wxString GetName();
};

#endif /* MATERIALCOEFFICIENTS_H_ */
