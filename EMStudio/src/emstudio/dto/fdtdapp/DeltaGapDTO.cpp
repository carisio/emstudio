/*
 * DeltaGapDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "DeltaGapDTO.h"

DeltaGapDTO::DeltaGapDTO() {

}

Excitation& DeltaGapDTO::GetExcitation() {
    return excitation;
}

double DeltaGapDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int DeltaGapDTO::GetNFrequency() const {
    return nFrequency;
}

double DeltaGapDTO::GetInitialFrequency() const {
    return initialFrequency;
}

Orientation DeltaGapDTO::GetOrientation() const {
    return orientation;
}

//double DeltaGapDTO::GetResistance() const {
//    return resistance;
//}

double DeltaGapDTO::GetX() const {
    return x;
}

double DeltaGapDTO::GetY() const {
    return y;
}

double DeltaGapDTO::GetZ() const {
    return z;
}

//bool DeltaGapDTO::IsResistiveSource() const {
//    return resistiveSource;
//}

void DeltaGapDTO::SetExcitation(Excitation excitation) {
    this->excitation = excitation;
}

void DeltaGapDTO::SetFrequencyStep(double frequencyStep) {
    this->frequencyStep = frequencyStep;
}

void DeltaGapDTO::SetNFrequency(int nFrequency) {
    this->nFrequency = nFrequency;
}

//void DeltaGapDTO::SetResistiveSource(bool b) {
//    this->resistiveSource = b;
//}

void DeltaGapDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

void DeltaGapDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

//void DeltaGapDTO::SetResistance(double resistance) {
//    this->resistance = resistance;
//}

void DeltaGapDTO::SetX(double x) {
    this->x = x;
}

void DeltaGapDTO::SetY(double y) {
    this->y = y;
}

void DeltaGapDTO::SetZ(double z) {
    this->z = z;
}

DeltaGapDTO::~DeltaGapDTO() {
}
Priority DeltaGapDTO::GetPriority() {
	Priority p;
	p.SetValue(HIGH);
	return p;
}
wxString DeltaGapDTO::GetDTOClassName() {
	return "DeltaGapDTO";
}
void DeltaGapDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	double frequency = units.GetUserDefinedFrequencyUnit().second;

	excitation.Unnormalize(units);
	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetInitialFrequency(GetInitialFrequency() * frequency);
	SetFrequencyStep(GetFrequencyStep() * frequency);
}
