/*
 * DirectionPlaneWaveME.cpp
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWaveME.h"

DirectionPlaneWaveME::DirectionPlaneWaveME() {
	SetWriteVersion(1);
}

DirectionPlaneWaveME::~DirectionPlaneWaveME() {
}

void DirectionPlaneWaveME::SetThetaExpression(wxString theta) {
	thetaParser.SetExpression(theta);
}
void DirectionPlaneWaveME::SetPhiExpression(wxString phi) {
	phiParser.SetExpression(phi);
}
void DirectionPlaneWaveME::SetPsiExpression(wxString psi) {
	psiParser.SetExpression(psi);
}
wxString DirectionPlaneWaveME::GetThetaExpression() {
	return thetaParser.GetExpression();
}
wxString DirectionPlaneWaveME::GetPhiExpression() {
	return phiParser.GetExpression();
}
wxString DirectionPlaneWaveME::GetPsiExpression() {
	return psiParser.GetExpression();
}
bool DirectionPlaneWaveME::isThetaExpressionValid() {
	return thetaParser.DefineConstantsAndCheckIfIsValid();
}
bool DirectionPlaneWaveME::isPhiExpressionValid() {
	return phiParser.DefineConstantsAndCheckIfIsValid();
}
bool DirectionPlaneWaveME::isPsiExpressionValid() {
	return psiParser.DefineConstantsAndCheckIfIsValid();
}
bool DirectionPlaneWaveME::isExpressionsValid() {
	return isThetaExpressionValid() && isPhiExpressionValid() && isPsiExpressionValid();
}
bool DirectionPlaneWaveME::EvalExpressions() {
	return isExpressionsValid();
}
double DirectionPlaneWaveME::GetTheta() const {
	return thetaParser.Eval();
}
double DirectionPlaneWaveME::GetPhi() const {
	return phiParser.Eval();
}
double DirectionPlaneWaveME::GetPsi() const {
	return psiParser.Eval();
}
void DirectionPlaneWaveME::Copy(BaseType* p) {
	SetThetaExpression(((static_cast<DirectionPlaneWaveME*>(p))->GetThetaExpression()));
	SetPhiExpression(((static_cast<DirectionPlaneWaveME*>(p))->GetPhiExpression()));
	SetPsiExpression(((static_cast<DirectionPlaneWaveME*>(p))->GetPsiExpression()));
}
wxString DirectionPlaneWaveME::GetBaseTypeClassName() {
	return "DirectionPlaneWaveME";
}

void DirectionPlaneWaveME::SetUserFriendlyStringRepresentation(wxString str) {

}
wxString DirectionPlaneWaveME::GetUserFriendlyStringRepresentation() {
	if (isExpressionsValid()) {
		wxString result;
//		result.Append(wxT("\u03B8 = ")).
//				Append(Converter::DoubleToFormattedString(GetTheta(), 0)).Append(wxT("\u00B0")).
//				Append(wxT(", \u03D5 = ")).
//				Append(Converter::DoubleToFormattedString(GetPhi(), 0)).Append(wxT("\u00B0")).
//				Append(wxT(", \u03A8 = ")).
//				Append(Converter::DoubleToFormattedString(GetPsi(), 0)).Append(wxT("\u00B0"));
		result.Append(wxT("q = ")).
				Append(Converter::DoubleToFormattedString(GetTheta(), 0)).Append(wxT("\u00B0")).
				Append(wxT(", f = ")).
				Append(Converter::DoubleToFormattedString(GetPhi(), 0)).Append(wxT("\u00B0")).
				Append(wxT(", y = ")).
				Append(Converter::DoubleToFormattedString(GetPsi(), 0)).Append(wxT("\u00B0"));
		return result;
	} else {
		return "Invalid expression";
	}
}

void DirectionPlaneWaveME::DoWrite(OutputBuffer& buffer) {
	wxString str = thetaParser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = phiParser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
	str = psiParser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
}
void DirectionPlaneWaveME::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	thetaParser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	phiParser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
	psiParser.SetExpressionWithDecimalSeparatorInformation(buffer.ReadString());
}
