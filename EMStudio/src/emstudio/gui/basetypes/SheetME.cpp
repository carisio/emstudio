/*
 * SheetME.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "SheetME.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

SheetME::SheetME() {
	SetWriteVersion(1);
	SetCutAtZ("25");
}

SheetME::~SheetME() {
}

void SheetME::SetX0Expression(wxString x) {
	x0Parser.SetExpression(x);
}
void SheetME::SetY0Expression(wxString y) {
	y0Parser.SetExpression(y);
}
void SheetME::SetZ0Expression(wxString z) {
	z0Parser.SetExpression(z);
}
wxString SheetME::GetX0Expression() {
	return x0Parser.GetExpression();
}
wxString SheetME::GetY0Expression() {
	return y0Parser.GetExpression();
}
wxString SheetME::GetZ0Expression() {
	return z0Parser.GetExpression();
}
bool SheetME::IsX0ExpressionValid() {
	return x0Parser.DefineConstantsAndCheckIfIsValid();
}
bool SheetME::IsY0ExpressionValid() {
	return y0Parser.DefineConstantsAndCheckIfIsValid();
}
bool SheetME::IsZ0ExpressionValid() {
	return z0Parser.DefineConstantsAndCheckIfIsValid();
}
void SheetME::SetX1Expression(wxString x) {
	x1Parser.SetExpression(x);
}
void SheetME::SetY1Expression(wxString y) {
	y1Parser.SetExpression(y);
}
void SheetME::SetZ1Expression(wxString z) {
	z1Parser.SetExpression(z);
}
wxString SheetME::GetX1Expression() {
	return x1Parser.GetExpression();
}
wxString SheetME::GetY1Expression() {
	return y1Parser.GetExpression();
}
wxString SheetME::GetZ1Expression() {
	return z1Parser.GetExpression();
}
bool SheetME::IsX1ExpressionValid() {
	return x1Parser.DefineConstantsAndCheckIfIsValid();
}
bool SheetME::IsY1ExpressionValid() {
	return y1Parser.DefineConstantsAndCheckIfIsValid();
}
bool SheetME::IsZ1ExpressionValid() {
	return z1Parser.DefineConstantsAndCheckIfIsValid();
}
bool SheetME::IsSheetValid() {
	return IsX0ExpressionValid() && IsY0ExpressionValid() && IsZ0ExpressionValid()
			&& IsX1ExpressionValid() && IsY1ExpressionValid() && IsZ1ExpressionValid();
}
bool SheetME::EvalExpressions() {
	return IsSheetValid();
}
double SheetME::GetX0() const {
	return x0Parser.Eval();
}
double SheetME::GetY0() const {
	return y0Parser.Eval();
}
double SheetME::GetZ0() const {
	return z0Parser.Eval();
}
double SheetME::GetX1() const {
	return x1Parser.Eval();
}
double SheetME::GetY1() const {
	return y1Parser.Eval();
}
double SheetME::GetZ1() const {
	return z1Parser.Eval();
}
bool SheetME::IsCutAtX() {
	return plane == SheetME::YZ;
}
bool SheetME::IsCutAtY() {
	return plane == SheetME::ZX;
}
bool SheetME::IsCutAtZ() {
	return plane == SheetME::XY;
}
void SheetME::SetCutAtX(wxString x) {
	plane = SheetME::YZ;
	x0Parser.SetExpression(x);
	x1Parser.SetExpression(x);
}
void SheetME::SetCutAtY(wxString y) {
	plane = SheetME::ZX;
	y0Parser.SetExpression(y);
	y1Parser.SetExpression(y);
}
void SheetME::SetCutAtZ(wxString z) {
	plane = SheetME::XY;
	z0Parser.SetExpression(z);
	z1Parser.SetExpression(z);
}
wxString SheetME::GetCutAtExpression() {
	if (IsCutAtX()) {
		return x0Parser.GetExpression();
	} else if (IsCutAtY()) {
		return y0Parser.GetExpression();
	} else if (IsCutAtZ()) {
		return z0Parser.GetExpression();
	}
	return "";
}
double SheetME::GetCutAt() {
	if (IsCutAtX()) {
		x0Parser.DefineConstantsAndCheckIfIsValid();
		return x0Parser.Eval();
	} else if (IsCutAtY()) {
		y0Parser.DefineConstantsAndCheckIfIsValid();
		return y0Parser.Eval();
	} else if (IsCutAtZ()) {
		z0Parser.DefineConstantsAndCheckIfIsValid();
		return z0Parser.Eval();
	}
	return 0;
}
void SheetME::Copy(BaseType* p) {
	SheetME* pSheet = static_cast<SheetME*>(p);
	SetX0Expression(pSheet->GetX0Expression());
	SetX1Expression(pSheet->GetX1Expression());
	SetY0Expression(pSheet->GetY0Expression());
	SetY1Expression(pSheet->GetY1Expression());
	SetZ0Expression(pSheet->GetZ0Expression());
	SetZ1Expression(pSheet->GetZ1Expression());
	if (pSheet->IsCutAtX()) {
		SetCutAtX(pSheet->GetCutAtExpression());
	} else if (pSheet->IsCutAtY()) {
		SetCutAtY(pSheet->GetCutAtExpression());
	} else if (pSheet->IsCutAtZ()) {
		SetCutAtZ(pSheet->GetCutAtExpression());
	}
}
wxString SheetME::GetBaseTypeClassName() {
	return "SheetME";
}

wxString SheetME::GetUserFriendlyStringRepresentation() {
	bool valid = IsSheetValid();
	if (!valid)
		return "Invalid expression";


	wxString result;
	if (IsCutAtX()) {
		double y = y1Parser.Eval() - y0Parser.Eval(); y = y < 0 ? -y : y;
		double z = z1Parser.Eval()-z0Parser.Eval(); z = z < 0 ? -z : z;

		result.Append("X = ").
				Append(Converter::DoubleToFormattedString(x0Parser.Eval(), 2)).
				Append(", ").
				Append(Converter::DoubleToFormattedString(y, 2)).
				Append(" x ").
				Append(Converter::DoubleToFormattedString(z, 2));

	} else if (IsCutAtY()) {
		double x = x1Parser.Eval()-x0Parser.Eval(); x = x < 0 ? -x : x;
		double z = z1Parser.Eval()-z0Parser.Eval(); z = z < 0 ? -z : z;

		result.Append("Y = ").
				Append(Converter::DoubleToFormattedString(y0Parser.Eval(), 2)).
				Append(", ").
				Append(Converter::DoubleToFormattedString(x, 2)).
				Append(" x ").
				Append(Converter::DoubleToFormattedString(z, 2));
	} else if (IsCutAtZ()) {
		double x = x1Parser.Eval()-x0Parser.Eval(); x = x < 0 ? -x : x;
		double y = y1Parser.Eval()-y0Parser.Eval(); y = y < 0 ? -y : y;

		result.Append("Z = ").
				Append(Converter::DoubleToFormattedString(z0Parser.Eval(), 2)).
				Append(", ").
				Append(Converter::DoubleToFormattedString(x, 2)).
				Append(" x ").
				Append(Converter::DoubleToFormattedString(y, 2));
	}
	return result;
}

void SheetME::SetUserFriendlyStringRepresentation(wxString str) {

}

void SheetME::DoWrite(OutputBuffer& buffer) {

	buffer.WriteInt(plane);
	wxString str = x0Parser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = y0Parser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = z0Parser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = x1Parser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = y1Parser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = z1Parser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
}
void SheetME::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	plane = buffer.ReadInt();
	x0Parser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	y0Parser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	z0Parser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	x1Parser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	y1Parser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	z1Parser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
}
Sheet SheetME::ConvertToSheet() {
	Sheet s;
	EvalExpressions();

	if (IsCutAtX()) {
		s.SetCutAtX(GetCutAt());
		s.SetY0(GetY0());
		s.SetY1(GetY1());
		s.SetZ0(GetZ0());
		s.SetZ1(GetZ1());
	} else if (IsCutAtY()) {
		s.SetCutAtY(GetCutAt());
		s.SetX0(GetX0());
		s.SetX1(GetX1());
		s.SetZ0(GetZ0());
		s.SetZ1(GetZ1());
	} else if (IsCutAtZ()) {
		s.SetCutAtZ(GetCutAt());
		s.SetX0(GetX0());
		s.SetX1(GetX1());
		s.SetY0(GetY0());
		s.SetY1(GetY1());
	}

	return s;
}
