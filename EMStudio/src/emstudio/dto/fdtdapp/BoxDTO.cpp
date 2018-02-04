/*
 * CubeDTO.cpp
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#include "BoxDTO.h"

BoxDTO::BoxDTO() {

}


double BoxDTO::GetX1() const {
    return x1;
}

double BoxDTO::GetX2() const {
    return x2;
}

double BoxDTO::GetY1() const {
    return y1;
}

double BoxDTO::GetY2() const {
    return y2;
}

double BoxDTO::GetZ1() const {
    return z1;
}

double BoxDTO::GetZ2() const {
    return z2;
}

MatchWithPML BoxDTO::GetMatchWithPML() {
	return matchWithPML;
}


void BoxDTO::SetX1(double x1) {
    this->x1 = x1;
}

void BoxDTO::SetX2(double x2) {
    this->x2 = x2;
}

void BoxDTO::SetY1(double y1) {
    this->y1 = y1;
}

void BoxDTO::SetY2(double y2) {
    this->y2 = y2;
}

void BoxDTO::SetZ1(double z1) {
    this->z1 = z1;
}

void BoxDTO::SetZ2(double z2) {
    this->z2 = z2;
}

void BoxDTO::SetMatchWithPML(MatchWithPML m) {
	matchWithPML = m;
}

BoxDTO::~BoxDTO() {

}

void BoxDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX1(GetX1() * space);
	SetY1(GetY1() * space);
	SetZ1(GetZ1() * space);
	SetX2(GetX2() * space);
	SetY2(GetY2() * space);
	SetZ2(GetZ2() * space);
}
wxString BoxDTO::GetDTOClassName() {
	return "BoxDTO";
}
