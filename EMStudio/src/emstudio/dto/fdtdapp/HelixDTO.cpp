/*
 * HelixDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "HelixDTO.h"

HelixDTO::HelixDTO() {

}

double HelixDTO::GetHelixRadius() const {
    return helixRadius;
}

double HelixDTO::GetLength() const {
    return length;
}

Orientation HelixDTO::GetOrientation() const {
    return orientation;
}

double HelixDTO::GetStartAngle() const {
    return startAngle;
}

double HelixDTO::GetTurnSeparation() const {
    return turnSeparation;
}

double HelixDTO::GetTurns() const {
    return turns;
}

double HelixDTO::GetWireRadius() const {
    return wireRadius;
}

double HelixDTO::GetX() const {
    return x;
}

double HelixDTO::GetY() const {
    return y;
}

double HelixDTO::GetZ() const {
    return z;
}

void HelixDTO::SetHelixRadius(double helixRadius) {
    this->helixRadius = helixRadius;
}

void HelixDTO::SetLength(double length) {
    this->length = length;
}

void HelixDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void HelixDTO::SetStartAngle(double startAngle) {
    this->startAngle = startAngle;
}

void HelixDTO::SetTurnSeparation(double turnSeparation) {
    this->turnSeparation = turnSeparation;
}

void HelixDTO::SetTurns(double turns) {
    this->turns = turns;
}

void HelixDTO::SetWireRadius(double wireRadius) {
    this->wireRadius = wireRadius;
}

void HelixDTO::SetX(double x) {
    this->x = x;
}

void HelixDTO::SetY(double y) {
    this->y = y;
}

void HelixDTO::SetZ(double z) {
    this->z = z;
}

HelixDTO::~HelixDTO() {
}

wxString HelixDTO::GetDTOClassName() {
	return "HelixDTO";
}

void HelixDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetLength(GetLength() * space);
	SetTurnSeparation(GetTurnSeparation() * space);
	SetHelixRadius(GetHelixRadius() * space);
	SetWireRadius(GetWireRadius() * space);
}
