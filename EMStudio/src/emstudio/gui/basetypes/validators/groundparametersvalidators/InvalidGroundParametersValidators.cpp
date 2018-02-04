/*
 * InvalidGroundParametersValidators.cpp
 *
 *  Created on: 19/03/2015
 *      Author: leandrocarisio
 */

#include "InvalidGroundParametersValidators.h"

namespace mom {

InvalidGroundParametersValidators::InvalidGroundParametersValidators(BaseTypeValidatorSmartPointer parent)
		: BaseTypeValidator(parent) {

}

InvalidGroundParametersValidators::~InvalidGroundParametersValidators() {

}


wxString InvalidGroundParametersValidators::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	GroundParameters* gp = static_cast<GroundParameters*>(b);
	wxString errorMsg;

	if (!expressionsValid) {
		errorMsg = baseTypeName;
		return errorMsg.Append(" has an invalid expression.\n");
	}

	if (ground2DefinedWithoutGround1) {
		errorMsg.Append("Ground 2 of ").Append(baseTypeName).Append(" cannot be defined if its ground 1 is free space.\n");
	}
	if (ground2DefinedAsFreeSpace) {
		errorMsg.Append("Ground 2 of ").Append(baseTypeName).Append(" cannot be defined as free space.\n");
	}
	if (!distBelowGroundGTOEZero) {
		errorMsg.Append("Distance below ground of ").Append(baseTypeName).Append(" should be greatter than or equal 0.\n");
	}
	if (!distFromOriginGTZero) {
		errorMsg.Append("Distance from origin of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}
	if (!nWiresGTOEZero) {
		errorMsg.Append("Number of wires of ").Append(baseTypeName).Append(" should be greatter than or equal 0.\n");
	}
	if (!wireLengthGTOEZero) {
		errorMsg.Append("Wire length of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}
	if (!wireRadiusGTOEZero) {
		errorMsg.Append("Wire radius of ").Append(baseTypeName).Append(" should be greatter than 0.\n");
	}
	if (!radialsDoesNotFluctuateOverGround2) {
		errorMsg.Append("The radials of ").Append(baseTypeName).Append(" cannot fluctuate over ground 2. Its length should be lower than distance from origin.\n");
	}
	return errorMsg;
}

bool InvalidGroundParametersValidators::DoIsValid(BaseType* b) {
	GroundParameters* gp = static_cast<GroundParameters*>(b);

	expressionsValid = gp->IsGroundParametersValid();
	if (!expressionsValid) return false;

	ground2DefinedWithoutGround1 = gp->GetGround1().IsFreeSpace() && gp->IsGround2();
	ground2DefinedAsFreeSpace = gp->IsGround2() && gp->GetGround2().IsFreeSpace();
	distBelowGroundGTOEZero = !gp->IsGround2() || gp->GetDistanceBelowGround() >= 0;
	distFromOriginGTZero = !gp->IsGround2() || gp->GetDistanceFromOrigin() > 0;
	nWiresGTOEZero = gp->GetNumberOfWires() >= 0;
	wireLengthGTOEZero = gp->GetNumberOfWires() == 0 || gp->GetWireLength() > 0;
	wireRadiusGTOEZero = gp->GetNumberOfWires() == 0 || gp->GetWireRadius() > 0;
	radialsDoesNotFluctuateOverGround2 = (gp->GetNumberOfWires() > 0 && gp->IsGround2() && gp->GetDistanceBelowGround() > 0) ? gp->GetWireLength() < gp->GetDistanceFromOrigin() : true;

	return expressionsValid &&
			!ground2DefinedWithoutGround1 &&
			!ground2DefinedAsFreeSpace &&
			distBelowGroundGTOEZero &&
			distFromOriginGTZero &&
			nWiresGTOEZero &&
			wireLengthGTOEZero &&
			wireRadiusGTOEZero &&
			radialsDoesNotFluctuateOverGround2;

}

} /* namespace mom */
