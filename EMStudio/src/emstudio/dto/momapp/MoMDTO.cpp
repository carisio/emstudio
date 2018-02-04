/*
 * MoMDTO.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "MoMDTO.h"

namespace mom {

MoMDTO::MoMDTO() {

}

MoMDTO::~MoMDTO() {
}

bool MoMDTO::IsUseExtendedThinWireKernel() const {
	return useExtendedThinWireKernel;
}
void MoMDTO::SetUseExtendedThinWireKernel(bool use) {
	useExtendedThinWireKernel = use;
}
double MoMDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int MoMDTO::GetNFrequency() const {
    return nFrequency;
}

double MoMDTO::GetInitialFrequency() const {
    return initialFrequency;
}


void MoMDTO::SetFrequencyStep(double frequencyStep) {
    this->frequencyStep = frequencyStep;
}

void MoMDTO::SetNFrequency(int nFrequency) {
    this->nFrequency = nFrequency;
}

void MoMDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}
wxString MoMDTO::GetDTOClassName() {
	return "mom::MoMDTO";
}
void MoMDTO::DoUnnormalize(Units units) {
	// No caso do NEC, espera-se que os dados de frequência sejam informados em MHz para a camada Core.
	double frequency = units.GetUserDefinedFrequencyUnit().second;

	SetInitialFrequency(GetInitialFrequency() * frequency / 1e6);
	SetFrequencyStep(GetFrequencyStep() * frequency  / 1e6);

	double space = units.GetUserDefinedSpaceUnit().second;
	SetDistBelowGround(GetDistBelowGround() * space);
	SetDistFromOrigin(GetDistFromOrigin() * space);
	SetWireLength(GetWireLength() * space);
	SetWireRadius(GetWireRadius() * space);
}

bool MoMDTO::IsCircularCliff() const {
	return circularCliff;
}

void MoMDTO::SetCircularCliff(bool circularCliff) {
	this->circularCliff = circularCliff;
}

bool MoMDTO::IsCurrentsGoToZero() const {
	return currentsGoToZero;
}

void MoMDTO::SetCurrentsGoToZero(bool currentsGoToZero) {
	this->currentsGoToZero = currentsGoToZero;
}

bool MoMDTO::IsCurrentsInterpolated() const {
	return currentsInterpolated;
}

void MoMDTO::SetCurrentsInterpolated(bool currentsInterpolated) {
	this->currentsInterpolated = currentsInterpolated;
}

double MoMDTO::GetDistBelowGround() const {
	return distBelowGround;
}

void MoMDTO::SetDistBelowGround(double distBelowGround) {
	this->distBelowGround = distBelowGround;
}

double MoMDTO::GetDistFromOrigin() const {
	return distFromOrigin;
}

void MoMDTO::SetDistFromOrigin(double distFromOrigin) {
	this->distFromOrigin = distFromOrigin;
}

bool MoMDTO::HasMedium1() const {
	return hasMedium1;
}

void MoMDTO::SetHasMedium1(bool hasMedium1) {
	this->hasMedium1 = hasMedium1;
}

bool MoMDTO::HasMedium2() const {
	return hasMedium2;
}

void MoMDTO::SetHasMedium2(bool hasMedium2) {
	this->hasMedium2 = hasMedium2;
}

bool MoMDTO::IsLinearCliff() const {
	return linearCliff;
}

void MoMDTO::SetLinearCliff(bool linearCliff) {
	this->linearCliff = linearCliff;
}

int MoMDTO::GetNumberOfRadials() const {
	return numberOfRadials;
}

void MoMDTO::SetNumberOfRadials(int numberOfRadials) {
	this->numberOfRadials = numberOfRadials;
}

double MoMDTO::GetWireLength() const {
	return wireLength;
}

void MoMDTO::SetWireLength(double wireLength) {
	this->wireLength = wireLength;
}

double MoMDTO::GetWireRadius() const {
	return wireRadius;
}

void MoMDTO::SetWireRadius(double wireRadius) {
	this->wireRadius = wireRadius;
}

Material MoMDTO::GetMedium1() {
	return medium1;
}

void MoMDTO::SetMedium1(Material medium1) {
	this->medium1 = medium1;
}

Material MoMDTO::GetMedium2() {
	return medium2;
}

void MoMDTO::SetMedium2(Material medium2) {
	this->medium2 = medium2;
}

} /* namespace mom */
