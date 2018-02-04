/*
 * RectangularSheetDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "RectangularPECSheetDTO.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"

RectangularPECSheetDTO::RectangularPECSheetDTO()
	: cutAtX(false), cutAtY(false), cutAtZ(false),
	cutAt(0), x0(0), y0(0), z0(0), x1(0), y1(0), z1(0) {

}

wxString RectangularPECSheetDTO::GetDTOClassName() {
	return "RectangularPECSheetDTO";
}

void RectangularPECSheetDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetCutAt(GetCutAt() * space);
	SetX0(GetX0() * space);
	SetY0(GetY0() * space);
	SetZ0(GetZ0() * space);
	SetX1(GetX1() * space);
	SetY1(GetY1() * space);
	SetZ1(GetZ1() * space);
}
Priority RectangularPECSheetDTO::GetPriority() {
	Priority p;
	p.SetValue(MEDIUM);
	return p;
}
double RectangularPECSheetDTO::GetCutAt() {
	return cutAt;
}
double RectangularPECSheetDTO::GetX0() {
	return x0;
}
double RectangularPECSheetDTO::GetY0() {
	return y0;
}
double RectangularPECSheetDTO::GetZ0() {
	return z0;
}
double RectangularPECSheetDTO::GetX1() {
	return x1;
}
double RectangularPECSheetDTO::GetY1() {
	return y1;
}
double RectangularPECSheetDTO::GetZ1() {
	return z1;
}
void RectangularPECSheetDTO::SetX0(double x) {
	x0 = x;
}
void RectangularPECSheetDTO::SetY0(double y) {
	y0 = y;
}
void RectangularPECSheetDTO::SetZ0(double z) {
	z0 = z;
}
void RectangularPECSheetDTO::SetX1(double x) {
	x1 = x;
}
void RectangularPECSheetDTO::SetY1(double y) {
	y1 = y;
}
void RectangularPECSheetDTO::SetZ1(double z) {
	z1 = z;
}
bool RectangularPECSheetDTO::IsCutAtX() {
	return cutAtX;
}
bool RectangularPECSheetDTO::IsCutAtY() {
	return cutAtY;
}
bool RectangularPECSheetDTO::IsCutAtZ() {
	return cutAtZ;
}
void RectangularPECSheetDTO::SetCutAtX(bool b) {
	cutAtX = b;
}
void RectangularPECSheetDTO::SetCutAtY(bool b) {
	cutAtY = b;
}
void RectangularPECSheetDTO::SetCutAtZ(bool b) {
	cutAtZ = b;
}
void RectangularPECSheetDTO::SetCutAt(double d) {
	cutAt = d;
}
void RectangularPECSheetDTO::SetMatchWithPML(MatchWithPML m) {
	matchWithPML = m;
}
MatchWithPML RectangularPECSheetDTO::GetMatchWithPML() {
	return matchWithPML;
}
RectangularPECSheetDTO::~RectangularPECSheetDTO() {

}
