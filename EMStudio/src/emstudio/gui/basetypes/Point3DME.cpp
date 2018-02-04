/*
 * Point3DME.cpp
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#include "Point3DME.h"

Point3DME::Point3DME() {
	SetWriteVersion(1);
}

Point3DME::~Point3DME() {
}

void Point3DME::SetXExpression(wxString x) {
	xParser.SetExpression(x);
}
void Point3DME::SetYExpression(wxString y) {
	yParser.SetExpression(y);
}
void Point3DME::SetZExpression(wxString z) {
	zParser.SetExpression(z);
}
wxString Point3DME::GetXExpression() {
	return xParser.GetExpression();
}
wxString Point3DME::GetYExpression() {
	return yParser.GetExpression();
}
wxString Point3DME::GetZExpression() {
	return zParser.GetExpression();
}
bool Point3DME::isXExpressionValid() {
	return xParser.DefineConstantsAndCheckIfIsValid();
}
bool Point3DME::isYExpressionValid() {
	return yParser.DefineConstantsAndCheckIfIsValid();
}
bool Point3DME::isZExpressionValid() {
	return zParser.DefineConstantsAndCheckIfIsValid();
}
bool Point3DME::isPointValid() {
	return isXExpressionValid() && isYExpressionValid() && isZExpressionValid();
}
bool Point3DME::EvalExpressions() {
	return isPointValid();
}

double Point3DME::GetX() const {
	return xParser.Eval();
}
double Point3DME::GetY() const {
	return yParser.Eval();
}
double Point3DME::GetZ() const {
	return zParser.Eval();
}

void Point3DME::Copy(BaseType* p) {
	SetXExpression(((static_cast<Point3DME*>(p))->GetXExpression()));
	SetYExpression(((static_cast<Point3DME*>(p))->GetYExpression()));
	SetZExpression(((static_cast<Point3DME*>(p))->GetZExpression()));
}
wxString Point3DME::GetBaseTypeClassName() {
	return "Point3DME";
}

void Point3DME::SetUserFriendlyStringRepresentation(wxString str) {

}
wxString Point3DME::GetUserFriendlyStringRepresentation() {
	if (isPointValid()) {
		wxString x = Converter::DoubleToFormattedString(GetX(), 2);
		wxString y = Converter::DoubleToFormattedString(GetY(), 2);
		wxString z = Converter::DoubleToFormattedString(GetZ(), 2);

		return "(" + x + " " + y + " " + z + ")";
	} else {
		return "Invalid expression";
	}
}

void Point3DME::DoWrite(OutputBuffer& buffer) {
	wxString str = xParser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = yParser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = zParser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
}
void Point3DME::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	xParser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	yParser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	zParser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
}
