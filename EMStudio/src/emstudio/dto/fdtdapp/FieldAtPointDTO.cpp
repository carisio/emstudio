/*
 * FieldAtPointDTO.cpp
 *
 *  Created on: 02/03/2012
 *      Author: Administrador
 */

#include "FieldAtPointDTO.h"

FieldAtPointDTO::FieldAtPointDTO() {

}

double FieldAtPointDTO::GetX() const {
    return x;
}

double FieldAtPointDTO::GetY() const {
    return y;
}

double FieldAtPointDTO::GetZ() const {
    return z;
}

void FieldAtPointDTO::SetX(double x) {
    this->x = x;
}

void FieldAtPointDTO::SetY(double y) {
    this->y = y;
}

void FieldAtPointDTO::SetZ(double z) {
    this->z = z;
}

wxString FieldAtPointDTO::GetDTOClassName() {
	return "FieldAtPointDTO";
}


double FieldAtPointDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int FieldAtPointDTO::GetNFrequency() const {
    return nFrequency;
}

double FieldAtPointDTO::GetInitialFrequency() const {
    return initialFrequency;
}

Priority FieldAtPointDTO::GetPriority() {
	Priority p;
	p.SetValue(MAXIMUM+1);
	return p;
}
void FieldAtPointDTO::SetFrequencyStep(double frequencyStep) {
    this->frequencyStep = frequencyStep;
}

void FieldAtPointDTO::SetNFrequency(int nFrequency) {
    this->nFrequency = nFrequency;
}

void FieldAtPointDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

void FieldAtPointDTO::SetShowTimeResponse(bool t) {
	this->showTimeResponse = t;
}
bool FieldAtPointDTO::IsShowTimeResponse() const {
	return showTimeResponse;
}
void FieldAtPointDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	double frequency = units.GetUserDefinedFrequencyUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);

	SetInitialFrequency(GetInitialFrequency() * frequency);
	SetFrequencyStep(GetFrequencyStep() * frequency);
}

FieldAtPointDTO::~FieldAtPointDTO() {
}

