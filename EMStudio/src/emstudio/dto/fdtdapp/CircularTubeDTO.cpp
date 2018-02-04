/*
 * CircularTubeDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "CircularTubeDTO.h"

CircularTubeDTO::CircularTubeDTO() {

}

double CircularTubeDTO::GetBottomRadius() const {
    return bottomRadius;
}

double CircularTubeDTO::GetLength() const {
    return length;
}

Orientation CircularTubeDTO::GetOrientation() const {
    return orientation;
}

double CircularTubeDTO::GetThickness() const {
    return thickness;
}

double CircularTubeDTO::GetTopRadius() const {
    return topRadius;
}

double CircularTubeDTO::GetX() const {
    return x;
}

double CircularTubeDTO::GetY() const {
    return y;
}

double CircularTubeDTO::GetZ() const {
    return z;
}

void CircularTubeDTO::SetBottomRadius(double bottomRadius) {
    this->bottomRadius = bottomRadius;
}

void CircularTubeDTO::SetLength(double length) {
    this->length = length;
}

void CircularTubeDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void CircularTubeDTO::SetThickness(double thickness) {
    this->thickness = thickness;
}

void CircularTubeDTO::SetTopRadius(double topRadius) {
    this->topRadius = topRadius;
}

void CircularTubeDTO::SetX(double x) {
    this->x = x;
}

void CircularTubeDTO::SetY(double y) {
    this->y = y;
}

void CircularTubeDTO::SetZ(double z) {
    this->z = z;
}

wxString CircularTubeDTO::GetDTOClassName() {
	return "CircularTubeDTO";
}

void CircularTubeDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetLength(GetLength() * space);
	SetBottomRadius(GetBottomRadius() * space);
	SetTopRadius(GetTopRadius() * space);
	SetThickness(GetThickness() * space);
}

CircularTubeDTO::~CircularTubeDTO() {

}
