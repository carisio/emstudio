/*
 * SphereDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "SphereDTO.h"

SphereDTO::SphereDTO() {

}

SphereDTO::~SphereDTO() {

}

wxString SphereDTO::GetDTOClassName() {
	return "SphereDTO";
}

double SphereDTO::GetOuterRadius() const {
    return outerRadius;
}

double SphereDTO::GetX() const {
    return x;
}

double SphereDTO::GetY() const {
    return y;
}

double SphereDTO::GetZ() const {
    return z;
}

void SphereDTO::SetOuterRadius(double radius) {
    this->outerRadius = radius;
}

void SphereDTO::SetX(double x) {
    this->x = x;
}

void SphereDTO::SetY(double y) {
    this->y = y;
}

void SphereDTO::SetZ(double z) {
    this->z = z;
}

double SphereDTO::GetInnerRadius() const {
    return innerRadius;
}

void SphereDTO::SetInnerRadius(double radius) {
    this->innerRadius = radius;
}

void SphereDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetOuterRadius(GetOuterRadius() * space);
	SetInnerRadius(GetInnerRadius() * space);
}
