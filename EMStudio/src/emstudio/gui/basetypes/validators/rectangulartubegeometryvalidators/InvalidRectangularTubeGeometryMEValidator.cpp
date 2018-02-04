/*
 * InvalidRectangularTubeGeometryMEValidator.cpp
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#include "InvalidRectangularTubeGeometryMEValidator.h"

InvalidRectangularTubeGeometryMEValidator::InvalidRectangularTubeGeometryMEValidator(BaseTypeValidatorSmartPointer parent)
		: BaseTypeValidator(parent) {

}

InvalidRectangularTubeGeometryMEValidator::~InvalidRectangularTubeGeometryMEValidator() {

}


wxString InvalidRectangularTubeGeometryMEValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	RectangularTubeGeometryME* geometry = static_cast<RectangularTubeGeometryME*>(b);
	wxString errorMsg;

	if (!expressionsValid) {
		errorMsg = baseTypeName;
		return errorMsg.Append(" has an invalid expression.\n");
	}

	wxString coord1;
	wxString coord2;
	if (geometry->IsXOriented()) {
		coord1 = "y"; coord2 = "z";
	} else if (geometry->IsYOriented()) {
		coord1 = "x"; coord2 = "z";
	} else if (geometry->IsZOriented()) {
		coord1 = "x"; coord2 = "y";
	}

	if (!lengthOK) {
		errorMsg.Append("The length of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}
	if (!baseCoord1OK || !topCoord1OK) {
		errorMsg.Append("The ").Append(coord1).Append("-dimension of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}
	if (!baseCoord1ThickDifZero || !topCoord1ThickDifZero) {
		errorMsg.Append("The ").Append(coord1).Append("-thickness of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}
	if (!baseCoord2OK || !topCoord2OK) {
		errorMsg.Append("The ").Append(coord2).Append("-dimension of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}
	if (!baseCoord2ThickDifZero || !topCoord2ThickDifZero ) {
		errorMsg.Append("The ").Append(coord2).Append("-thickness of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}

	return errorMsg;
}

bool InvalidRectangularTubeGeometryMEValidator::DoIsValid(BaseType* b) {
	RectangularTubeGeometryME* geometry = static_cast<RectangularTubeGeometryME*>(b);

	expressionsValid = geometry->IsGeometryValid();
	if (!expressionsValid) return false;

	lengthOK = (geometry->GetBaseCutAt() - geometry->GetTopCutAt()) != 0;

	baseCoord1OK = (geometry->GetBaseCoord1End() - geometry->GetBaseCoord1Begin()) > 0;
	baseCoord2OK = (geometry->GetBaseCoord2End() - geometry->GetBaseCoord2Begin()) > 0;
	baseCoord1ThickDifZero = geometry->GetBaseCoord1Thickness() > 0;
	baseCoord2ThickDifZero = geometry->GetBaseCoord2Thickness() > 0;
	topCoord1OK = (geometry->GetTopCoord1End() - geometry->GetTopCoord1Begin()) != 0;
	topCoord2OK = (geometry->GetTopCoord2End() - geometry->GetTopCoord2Begin()) != 0;
	topCoord1ThickDifZero = geometry->GetTopCoord1Thickness() > 0;
	topCoord2ThickDifZero = geometry->GetTopCoord2Thickness() > 0;

	return expressionsValid &&
			lengthOK &&
			baseCoord1OK &&
			baseCoord2OK &&
			baseCoord1ThickDifZero &&
			baseCoord2ThickDifZero &&
			topCoord1OK &&
			topCoord2OK &&
			topCoord1ThickDifZero &&
			topCoord2ThickDifZero;
}
