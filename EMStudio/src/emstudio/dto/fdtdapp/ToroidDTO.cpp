/*
 * ToroidDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "ToroidDTO.h"

ToroidDTO::ToroidDTO() {

}

ToroidDTO::~ToroidDTO() {

}

wxString ToroidDTO::GetDTOClassName() {
	return "ToroidDTO";
}

double ToroidDTO::GetToroidRadius() const {
    return toroidRadius;
}

Orientation ToroidDTO::GetOrientation() const {
    return orientation;
}

double ToroidDTO::GetWireRadius() const {
    return wireRadius;
}

double ToroidDTO::GetX() const {
    return x;
}

double ToroidDTO::GetY() const {
    return y;
}

double ToroidDTO::GetZ() const {
    return z;
}

void ToroidDTO::SetToroidRadius(double toroidRadius) {
    this->toroidRadius = toroidRadius;
}

void ToroidDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void ToroidDTO::SetWireRadius(double wireRadius) {
    this->wireRadius = wireRadius;
}

void ToroidDTO::SetX(double x) {
    this->x = x;
}

void ToroidDTO::SetY(double y) {
    this->y = y;
}

void ToroidDTO::SetZ(double z) {
    this->z = z;
}

void ToroidDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetWireRadius(GetWireRadius() * space);
	SetToroidRadius(GetToroidRadius() * space);
}
