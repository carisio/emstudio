/*
 * PlaneWaveDTO.h
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#ifndef PLANEWAVEDTO_H_
#define PLANEWAVEDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Excitation.h"

class PlaneWaveDTO : public ElementsWithFacetsDTO {
private:
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	double zmin;
	double zmax;
	double theta;
	double phi;
	double psi;
	Excitation excitation;
//	bool hardSource;

public:
    Excitation& GetExcitation();
    double GetPhi() const;
    double GetPsi() const;
    double GetTheta() const;
    double GetXmax() const;
    double GetXmin() const;
    double GetYmax() const;
    double GetYmin() const;
    double GetZmax() const;
    double GetZmin() const;
//    bool IsHardSource() const;
    void SetExcitation(Excitation excitation);
//    void SetHardSource(bool hardSource);
    void SetPhi(double phi);
    void SetPsi(double psi);
    void SetTheta(double theta);
    void SetXmax(double xmax);
    void SetXmin(double xmin);
    void SetYmax(double ymax);
    void SetYmin(double ymin);
    void SetZmax(double zmax);
    void SetZmin(double zmin);

public:
	PlaneWaveDTO();

	virtual wxString GetDTOClassName();
	virtual void DoUnnormalize(Units units);
	virtual Priority GetPriority();

	virtual ~PlaneWaveDTO();
};

#endif /* PLANEWAVEDTO_H_ */
