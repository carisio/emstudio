/*
 * ThinWireDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "ThinWireDTO.h"

ThinWireDTO::ThinWireDTO() {

}

double ThinWireDTO::GetLength() const {
    return length;
}

Orientation ThinWireDTO::GetOrientation() const {
    return orientation;
}

double ThinWireDTO::GetRadius() const {
    return radius;
}

double ThinWireDTO::GetX() const {
    return x;
}

double ThinWireDTO::GetY() const {
    return y;
}

double ThinWireDTO::GetZ() const {
    return z;
}

void ThinWireDTO::SetLength(double length) {
    this->length = length;
}

void ThinWireDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void ThinWireDTO::SetRadius(double radius) {
    this->radius = radius;
}

void ThinWireDTO::SetX(double x) {
    this->x = x;
}

void ThinWireDTO::SetY(double y) {
    this->y = y;
}

void ThinWireDTO::SetZ(double z) {
    this->z = z;
}

ThinWireDTO::~ThinWireDTO() {

}

wxString ThinWireDTO::GetDTOClassName() {
	return "ThinWireDTO";
}
Priority ThinWireDTO::GetPriority() {
	Priority p;
	p.SetValue(MEDIUM);
	return p;
}
void ThinWireDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetLength(GetLength() * space);
	SetRadius(GetRadius() * space);
}
