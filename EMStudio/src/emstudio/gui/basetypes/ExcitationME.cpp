/*
 * ExcitationME.cpp
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#include "ExcitationME.h"

ExcitationME::ExcitationME()
	: types(), type(), parameters() {
	SetWriteVersion(1);

	types.Add("Gaussian");
	types.Add("Gaussian Derivative");
	types.Add("Generic");
	types.Add("Ricker Wavelet");
	types.Add("Senoidal");
	parameters.push_back(std::pair<wxString, wxString>("Amplitude", "1"));

	SetType("Gaussian");
}

ExcitationME::~ExcitationME() {

}

int ExcitationME::GetNumberOfParameters() {
	return parameters.size();
}
//void ExcitationME::SetValue(ExcitationME e) {
//	parameters.clear();
//
//	SetType(e.GetType());
//	for (int i = 0; i < e.GetNumberOfParameters(); i++) {
//		parameters.push_back(e.GetParameter(i));
//	}
//}
void ExcitationME::SetType(wxString type) {
	// Salva a amplitude;
	std::pair<wxString, wxString> amplitude;
	if (this->type != "Generic")
		amplitude = parameters[0];
	else
		amplitude = std::pair<wxString, wxString>("Amplitude", "1");

	this->type = type;

	parameters.clear();

	if (type == "Senoidal") {
		parameters.resize(3);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, wxString>("Frequency", "10");
		wxString phase = wxString("Phase (").Append(wxT("\u00B0")).Append(")");
		parameters[2] = std::pair<wxString, wxString>(phase, "0");
	} else if (type == "Gaussian") {
		parameters.resize(2);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, wxString>("Frequency", "10");
	} else if (type == "Generic") {
		parameters.resize(1);
		parameters[0] = std::pair<wxString, wxString>("Equation (MKS)", "1*sin(2*pi*1e9*t)");
	} else if (type == "Gaussian Derivative") {
		parameters.resize(2);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, wxString>("Frequency", "10");
	} else if (type == "Ricker Wavelet") {
		parameters.resize(2);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, wxString>("Frequency", "10");
	}
}

wxString ExcitationME::GetType() {
	return type;
}
wxArrayString ExcitationME::GetTypes() {
	return types;
}

std::vector<std::pair<wxString,wxString> > ExcitationME::GetParameters() {
	return parameters;
}
void ExcitationME::SetParameter(int parameterNumber, wxString parameter) {
	parameters[parameterNumber].second = parameter;
}
std::pair<wxString, wxString> ExcitationME::GetParameter(int parameterNumber) {
	return parameters[parameterNumber];
}

void ExcitationME::SetUserFriendlyStringRepresentation(wxString s) {
	SetType(s);
}
wxString ExcitationME::GetUserFriendlyStringRepresentation() {
	if (IsExcitationValid())
		return GetType();
	else
		return "Invalid expression";
}

void ExcitationME::DoWrite(OutputBuffer& buffer) {
	MathParser mathParser;
	buffer.WriteString(type);

	int size = GetParameters().size();
	buffer.WriteInt(size);

	for (int i = 0; i < size; i++) {
		std::pair<wxString, wxString> p = GetParameters()[i];
		buffer.WriteString(p.first);
		mathParser.SetExpression(p.second);
		wxString expression = mathParser.GetExpressionWithDecimalSeparatorInformation();
		buffer.WriteString(expression);
	}
}
void ExcitationME::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	type = buffer.ReadString();

	int nParam = buffer.ReadInt();

	parameters.clear();
	MathParser mathPaser;
	for (int i = 0; i < nParam; i++) {
		wxString description = buffer.ReadString();
		wxString value = buffer.ReadString();
		mathPaser.SetExpressionWithDecimalSeparatorInformation(value);
		parameters.push_back(std::pair<wxString, wxString>(description, mathPaser.GetExpression()));
	}
}
/* Excitation tem exatamente a mesma estrutura.
 * A diferença é que ele lida diretamente com os dados em double, e não com expressões
 */
bool ExcitationME::IsExcitationValid() {
	MathParser mp;
	mp.DefineConstants();

	if (GetType() == "Generic") {
		mp.DefineVariables();
	}

	for (int i = 0; i < GetNumberOfParameters(); i++) {
		mp.SetExpression(GetParameter(i).second);
		if (! mp.IsValid())
			return false;
	}

	return true;
}
Excitation ExcitationME::ConvertToExcitation() {
	Excitation e;
	e.SetType(GetType());

	if (GetType() == "Generic") {
		e.SetExpressionForGenericExcitation(GetParameter(0).second);
	} else {
		MathParser mp;
		for (int i = 0; i < GetNumberOfParameters(); i++) {
			mp.SetExpression(GetParameter(i).second);
			mp.DefineConstantsAndCheckIfIsValid(); // Necessário para chamar Eval depois
			e.SetParameter(i, mp.Eval());
		}
	}
	return e;
}
void ExcitationME::Copy(BaseType* b) {
	ExcitationME* e = (static_cast<ExcitationME*>(b));

	SetType(e->GetType());
	parameters = e->GetParameters();
}
wxString ExcitationME::GetBaseTypeClassName() {
	return "ExcitationME";
}
