/*
 * FDTDDTO.h
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#ifndef FDTDDTO_H_
#define FDTDDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/gui/basetypes/AbsorvingBoundaryCondition.h"
#include "emstudio/units/Units.h"

class FDTDDTO : public ElementsWithFacetsDTO {
private:
	double xmin;
	double ymin;
	double zmin;
	double xmax;
	double ymax;
	double zmax;
	int xcells;
	int ycells;
	int zcells;
	int timesteps;
	double deltaT;
	AbsorvingBoundaryCondition abc;
	bool smoothMesh;

public:
	FDTDDTO();
	virtual wxString GetDTOClassName();
	virtual ~FDTDDTO();

	virtual void DoUnnormalize(Units units);

    AbsorvingBoundaryCondition GetABC() const;
    double GetDeltaT() const;
    int GetTimesteps() const;
    int GetXcells() const;
    double GetXmax() const;
    double GetXmin() const;
    int GetYcells() const;
    double GetYmax() const;
    double GetYmin() const;
    int GetZcells() const;
    double GetZmax() const;
    double GetZmin() const;
    int GetNpml();
    bool IsSmoothMesh() const;
    void SetABC(AbsorvingBoundaryCondition abc);
    void SetDeltaT(double deltaT);
    void SetTimesteps(int timesteps);
    void SetXcells(int xcells);
    void SetXmax(double xmax);
    void SetXmin(double xmin);
    void SetYcells(int ycells);
    void SetYmax(double ymax);
    void SetYmin(double ymin);
    void SetZcells(int zcells);
    void SetZmax(double zmax);
    void SetZmin(double zmin);
    void SetNpml(int npml);
    void SetSmoothMesh(bool smoothMesh);
};

#endif /* FDTDDTO_H_ */
