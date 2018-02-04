/*
 * RectangularTubeGeometryME.cpp
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#include "RectangularTubeGeometryME.h"
#include "emstudio/util/converters/Converter.h"
#include <iostream>
using namespace::std;

RectangularTubeGeometryME::RectangularTubeGeometryME() {
	SetWriteVersion(1);

	SetZOriented();
	SetBaseCutAtExpression("0");
	SetBaseCoord1BeginExpression("10");
	SetBaseCoord1EndExpression("30");
	SetBaseCoord2BeginExpression("10");
	SetBaseCoord2EndExpression("30");
	SetBaseCoord1ThicknessExpression("3");
	SetBaseCoord2ThicknessExpression("3");
	SetTopCutAtExpression("30");
	SetTopCoord1BeginExpression("15");
	SetTopCoord1EndExpression("25");
	SetTopCoord2BeginExpression("15");
	SetTopCoord2EndExpression("25");
	SetTopCoord1ThicknessExpression("3");
	SetTopCoord2ThicknessExpression("3");
}

RectangularTubeGeometryME::~RectangularTubeGeometryME() {

}

void RectangularTubeGeometryME::SetXOriented() {
	orientation = RectangularTubeGeometryME::X;
}
void RectangularTubeGeometryME::SetYOriented() {
	orientation = RectangularTubeGeometryME::Y;
}
void RectangularTubeGeometryME::SetZOriented() {
	orientation = RectangularTubeGeometryME::Z;
}

bool RectangularTubeGeometryME::IsXOriented() {
	return orientation == RectangularTubeGeometryME::X;
}
bool RectangularTubeGeometryME::IsYOriented() {
	return orientation == RectangularTubeGeometryME::Y;
}
bool RectangularTubeGeometryME::IsZOriented() {
	return orientation == RectangularTubeGeometryME::Z;
}

void RectangularTubeGeometryME::SetBaseCutAtExpression(wxString expr) {
	bCutAt.SetExpression(expr);
}
void RectangularTubeGeometryME::SetBaseCoord1BeginExpression(wxString expr) {
	bCoord1Begin.SetExpression(expr);
}
void RectangularTubeGeometryME::SetBaseCoord1EndExpression(wxString expr) {
	bCoord1End.SetExpression(expr);
}
void RectangularTubeGeometryME::SetBaseCoord2BeginExpression(wxString expr) {
	bCoord2Begin.SetExpression(expr);
}
void RectangularTubeGeometryME::SetBaseCoord2EndExpression(wxString expr) {
	bCoord2End.SetExpression(expr);
}
void RectangularTubeGeometryME::SetBaseCoord1ThicknessExpression(wxString expr) {
	bCoord1Thickness.SetExpression(expr);
}
void RectangularTubeGeometryME::SetBaseCoord2ThicknessExpression(wxString expr) {
	bCoord2Thickness.SetExpression(expr);
}
void RectangularTubeGeometryME::SetTopCutAtExpression(wxString expr) {
	tCutAt.SetExpression(expr);
}
void RectangularTubeGeometryME::SetTopCoord1BeginExpression(wxString expr) {
	tCoord1Begin.SetExpression(expr);
}
void RectangularTubeGeometryME::SetTopCoord1EndExpression(wxString expr) {
	tCoord1End.SetExpression(expr);
}
void RectangularTubeGeometryME::SetTopCoord2BeginExpression(wxString expr) {
	tCoord2Begin.SetExpression(expr);
}
void RectangularTubeGeometryME::SetTopCoord2EndExpression(wxString expr) {
	tCoord2End.SetExpression(expr);
}
void RectangularTubeGeometryME::SetTopCoord1ThicknessExpression(wxString expr) {
	tCoord1Thickness.SetExpression(expr);
}
void RectangularTubeGeometryME::SetTopCoord2ThicknessExpression(wxString expr) {
	tCoord2Thickness.SetExpression(expr);
}

wxString RectangularTubeGeometryME::GetBaseCutAtExpression() {
	return bCutAt.GetExpression();
}
wxString RectangularTubeGeometryME::GetBaseCoord1BeginExpression() {
	return bCoord1Begin.GetExpression();
}
wxString RectangularTubeGeometryME::GetBaseCoord1EndExpression() {
	return bCoord1End.GetExpression();
}
wxString RectangularTubeGeometryME::GetBaseCoord2BeginExpression() {
	return bCoord2Begin.GetExpression();
}
wxString RectangularTubeGeometryME::GetBaseCoord2EndExpression() {
	return bCoord2End.GetExpression();
}
wxString RectangularTubeGeometryME::GetBaseCoord1ThicknessExpression() {
	return bCoord1Thickness.GetExpression();
}
wxString RectangularTubeGeometryME::GetBaseCoord2ThicknessExpression() {
	return bCoord2Thickness.GetExpression();
}
wxString RectangularTubeGeometryME::GetTopCutAtExpression() {
	return tCutAt.GetExpression();
}
wxString RectangularTubeGeometryME::GetTopCoord1BeginExpression() {
	return tCoord1Begin.GetExpression();
}
wxString RectangularTubeGeometryME::GetTopCoord1EndExpression() {
	return tCoord1End.GetExpression();
}
wxString RectangularTubeGeometryME::GetTopCoord2BeginExpression() {
	return tCoord2Begin.GetExpression();
}
wxString RectangularTubeGeometryME::GetTopCoord2EndExpression() {
	return tCoord2End.GetExpression();
}
wxString RectangularTubeGeometryME::GetTopCoord1ThicknessExpression() {
	return tCoord1Thickness.GetExpression();
}
wxString RectangularTubeGeometryME::GetTopCoord2ThicknessExpression() {
	return tCoord2Thickness.GetExpression();
}

double RectangularTubeGeometryME::GetBaseCutAt() {
	return bCutAt.Eval();
}
double RectangularTubeGeometryME::GetBaseCoord1Begin() {
	return bCoord1Begin.Eval();
}
double RectangularTubeGeometryME::GetBaseCoord1End() {
	return bCoord1End.Eval();
}
double RectangularTubeGeometryME::GetBaseCoord2Begin() {
	return bCoord2Begin.Eval();
}
double RectangularTubeGeometryME::GetBaseCoord2End() {
	return bCoord2End.Eval();
}
double RectangularTubeGeometryME::GetBaseCoord1Thickness() {
	return bCoord1Thickness.Eval();
}
double RectangularTubeGeometryME::GetBaseCoord2Thickness() {
	return bCoord2Thickness.Eval();
}
double RectangularTubeGeometryME::GetTopCutAt() {
	return tCutAt.Eval();
}
double RectangularTubeGeometryME::GetTopCoord1Begin() {
	return tCoord1Begin.Eval();
}
double RectangularTubeGeometryME::GetTopCoord1End() {
	return tCoord1End.Eval();
}
double RectangularTubeGeometryME::GetTopCoord2Begin() {
	return tCoord2Begin.Eval();
}
double RectangularTubeGeometryME::GetTopCoord2End() {
	return tCoord2End.Eval();
}
double RectangularTubeGeometryME::GetTopCoord1Thickness() {
	return tCoord1Thickness.Eval();
}
double RectangularTubeGeometryME::GetTopCoord2Thickness() {
	return tCoord2Thickness.Eval();
}

bool RectangularTubeGeometryME::IsBaseCutAtExpressionValid() {
	return bCutAt.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsBaseCoord1BeginExpressionValid() {
	return bCoord1Begin.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsBaseCoord1EndExpressionValid() {
	return bCoord1End.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsBaseCoord2BeginExpressionValid() {
	return bCoord2Begin.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsBaseCoord2EndExpressionValid() {
	return bCoord2End.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsBaseCoord1ThicknessExpressionValid() {
	return bCoord1Thickness.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsBaseCoord2ThicknessExpressionValid() {
	return bCoord2Thickness.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsTopCutAtExpressionValid() {
	return tCutAt.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsTopCoord1BeginExpressionValid() {
	return tCoord1Begin.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsTopCoord1EndExpressionValid() {
	return tCoord1End.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsTopCoord2BeginExpressionValid() {
	return tCoord2Begin.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsTopCoord2EndExpressionValid() {
	return tCoord2End.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsTopCoord1ThicknessExpressionValid() {
	return tCoord1Thickness.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsTopCoord2ThicknessExpressionValid() {
	return tCoord2Thickness.DefineConstantsAndCheckIfIsValid();
}
bool RectangularTubeGeometryME::IsGeometryValid() {
	return 	IsBaseCutAtExpressionValid() &&
			IsBaseCoord1BeginExpressionValid() &&
			IsBaseCoord1EndExpressionValid() &&
			IsBaseCoord2BeginExpressionValid() &&
			IsBaseCoord2EndExpressionValid() &&
			IsBaseCoord1ThicknessExpressionValid() &&
			IsBaseCoord2ThicknessExpressionValid() &&
			IsTopCutAtExpressionValid() &&
			IsTopCoord1BeginExpressionValid() &&
			IsTopCoord1EndExpressionValid() &&
			IsTopCoord2BeginExpressionValid() &&
			IsTopCoord2EndExpressionValid() &&
			IsTopCoord1ThicknessExpressionValid() &&
			IsTopCoord2ThicknessExpressionValid();
}


void RectangularTubeGeometryME::Copy(BaseType* p) {
	RectangularTubeGeometryME* pRTG = static_cast<RectangularTubeGeometryME*>(p);

	orientation = pRTG->orientation;
	SetBaseCutAtExpression(pRTG->GetBaseCutAtExpression());
	SetBaseCoord1BeginExpression(pRTG->GetBaseCoord1BeginExpression());
	SetBaseCoord1EndExpression(pRTG->GetBaseCoord1EndExpression());
	SetBaseCoord2BeginExpression(pRTG->GetBaseCoord2BeginExpression());
	SetBaseCoord2EndExpression(pRTG->GetBaseCoord2EndExpression());
	SetBaseCoord1ThicknessExpression(pRTG->GetBaseCoord1ThicknessExpression());
	SetBaseCoord2ThicknessExpression(pRTG->GetBaseCoord2ThicknessExpression());
	SetTopCutAtExpression(pRTG->GetTopCutAtExpression());
	SetTopCoord1BeginExpression(pRTG->GetTopCoord1BeginExpression());
	SetTopCoord1EndExpression(pRTG->GetTopCoord1EndExpression());
	SetTopCoord2BeginExpression(pRTG->GetTopCoord2BeginExpression());
	SetTopCoord2EndExpression(pRTG->GetTopCoord2EndExpression());
	SetTopCoord1ThicknessExpression(pRTG->GetTopCoord1ThicknessExpression());
	SetTopCoord2ThicknessExpression(pRTG->GetTopCoord2ThicknessExpression());
}
wxString RectangularTubeGeometryME::GetBaseTypeClassName() {
	return "RectangularTubeGeometryME";
}

wxString RectangularTubeGeometryME::GetUserFriendlyStringRepresentation() {
	bool valid = IsGeometryValid();
	if (!valid)
		return "Invalid expression";

	double length = GetTopCutAt() - GetBaseCutAt();
	length = length < 0 ? length*-1 : length;

	wxString result;
	result = "Length: ";
	result.Append(Converter::DoubleToFormattedString(length, 2)). Append(" (");
	if (IsXOriented()) result.Append("X)");
	if (IsYOriented()) result.Append("Y)");
	if (IsZOriented()) result.Append("Z)");

	return result;
}

void RectangularTubeGeometryME::SetUserFriendlyStringRepresentation(wxString str) {

}

void RectangularTubeGeometryME::DoWrite(OutputBuffer& buffer) {

	buffer.WriteInt(orientation);

	wxString str = bCutAt.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = bCoord1Begin.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = bCoord1End.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = bCoord2Begin.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = bCoord2End.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = bCoord1Thickness.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = bCoord2Thickness.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);

	str = tCutAt.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = tCoord1Begin.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = tCoord1End.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = tCoord2Begin.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = tCoord2End.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = tCoord1Thickness.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = tCoord2Thickness.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
}
void RectangularTubeGeometryME::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	orientation = buffer.ReadInt();
	bCutAt.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	bCoord1Begin.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	bCoord1End.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	bCoord2Begin.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	bCoord2End.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	bCoord1Thickness.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	bCoord2Thickness.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	tCutAt.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	tCoord1Begin.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	tCoord1End.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	tCoord2Begin.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	tCoord2End.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	tCoord1Thickness.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	tCoord2Thickness.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());

}
