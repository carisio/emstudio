/*
 * RectangularTubeDTO.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "RectangularTubeDTO.h"

RectangularTubeDTO::RectangularTubeDTO() {

}

double RectangularTubeDTO::GetBaseInnerHeight() const {
    return baseInnerHeight;
}

double RectangularTubeDTO::GetBaseInnerWidth() const {
    return baseInnerWidth;
}

double RectangularTubeDTO::GetBaseOutterHeight() const {
    return baseOutterHeight;
}

double RectangularTubeDTO::GetBaseOutterWidth() const {
    return baseOutterWidth;
}

double RectangularTubeDTO::GetLength() const {
    return length;
}

Orientation RectangularTubeDTO::GetOrientation() const {
    return orientation;
}

double RectangularTubeDTO::GetTopInnerHeight() const {
    return topInnerHeight;
}

double RectangularTubeDTO::GetTopInnerWidth() const {
    return topInnerWidth;
}

double RectangularTubeDTO::GetTopOutterHeight() const {
    return topOutterHeight;
}

double RectangularTubeDTO::GetTopOutterWidth() const {
    return topOutterWidth;
}

double RectangularTubeDTO::GetX() const {
    return x;
}

double RectangularTubeDTO::GetY() const {
    return y;
}

double RectangularTubeDTO::GetZ() const {
    return z;
}

void RectangularTubeDTO::SetBaseInnerHeight(double baseInnerHeight) {
    this->baseInnerHeight = baseInnerHeight;
}

void RectangularTubeDTO::SetBaseInnerWidth(double baseInnerWidth) {
    this->baseInnerWidth = baseInnerWidth;
}

void RectangularTubeDTO::SetBaseOutterHeight(double baseOutterHeight) {
    this->baseOutterHeight = baseOutterHeight;
}

void RectangularTubeDTO::SetBaseOutterWidth(double baseOutterWidth) {
    this->baseOutterWidth = baseOutterWidth;
}

void RectangularTubeDTO::SetLength(double length) {
    this->length = length;
}

void RectangularTubeDTO::SetOrientation(Orientation orientation) {
    this->orientation = orientation;
}

void RectangularTubeDTO::SetTopInnerHeight(double topInnerHeight) {
    this->topInnerHeight = topInnerHeight;
}

void RectangularTubeDTO::SetTopInnerWidth(double topInnerWidth) {
    this->topInnerWidth = topInnerWidth;
}

void RectangularTubeDTO::SetTopOutterHeight(double topOutterHeight) {
    this->topOutterHeight = topOutterHeight;
}

void RectangularTubeDTO::SetTopOutterWidth(double topOutterWidth) {
    this->topOutterWidth = topOutterWidth;
}

void RectangularTubeDTO::SetX(double x) {
    this->x = x;
}

void RectangularTubeDTO::SetY(double y) {
    this->y = y;
}

void RectangularTubeDTO::SetZ(double z) {
    this->z = z;
}

RectangularTubeDTO::~RectangularTubeDTO() {

}

wxString RectangularTubeDTO::GetDTOClassName() {
	return "RectangularTubeDTO";
}

void RectangularTubeDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;

	SetX(GetX() * space);
	SetY(GetY() * space);
	SetZ(GetZ() * space);
	SetLength(GetLength() * space);
	SetBaseInnerHeight(GetBaseInnerHeight() * space);
	SetBaseOutterHeight(GetBaseOutterHeight() * space);
	SetBaseInnerWidth(GetBaseInnerWidth() * space);
	SetBaseOutterWidth(GetBaseOutterWidth() * space);
	SetTopInnerHeight(GetTopInnerHeight() * space);
	SetTopOutterHeight(GetTopOutterHeight() * space);
	SetTopInnerWidth(GetTopInnerWidth() * space);
	SetTopOutterWidth(GetTopOutterWidth() * space);
}

