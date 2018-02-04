/*
 * GroundParameters.cpp
 *
 *  Created on: 18/03/2015
 *      Author: Leandro
 */

#include <emstudio/gui/basetypes/GroundParameters.h>

namespace mom {

GroundParameters::GroundParameters() {
	SetWriteVersion(1);

	cliff = 2;
	gpflag = 1;
	ground2Exists = false;
	distanceBelowGround.SetExpression("0");
	distanceFromOrigin.SetExpression("0");
	numberOfWires.SetExpression("0");
	wireLength.SetExpression("0");
	wireRadius.SetExpression("0");
}

GroundParameters::~GroundParameters() {
}

/* Herdados de BaseType */
void GroundParameters::Copy(BaseType* g) {
	SetGround1(((static_cast<GroundParameters*>(g))->GetGround1()));
	if (((static_cast<GroundParameters*>(g))->IsCurrentsOnSegmentsTouchingGroundGoToZero()))
		SetCurrentsOnSegmentsTouchingGroundGoToZero();
	if (((static_cast<GroundParameters*>(g))->IsCurrentsOnSegmentsTouchingGroundInterpolated()))
		SetCurrentsOnSegmentsTouchingGroundInterpolated();
	SetGround2(((static_cast<GroundParameters*>(g))->GetGround2()));
	if (((static_cast<GroundParameters*>(g))->IsCircularCliff()))
		SetCircularCliff();
	if (((static_cast<GroundParameters*>(g))->IsLinearCliff()))
		SetLinearCliff();
	SetGround2Exists(((static_cast<GroundParameters*>(g))->IsGround2()));
	SetDistanceBelowGroundExpression(((static_cast<GroundParameters*>(g))->GetDistanceBelowGroundExpression()));
	SetDistanceFromOriginExpression(((static_cast<GroundParameters*>(g))->GetDistanceFromOriginExpression()));
	SetNumberOfWiresExpression(((static_cast<GroundParameters*>(g))->GetNumberOfWiresExpression()));
	SetWireLengthExpression(((static_cast<GroundParameters*>(g))->GetWireLengthExpression()));
	SetWireRadiusExpression(((static_cast<GroundParameters*>(g))->GetWireRadiusExpression()));
}
wxString GroundParameters::GetBaseTypeClassName() {
	return "mom::GroundParameters";
}

void GroundParameters::SetUserFriendlyStringRepresentation(wxString str) {

}
wxString GroundParameters::GetUserFriendlyStringRepresentation() {
	wxString rep;
	if (IsGroundParametersValid()) {
		if (GetNumberOfGround() == 0) {
			rep = "Free space; ";
		} else if (GetNumberOfGround() == 1){
			rep = ground1.GetDescription() + ";";
		} else if (GetNumberOfGround() == 2) {
			if (IsCircularCliff())
				rep += "Circular cliff; ";
			if (IsLinearCliff())
				rep += "Linear cliff; ";
		}
		rep += Converter::IntToFormattedString(GetNumberOfWires()) + " radials";
	} else {
		rep = "Invalid expression";
	}
	return rep;
}

void GroundParameters::DoWrite(OutputBuffer& buffer) {
	ground1.Write(buffer);
	buffer.WriteInt(gpflag);
	ground2.Write(buffer);
	buffer.WriteInt(cliff);
	buffer.WriteBool(ground2Exists);
	wxString str = distanceBelowGround.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = distanceFromOrigin.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = numberOfWires.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = wireLength.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = wireRadius.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
}
void GroundParameters::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	ground1.Read(buffer);
	gpflag = buffer.ReadInt();
	ground2.Read(buffer);
	cliff = buffer.ReadInt();
	ground2Exists = buffer.ReadBool();
	distanceBelowGround.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	distanceFromOrigin.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	numberOfWires.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	wireLength.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	wireRadius.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
}

