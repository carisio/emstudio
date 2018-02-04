/*
 * Segment.cpp
 *
 *  Created on: 28/05/2014
 *      Author: leandrocarisio
 */

#include "Segment.h"
#include "math.h"

Segment::Segment(Rvector3 p1, Rvector3 p2, double radius) :
	p1(p1), p2(p2), radius(radius) {
}

Segment::~Segment() {
}
void Segment::MultiplyByConstant(double c) {
	p1 = p1 * c;
	p2 = p2 * c;
	radius = radius * c;
}
void Segment::SetP1(Rvector3& p1) {
	this->p1 = p1;
}
void Segment::SetP2(Rvector3& p1) {
	this->p2 = p2;
}
void Segment::SetRadius(double& radius) {
	this->radius = radius;
}
Rvector3 Segment::GetP1() {
	return p1;
}
Rvector3 Segment::GetP2() {
	return p2;
}
double Segment::GetRadius() {
	return radius;
}
double Segment::GetDistanceToCenter(double x, double y, double z) {
	double xc = (p1.X + (p2.X-p1.X)/2);
	double yc = (p1.Y + (p2.Y-p1.Y)/2);
	double zc = (p1.Z + (p2.Z-p1.Z)/2);

	return sqrt( pow((x-xc),2) + pow((y-yc),2) + pow((z-zc),2));
}
