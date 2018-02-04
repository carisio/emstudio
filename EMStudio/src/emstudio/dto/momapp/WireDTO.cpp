/*
 * WireDTO.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "WireDTO.h"

namespace mom {

WireDTO::WireDTO() {

}

WireDTO::~WireDTO() {
}

void WireDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	SetP1(GetP1() * space);
	SetP2(GetP2() * space);
	SetRadius(GetRadius() * space);
}
wxString WireDTO::GetDTOClassName() {
	return "mom::WireDTO";
}
void WireDTO::SetP1(Rvector3 p1) {
	this->p1 = p1;
}
void WireDTO::SetP2(Rvector3 p2) {
	this->p2 = p2;
}
void WireDTO::SetRadius(double radius) {
	this->radius = radius;
}
void WireDTO::SetNumberOfSegments(int numberOfSegments) {
	this->numberOfSegments = numberOfSegments;
}
Rvector3 WireDTO::GetP1() {
	return p1;
}
Rvector3 WireDTO::GetP2() {
	return p2;
}
double WireDTO::GetRadius() {
	return radius;
}
int WireDTO::GetNumberOfSegments() {
	return numberOfSegments;
}

} /* namespace mom */
