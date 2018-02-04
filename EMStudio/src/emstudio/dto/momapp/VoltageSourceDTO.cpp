/*
 * VoltageSourceDTO.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "VoltageSourceDTO.h"

namespace mom {

VoltageSourceDTO::VoltageSourceDTO() {

}

VoltageSourceDTO::~VoltageSourceDTO() {

}

void VoltageSourceDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
}
wxString VoltageSourceDTO::GetDTOClassName() {
	return "mom::VoltageSourceDTO";
}
void VoltageSourceDTO::SetRealPart(double r) {
	realPart = r;
}
void VoltageSourceDTO::SetImagPart(double i) {
	imagPart = i;
}
void VoltageSourceDTO::SetX(double x) {
	this->x = x;
}
void VoltageSourceDTO::SetY(double y) {
	this->y = y;
}
void VoltageSourceDTO::SetZ(double z) {
	this->z = z;
}
double VoltageSourceDTO::GetRealPart() {
	return realPart;
}
double VoltageSourceDTO::GetImagPart() {
	return imagPart;
}
double VoltageSourceDTO::GetX() {
	return x;
}
double VoltageSourceDTO::GetY() {
	return y;
}
double VoltageSourceDTO::GetZ() {
	return z;
}

} /* namespace mom */