/* Getters and setters */
Material GroundParameters::GetGround1() {
	return ground1;
}
Material GroundParameters::GetGround2() {
	return ground2;
}
bool GroundParameters::IsGround2() {
	return ground2Exists;
}
bool GroundParameters::IsCircularCliff() {
	return cliff == 3;
}
bool GroundParameters::IsLinearCliff() {
	return cliff == 2;
}
wxString GroundParameters::GetDistanceBelowGroundExpression() {
	return distanceBelowGround.GetExpression();
}
wxString GroundParameters::GetDistanceFromOriginExpression() {
	return distanceFromOrigin.GetExpression();
}
wxString GroundParameters::GetNumberOfWiresExpression() {
	return numberOfWires.GetExpression();
}
wxString GroundParameters::GetWireLengthExpression() {
	return wireLength.GetExpression();
}
wxString GroundParameters::GetWireRadiusExpression() {
	return wireRadius.GetExpression();
}
double GroundParameters::GetDistanceBelowGround() {
	return distanceBelowGround.Eval();
}
double GroundParameters::GetDistanceFromOrigin() {
	return distanceFromOrigin.Eval();
}
int GroundParameters::GetNumberOfWires() {
	return (int)numberOfWires.Eval();
}
double GroundParameters::GetWireLength() {
	return wireLength.Eval();
}
double GroundParameters::GetWireRadius() {
	return wireRadius.Eval();
}
void GroundParameters::SetGround1(Material m) {
	ground1 = m;
}
void GroundParameters::SetGround2(Material m) {
	ground2 = m;
}
void GroundParameters::SetGround2Exists(bool b) {
	ground2Exists = b;
}
void GroundParameters::SetCircularCliff() {
	cliff = 3;
}
void GroundParameters::SetLinearCliff(){
	cliff = 2;
}
void GroundParameters::SetDistanceBelowGroundExpression(wxString expr) {
	distanceBelowGround.SetExpression(expr);
}
void GroundParameters::SetDistanceFromOriginExpression(wxString expr) {
	distanceFromOrigin.SetExpression(expr);
}
void GroundParameters::SetNumberOfWiresExpression(wxString expr) {
	numberOfWires.SetExpression(expr);
}
void GroundParameters::SetWireLengthExpression(wxString expr) {
	wireLength.SetExpression(expr);
}
void GroundParameters::SetWireRadiusExpression(wxString expr) {
	wireRadius.SetExpression(expr);
}
/* Check if the expressions are valid */
bool GroundParameters::IsDistanceBelowGroundExpressionValid() {
	return distanceBelowGround.IsValid();
}
bool GroundParameters::IsDistanceFromOriginExpressionValid() {
	return distanceFromOrigin.IsValid();
}
bool GroundParameters::IsNumberOfWiresExpressionValid() {
	return numberOfWires.IsValid();
}
bool GroundParameters::IsWireLengthExpressionValid() {
	return wireLength.IsValid();
}
bool GroundParameters::IsWireRadiusExpressionValid() {
	return wireRadius.IsValid();
}
bool GroundParameters::IsGroundParametersValid() {
	// Sync materials
	ground1.Sync(false);
	ground2.Sync(false);

	bool ground2OK = !IsGround2() ||
			(IsDistanceBelowGroundExpressionValid() && IsDistanceFromOriginExpressionValid());
	return  ground2OK &&
			IsNumberOfWiresExpressionValid() &&
			IsWireLengthExpressionValid() &&
			IsWireRadiusExpressionValid();
}
/* Other methods */
int GroundParameters::GetNumberOfGround() {
	int n = 0;
	if (!ground1.IsFreeSpace())
		n++;
	if (IsGround2() && !ground2.IsFreeSpace())
		n++;
	return n;
}

bool GroundParameters::IsCurrentsOnSegmentsTouchingGroundGoToZero() {
	return gpflag == -1;
}
bool GroundParameters::IsCurrentsOnSegmentsTouchingGroundInterpolated() {
	return gpflag == 1;
}
void GroundParameters::SetCurrentsOnSegmentsTouchingGroundGoToZero() {
	gpflag = -1;
}
void GroundParameters::SetCurrentsOnSegmentsTouchingGroundInterpolated() {
	gpflag = 1;
}

} /* namespace mom */
