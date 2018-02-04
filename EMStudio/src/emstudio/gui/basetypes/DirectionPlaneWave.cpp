/*
 * DirectionPlaneWave.cpp
 *
 *  Created on: 20/11/2012
 *      Author: leandrocarisio
 */

#include "DirectionPlaneWave.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

DirectionPlaneWave::DirectionPlaneWave()
	: theta(0), phi(0), psi(0) {
	SetWriteVersion(1);
}

DirectionPlaneWave::~DirectionPlaneWave() {
}

double DirectionPlaneWave::GetTheta() {
	return theta;
}
double DirectionPlaneWave::GetPhi() {
	return phi;
}
double DirectionPlaneWave::GetPsi() {
	return psi;
}
void DirectionPlaneWave::SetTheta(double d) {
	theta = d;
}
void DirectionPlaneWave::SetPhi(double d) {
	phi = d;
}
void DirectionPlaneWave::SetPsi(double d) {
	psi = d;
}

void DirectionPlaneWave::Copy(BaseType* p) {
	DirectionPlaneWave* pDirectionPlaneWave = static_cast<DirectionPlaneWave*>(p);

	SetTheta(pDirectionPlaneWave->GetTheta());
	SetPhi(pDirectionPlaneWave->GetPhi());
	SetPsi(pDirectionPlaneWave->GetPsi());
}
wxString DirectionPlaneWave::GetBaseTypeClassName() {
	return "DirectionPlaneWave";
}

wxString DirectionPlaneWave::GetUserFriendlyStringRepresentation() {
	wxString result;
//	result.Append(wxT("\u03B8 = ")).
//			Append(Converter::DoubleToFormattedString(theta, 0)).Append(wxT("\u00B0")).
//			Append(wxT(", \u03D5 = ")).
//			Append(Converter::DoubleToFormattedString(phi, 0)).Append(wxT("\u00B0")).
//			Append(wxT(", \u03A8 = ")).
//			Append(Converter::DoubleToFormattedString(psi, 0)).Append(wxT("\u00B0"));
	result.Append(wxT("q = ")).
			Append(Converter::DoubleToFormattedString(GetTheta(), 0)).Append(wxT("\u00B0")).
			Append(wxT(", f = ")).
			Append(Converter::DoubleToFormattedString(GetPhi(), 0)).Append(wxT("\u00B0")).
			Append(wxT(", y = ")).
			Append(Converter::DoubleToFormattedString(GetPsi(), 0)).Append(wxT("\u00B0"));
	return result;
}

void DirectionPlaneWave::SetUserFriendlyStringRepresentation(wxString str) {

}
void DirectionPlaneWave::DoWrite(OutputBuffer& buffer) {
	buffer.WriteDouble(theta);
	buffer.WriteDouble(phi);
	buffer.WriteDouble(psi);
}
void DirectionPlaneWave::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	theta = buffer.ReadDouble();
	phi = buffer.ReadDouble();
	psi = buffer.ReadDouble();
}
