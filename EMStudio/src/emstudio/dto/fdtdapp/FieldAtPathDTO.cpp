/*
 * FieldAtPathDTO.cpp
 *
 *  Created on: 21/03/2012
 *      Author: Leandro
 */

#include "FieldAtPathDTO.h"

FieldAtPathDTO::FieldAtPathDTO() {

}

FieldAtPathDTO::~FieldAtPathDTO() {
}

wxString FieldAtPathDTO::GetDTOClassName() {
	return "FieldAtPathDTO";
}

double FieldAtPathDTO::GetLength() const {
    return length;
}

Orientation FieldAtPathDTO::GetOrientation() const {
    return orientation;
}

double FieldAtPathDTO::GetX() const {
    return x;
}

double FieldAtPathDTO::GetY() const {
    return y;
}

double FieldAtPathDTO::GetZ() const {
    return z;
}

void FieldAtPathDTO::SetLength(double length) {
    this->length = length;
}

void FieldAtPathDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void FieldAtPathDTO::SetX(double x) {
    this->x = x;
}

void FieldAtPathDTO::SetY(double y) {
    this->y = y;
}

void FieldAtPathDTO::SetZ(double z) {
    this->z = z;
}

Priority FieldAtPathDTO::GetPriority() {
	Priority p;
	p.SetValue(MAXIMUM+1);
	return p;
}
double FieldAtPathDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int FieldAtPathDTO::GetNFrequency() const {
    return nFrequency;
}

double FieldAtPathDTO::GetInitialFrequency() const {
    return initialFrequency;
}


void FieldAtPathDTO::SetFrequencyStep(double frequencyStep) {
    this->frequencyStep = frequencyStep;
}

void FieldAtPathDTO::SetNFrequency(int nFrequency) {
    this->nFrequency = nFrequency;
}

void FieldAtPathDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

void FieldAtPathDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	double frequency = units.GetUserDefinedFrequencyUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetLength(GetLength() * space);

	SetInitialFrequency(GetInitialFrequency() * frequency);
	SetFrequencyStep(GetFrequencyStep() * frequency);
}
