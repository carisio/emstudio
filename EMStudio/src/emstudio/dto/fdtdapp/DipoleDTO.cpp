/*
 * DipoleDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "DipoleDTO.h"

DipoleDTO::DipoleDTO() {

}

Orientation DipoleDTO::GetOrientation() const {
	return orientation;
}
Excitation& DipoleDTO::GetExcitation() {
    return excitation;
}

double DipoleDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int DipoleDTO::GetNFrequency() const {
    return nFrequency;
}

double DipoleDTO::GetInitialFrequency() const {
    return initialFrequency;
}

double DipoleDTO::GetLength() const {
    return length;
}

double DipoleDTO::GetLineImpedance() const {
    return lineImpedance;
}

int DipoleDTO::GetLinePoints() const {
    return linePoints;
}

int DipoleDTO::GetSourcePoints() const {
    return sourcePoints;
}

double DipoleDTO::GetWireRadius() const {
    return wireRadius;
}

double DipoleDTO::GetX() const {
    return x;
}

double DipoleDTO::GetY() const {
    return y;
}

double DipoleDTO::GetZ() const {
    return z;
}

void DipoleDTO::SetOrientation(Orientation o) {
	this->orientation = o;
}

void DipoleDTO::SetExcitation(Excitation e) {
    this->excitation = e;
}

void DipoleDTO::SetFrequencyStep(double finalFrequency) {
    this->frequencyStep = finalFrequency;
}

void DipoleDTO::SetNFrequency(int frequency) {
    nFrequency = frequency;
}

void DipoleDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

void DipoleDTO::SetLength(double length) {
    this->length = length;
}

void DipoleDTO::SetLineImpedance(double lineImpedance) {
    this->lineImpedance = lineImpedance;
}

void DipoleDTO::SetLinePoints(int linePoints) {
    this->linePoints = linePoints;
}

void DipoleDTO::SetSourcePoints(int sourcePoints) {
    this->sourcePoints = sourcePoints;
}

void DipoleDTO::SetWireRadius(double wireRadius) {
    this->wireRadius = wireRadius;
}

void DipoleDTO::SetX(double x) {
    this->x = x;
}

void DipoleDTO::SetY(double y) {
    this->y = y;
}

void DipoleDTO::SetZ(double z) {
    this->z = z;
}

wxString DipoleDTO::GetDTOClassName() {
	return "DipoleDTO";
}

void DipoleDTO::DoUnnormalize(Units units) {
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

DipoleDTO::~DipoleDTO() {

}

Priority DipoleDTO::GetPriority() {
	Priority p;
	p.SetValue(HIGH);
	return p;
}
