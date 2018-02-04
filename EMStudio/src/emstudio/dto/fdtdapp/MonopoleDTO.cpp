/*
 * MonopoleDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "MonopoleDTO.h"

MonopoleDTO::MonopoleDTO() {

}

Excitation& MonopoleDTO::GetExcitation() {
    return excitation;
}

double MonopoleDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int MonopoleDTO::GetNFrequency() const {
    return nFrequency;
}

double MonopoleDTO::GetInitialFrequency() const {
    return initialFrequency;
}

double MonopoleDTO::GetLength() const {
    return length;
}

double MonopoleDTO::GetLineImpedance() const {
    return lineImpedance;
}

int MonopoleDTO::GetLinePoints() const {
    return linePoints;
}

Orientation MonopoleDTO::GetOrientation() const {
    return orientation;
}

int MonopoleDTO::GetSourcePoints() const {
    return sourcePoints;
}

//double MonopoleDTO::GetVelocityFactor() const {
//    return velocityFactor;
//}

double MonopoleDTO::GetWireRadius() const {
    return wireRadius;
}

double MonopoleDTO::GetX() const {
    return x;
}

double MonopoleDTO::GetY() const {
    return y;
}

double MonopoleDTO::GetZ() const {
    return z;
}

void MonopoleDTO::SetExcitation(Excitation excitation) {
    this->excitation = excitation;
}

void MonopoleDTO::SetFrequencyStep(double freqStep) {
    this->frequencyStep = freqStep;
}

void MonopoleDTO::SetNFrequency(int frequency) {
    nFrequency = frequency;
}

void MonopoleDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

void MonopoleDTO::SetLength(double length) {
    this->length = length;
}

void MonopoleDTO::SetLineImpedance(double lineImpedance) {
    this->lineImpedance = lineImpedance;
}

void MonopoleDTO::SetLinePoints(int linePoints) {
    this->linePoints = linePoints;
}

void MonopoleDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void MonopoleDTO::SetSourcePoints(int sourcePoints) {
    this->sourcePoints = sourcePoints;
}
//
//void MonopoleDTO::SetVelocityFactor(double velocityFactor) {
//    this->velocityFactor = velocityFactor;
//}

void MonopoleDTO::SetWireRadius(double wireRadius) {
    this->wireRadius = wireRadius;
}

void MonopoleDTO::SetX(double x) {
    this->x = x;
}

void MonopoleDTO::SetY(double y) {
    this->y = y;
}

void MonopoleDTO::SetZ(double z) {
    this->z = z;
}


MonopoleDTO::~MonopoleDTO() {

}

wxString MonopoleDTO::GetDTOClassName() {
	return "MonopoleDTO";
}

void MonopoleDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	double frequency = units.GetUserDefinedFrequencyUnit().second;

	excitation.Unnormalize(units);

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetLength(GetLength() * space);
	SetWireRadius(GetWireRadius() * space);
	SetInitialFrequency(GetInitialFrequency() * frequency);
	SetFrequencyStep(GetFrequencyStep() * frequency);
}

Priority MonopoleDTO::GetPriority() {
	Priority p;
	p.SetValue(HIGH);
	return p;
}
