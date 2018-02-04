/*
 * GeneralSourceDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "MicrostripDTO.h"

MicrostripDTO::MicrostripDTO() {

}

MicrostripDTO::~MicrostripDTO() {

}

wxString MicrostripDTO::GetDTOClassName() {
	return "MicrostripDTO";
}

void MicrostripDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	double frequency = units.GetUserDefinedFrequencyUnit().second;

	SetX1(GetX1() * space);
	SetY1(GetY1() * space);
	SetZ1(GetZ1() * space);
	SetX2(GetX2() * space);
	SetY2(GetY2() * space);
	SetZ2(GetZ2() * space);

	excitation.Unnormalize(units);
	SetInitialFrequency(GetInitialFrequency() * frequency);
	SetFrequencyStep(GetFrequencyStep() * frequency);

	SetLinePositionX(GetLinePositionX() * space);
	SetLineWidth(GetLineWidth() * space);
	SetLineLength(GetLineLength() * space);


	vector<pair<double, double> > coord = ports.GetCoordinates();
	vector<pair<double, double> > newCoordinates;

	for (size_t i = 0; i < coord.size(); i++) {
		pair<double, double> newPair(coord[i].first*space, coord[i].second*space);
		newCoordinates.push_back(newPair);
	}
	ports.SetCoordinates(newCoordinates);
}

double MicrostripDTO::GetX1() const {
    return x1;
}

double MicrostripDTO::GetX2() const {
    return x2;
}

double MicrostripDTO::GetY1() const {
    return y1;
}

double MicrostripDTO::GetY2() const {
    return y2;
}

double MicrostripDTO::GetZ1() const {
    return z1;
}

double MicrostripDTO::GetZ2() const {
    return z2;
}

void MicrostripDTO::SetX1(double x1) {
    this->x1 = x1;
}

void MicrostripDTO::SetX2(double x2) {
    this->x2 = x2;
}

void MicrostripDTO::SetY1(double y1) {
    this->y1 = y1;
}

void MicrostripDTO::SetY2(double y2) {
    this->y2 = y2;
}

void MicrostripDTO::SetZ1(double z1) {
    this->z1 = z1;
}

void MicrostripDTO::SetZ2(double z2) {
    this->z2 = z2;
}

void MicrostripDTO::SetExcitation(Excitation e) {
    this->excitation = e;
}

void MicrostripDTO::SetFrequencyStep(double frequencyStep) {
    this->frequencyStep = frequencyStep;
}

void MicrostripDTO::SetNFrequency(int frequency) {
    nFrequency = frequency;
}

void MicrostripDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

Excitation& MicrostripDTO::GetExcitation() {
    return excitation;
}

double MicrostripDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int MicrostripDTO::GetNFrequency() const {
    return nFrequency;
}

double MicrostripDTO::GetInitialFrequency() const {
    return initialFrequency;
}

double MicrostripDTO::GetLinePositionX() const {
	return linePositionX;
}
double MicrostripDTO::GetLineLength() const {
	return lineLength;
}
double MicrostripDTO::GetLineWidth() const {
	return lineWidth;
}
void MicrostripDTO::SetLinePositionX(double linePosition) {
	this->linePositionX = linePosition;
}
void MicrostripDTO::SetLineLength(double lineLength) {
	this->lineLength = lineLength;
}
void MicrostripDTO::SetLineWidth(double lineWidth) {
	this->lineWidth = lineWidth;
}

void MicrostripDTO::SetPecUnderSubstrate(bool yn) {
	this->pecUnderSubstrate = yn;
}
bool MicrostripDTO::IsPecUnderSubstrate() {
	return pecUnderSubstrate;
}

double MicrostripDTO::GetLineImpedance() const {
    return lineImpedance;
}

int MicrostripDTO::GetLinePoints() const {
    return linePoints;
}

int MicrostripDTO::GetSourcePoint() const {
    return sourcePoint;
}

void MicrostripDTO::SetLineImpedance(double lineImpedance) {
    this->lineImpedance = lineImpedance;
}

void MicrostripDTO::SetLinePoints(int linePoints) {
    this->linePoints = linePoints;
}

void MicrostripDTO::SetSourcePoint(int sourcePoints) {
    this->sourcePoint = sourcePoints;
}

void MicrostripDTO::SetMatchWithPML(MatchWithPML m) {
	matchWithPML = m;
}

MatchWithPML MicrostripDTO::GetMatchWithPML() {
	return matchWithPML;
}

void MicrostripDTO::SetPorts(MicrostripXYPorts ports) {
	this->ports = ports;
}
MicrostripXYPorts MicrostripDTO::GetPorts() {
	return ports;
}
