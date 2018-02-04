/*
 * InvalidPoint3DMEValidator.cpp
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#include "InvalidPoint3DMEValidator.h"

InvalidPoint3DMEValidator::InvalidPoint3DMEValidator(BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent) {

}

InvalidPoint3DMEValidator::~InvalidPoint3DMEValidator() {

}


wxString InvalidPoint3DMEValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" has an invalid expression.");
}

bool InvalidPoint3DMEValidator::DoIsValid(BaseType* b) {
	Point3DME* point3D = static_cast<Point3DME*>(b);

	return point3D->isPointValid();
}

bool CheckBoundaries(Point3DME& lowerBoundary, Point3DME& upperBoundary, wxString& errorMessage, wxString lowerBoundaryName, wxString upperBoundaryName) {
	bool valid = true;

	if (!lowerBoundary.isPointValid()) {
		errorMessage.Append(lowerBoundaryName).Append(" is invalid.\n");
		valid = false;
	}
	if (!upperBoundary.isPointValid()) {
		errorMessage.Append(upperBoundaryName).Append(" is invalid.\n");
		valid = false;
	}
	if (!valid) return false;

	if (lowerBoundary.GetX() >= upperBoundary.GetX()) {
		errorMessage.Append(upperBoundaryName).Append(" (x) should be greater than ").Append(lowerBoundaryName).Append(" (x).\n");
		valid = false;
	}
	if (lowerBoundary.GetY() >= upperBoundary.GetY()) {
		errorMessage.Append(upperBoundaryName).Append(" (y) should be greater than ").Append(lowerBoundaryName).Append(" (y).\n");
		valid = false;
	}
	if (lowerBoundary.GetZ() >= upperBoundary.GetZ()) {
		errorMessage.Append(upperBoundaryName).Append(" (z) should be greater than ").Append(lowerBoundaryName).Append(" (z).\n");
		valid = false;
	}

	return valid;
}
