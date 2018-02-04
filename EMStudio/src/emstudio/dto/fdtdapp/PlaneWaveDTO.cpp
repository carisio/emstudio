/*
 * PlaneWaveDTO.cpp
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#include "PlaneWaveDTO.h"

PlaneWaveDTO::PlaneWaveDTO() {

}

Excitation& PlaneWaveDTO::GetExcitation() {
    return excitation;
}

double PlaneWaveDTO::GetPhi() const {
    return phi;
}

double PlaneWaveDTO::GetPsi() const {
    return psi;
}

double PlaneWaveDTO::GetTheta() const {
    return theta;
}

double PlaneWaveDTO::GetXmax() const {
    return xmax;
}

double PlaneWaveDTO::GetXmin() const {
    return xmin;
}

double PlaneWaveDTO::GetYmax() const {
    return ymax;
}

double PlaneWaveDTO::GetYmin() const {
    return ymin;
}

double PlaneWaveDTO::GetZmax() const {
    return zmax;
}

double PlaneWaveDTO::GetZmin() const {
    return zmin;
}

//bool PlaneWaveDTO::IsHardSource() const {
//    return hardSource;
//}

void PlaneWaveDTO::SetExcitation(Excitation excitation) {
    this->excitation = excitation;
}

//void PlaneWaveDTO::SetHardSource(bool hardSource) {
//    this->hardSource = hardSource;
//}

void PlaneWaveDTO::SetPhi(double phi) {
    this->phi = phi;
}

void PlaneWaveDTO::SetPsi(double psi) {
    this->psi = psi;
}

void PlaneWaveDTO::SetTheta(double theta) {
    this->theta = theta;
}

void PlaneWaveDTO::SetXmax(double xmax) {
    this->xmax = xmax;
}

void PlaneWaveDTO::SetXmin(double xmin) {
    this->xmin = xmin;
}

void PlaneWaveDTO::SetYmax(double ymax) {
    this->ymax = ymax;
}

void PlaneWaveDTO::SetYmin(double ymin) {
    this->ymin = ymin;
}

void PlaneWaveDTO::SetZmax(double zmax) {
    this->zmax = zmax;
}

void PlaneWaveDTO::SetZmin(double zmin) {
    this->zmin = zmin;
}

PlaneWaveDTO::~PlaneWaveDTO() {

}

wxString PlaneWaveDTO::GetDTOClassName() {
	return "PlaneWaveDTO";
}

void PlaneWaveDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
//	double frequency = units.GetUserDefinedFrequencyUnit().second;

	excitation.Unnormalize(units);
	SetXmin(GetXmin() * space);
	SetYmin(GetYmin() * space);
	SetZmin(GetZmin() * space);
	SetXmax(GetXmax() * space);
	SetYmax(GetYmax() * space);
	SetZmax(GetZmax() * space);
}

Priority PlaneWaveDTO::GetPriority() {
	Priority p;
	p.SetValue(HIGH);
	return p;
}
