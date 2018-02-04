/*
 * CylinderDTO.cpp
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#include "CylinderDTO.h"

CylinderDTO::CylinderDTO() {

}

CylinderDTO::~CylinderDTO() {

}

wxString CylinderDTO::GetDTOClassName() {
	return "CylinderDTO";
}

double CylinderDTO::GetLength() const {
    return length;
}

Orientation CylinderDTO::GetOrientation() const {
    return orientation;
}

double CylinderDTO::GetOuterRadius() const {
    return outerRadius;
}

double CylinderDTO::GetX() const {
    return x;
}

double CylinderDTO::GetY() const {
    return y;
}

double CylinderDTO::GetZ() const {
    return z;
}

void CylinderDTO::SetLength(double length) {
    this->length = length;
}

void CylinderDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void CylinderDTO::SetOuterRadius(double radius) {
    this->outerRadius = radius;
}

void CylinderDTO::SetX(double x) {
    this->x = x;
}

void CylinderDTO::SetY(double y) {
    this->y = y;
}

void CylinderDTO::SetZ(double z) {
    this->z = z;
}

double CylinderDTO::GetInnerRadius() const {
    return innerRadius;
}

void CylinderDTO::SetInnerRadius(double radius) {
    this->innerRadius = radius;
}

void CylinderDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetLength(GetLength() * space);
	SetOuterRadius(GetOuterRadius() * space);
	SetInnerRadius(GetInnerRadius() * space);
}
