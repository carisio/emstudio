/*
 * FDTDDTO.cpp
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#include "FDTDDTO.h"
#include "emstudio/util/constants/Constants.h"

FDTDDTO::FDTDDTO() {

}

void FDTDDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
//	double time = units.GetUserDefinedTimeUnit().second;

	SetXmin(GetXmin() * space);
	SetYmin(GetYmin() * space);
	SetZmin(GetZmin() * space);
	SetXmax(GetXmax() * space);
	SetYmax(GetYmax() * space);
	SetZmax(GetZmax() * space);

	// TODO: O CÁLCULO ABAIXO APENAS FUNCIONA PARA GRIDS UNIFORMES.
	double dx = (GetXmax() - GetXmin())/GetXcells();
	double dy = (GetYmax() - GetYmin())/GetYcells();
	double dz = (GetZmax() - GetZmin())/GetZcells();
	double min = dx;

    if (dy < min)
    	min = dy;
    if (dz < min)
    	min = dz;
    double deltaT = min/(2.*SPEED_OF_LIGHT_VACUUM);

    SetDeltaT(deltaT);
}

AbsorvingBoundaryCondition FDTDDTO::GetABC() const {
    return abc;
}

double FDTDDTO::GetDeltaT() const {
    return deltaT;
}

int FDTDDTO::GetTimesteps() const {
    return timesteps;
}

int FDTDDTO::GetXcells() const {
    return xcells;
}

double FDTDDTO::GetXmax() const {
    return xmax;
}

double FDTDDTO::GetXmin() const {
    return xmin;
}

int FDTDDTO::GetYcells() const {
    return ycells;
}

double FDTDDTO::GetYmax() const {
    return ymax;
}

double FDTDDTO::GetYmin() const {
    return ymin;
}

int FDTDDTO::GetZcells() const {
    return zcells;
}

double FDTDDTO::GetZmax() const {
    return zmax;
}

double FDTDDTO::GetZmin() const {
    return zmin;
}
int FDTDDTO::GetNpml() {
	return abc.GetNpml();
}

void FDTDDTO::SetABC(AbsorvingBoundaryCondition abc) {
    this->abc = abc;
}

void FDTDDTO::SetDeltaT(double deltaT) {
    this->deltaT = deltaT;
}

void FDTDDTO::SetTimesteps(int timesteps) {
    this->timesteps = timesteps;
}

void FDTDDTO::SetXcells(int xcells) {
    this->xcells = xcells;
}

void FDTDDTO::SetXmax(double xmax) {
    this->xmax = xmax;
}

void FDTDDTO::SetYcells(int ycells) {
    this->ycells = ycells;
}

void FDTDDTO::SetYmax(double ymax) {
    this->ymax = ymax;
}

void FDTDDTO::SetYmin(double ymin) {
    this->ymin = ymin;
}

void FDTDDTO::SetZcells(int zcells) {
    this->zcells = zcells;
}

void FDTDDTO::SetZmax(double zmax) {
    this->zmax = zmax;
}

void FDTDDTO::SetZmin(double zmin) {
    this->zmin = zmin;
}

void FDTDDTO::SetXmin(double xmin) {
    this->xmin = xmin;
}

bool FDTDDTO::IsSmoothMesh() const {
	return smoothMesh;
}

void FDTDDTO::SetSmoothMesh(bool smoothMesh) {
	this->smoothMesh = smoothMesh;
}
FDTDDTO::~FDTDDTO() {
}

wxString FDTDDTO::GetDTOClassName() {
	return "FDTDDTO";
}
