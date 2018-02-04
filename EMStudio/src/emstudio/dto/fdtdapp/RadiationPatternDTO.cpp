/*
 * RadiationPatternDTO.cpp
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#include "RadiationPatternDTO.h"

RadiationPatternDTO::RadiationPatternDTO() {

}

RadiationPatternDTO::~RadiationPatternDTO() {
}

wxString RadiationPatternDTO::GetDTOClassName() {
	return "RadiationPatternDTO";
}
Priority RadiationPatternDTO::GetPriority() {
	Priority p;
	p.SetValue(MAXIMUM+1);
	return p;
}
void RadiationPatternDTO::DoUnnormalize(Units units) {
	double frequency = units.GetUserDefinedFrequencyUnit().second;
	double space = units.GetUserDefinedSpaceUnit().second;

	SetInitialFrequency(GetInitialFrequency() * frequency);
	SetFrequencyStep(GetFrequencyStep() * frequency);

	SetXmin(GetXmin() * space);
	SetYmin(GetYmin() * space);
	SetZmin(GetZmin() * space);
	SetXmax(GetXmax() * space);
	SetYmax(GetYmax() * space);
	SetZmax(GetZmax() * space);
}

double RadiationPatternDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int RadiationPatternDTO::GetNFrequency() const {
    return nFrequency;
}

double RadiationPatternDTO::GetInitialFrequency() const {
    return initialFrequency;
}


void RadiationPatternDTO::SetFrequencyStep(double frequencyStep) {
    this->frequencyStep = frequencyStep;
}

void RadiationPatternDTO::SetNFrequency(int nFrequency) {
    this->nFrequency = nFrequency;
}

void RadiationPatternDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

void RadiationPatternDTO::SetXmax(double xmax) {
    this->xmax = xmax;
}

void RadiationPatternDTO::SetXmin(double xmin) {
    this->xmin = xmin;
}

void RadiationPatternDTO::SetYmax(double ymax) {
    this->ymax = ymax;
}

void RadiationPatternDTO::SetYmin(double ymin) {
    this->ymin = ymin;
}

void RadiationPatternDTO::SetZmax(double zmax) {
    this->zmax = zmax;
}

void RadiationPatternDTO::SetZmin(double zmin) {
    this->zmin = zmin;
}
double RadiationPatternDTO::GetXmax() const {
    return xmax;
}

double RadiationPatternDTO::GetXmin() const {
    return xmin;
}

double RadiationPatternDTO::GetYmax() const {
    return ymax;
}

double RadiationPatternDTO::GetYmin() const {
    return ymin;
}

double RadiationPatternDTO::GetZmax() const {
    return zmax;
}

double RadiationPatternDTO::GetZmin() const {
    return zmin;
}
