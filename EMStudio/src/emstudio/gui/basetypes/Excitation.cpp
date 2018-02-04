/*
 * Excitation.cpp
 *
 *  Created on: 03/10/2011
 *      Author: leandrocarisio
 */

#include "Excitation.h"

Excitation::Excitation()
	: types(), type(), parameters() {
	types.Add("Gaussian");
	types.Add("Gaussian Derivative");
	types.Add("Generic");
	types.Add("Ricker Wavelet");
	types.Add("Senoidal");
	parameters.push_back(std::pair<wxString, double>("Amplitude", 1.0));

	SetType("Gaussian");
}

Excitation::~Excitation() {

}

int Excitation::GetNumberOfParameters() {
	return parameters.size();
}
void Excitation::SetExpressionForGenericExcitation(wxString s) {
	genericExcitation.SetExpression(s);
}
void Excitation::SetType(wxString type) {
	this->type = type;

	// Salva a amplitude;
	std::pair<wxString, double> amplitude = parameters[0];
	parameters.clear();

	if (type == "Senoidal") {
		parameters.resize(3);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, double>("Frequency", 10);
		wxString phase = wxString("Phase (").Append(wxT("\u00B0")).Append(")");
		parameters[2] = std::pair<wxString, double>(phase, 0);
	} else if (type == "Gaussian") {
		parameters.resize(2);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, double>("Frequency", 10);
//		parameters[1] = std::pair<wxString, double>("Initial time", 0.17);
//		parameters[2] = std::pair<wxString, double>("Duration", 0.0397886);
	} else if (type == "Generic") {
		parameters.resize(0);
	} else if (type == "Gaussian Derivative") {
		parameters.resize(2);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, double>("Frequency", 10);
	} else if (type == "Ricker Wavelet") {
		parameters.resize(2);
		parameters[0] = amplitude;
		parameters[1] = std::pair<wxString, double>("Frequency", 10);
	}
}
double Excitation::GetExcitationValue(double t) {
	// TODO: PRA TIRAR ESSE IF, O SETTYPE TEM QUE CONFIGURAR UM PONTEIRO PARA UMA FUNÇÃO
	// POR ENQUANTO ESTÁ ASSIM SÓ PRA TESTAR.

	if (type == "Senoidal") {
		double amplitude = parameters[0].second;
		double frequency = parameters[1].second;
		double phase = parameters[2].second;
		double alfa = 0.35;
		return amplitude*pow((1. - exp(-alfa*2*PI*frequency*t)),2)*sin(2*PI*frequency*t + phase*PI/180);
	} else if (type == "Gaussian") {
		double amplitude = parameters[0].second;
		double frequency = parameters[1].second;
		return amplitude*exp(-pow( (6.0*frequency*t/1.35 - 3.0) ,2));
	} else if (type == "Generic") {
		genericExcitation.ChangeVariable("t", t);
		genericExcitation.IsValid();
		return genericExcitation.Eval();
	} else if (type == "Gaussian Derivative") {
		double amplitude = parameters[0].second;
		double frequency = parameters[1].second;
		return -2.33*amplitude*(6*frequency*t/1.35 - 3.)*exp(-pow(6*frequency*t/1.35 - 3., 2));
	} else if (type == "Ricker Wavelet") {
		double amplitude = parameters[0].second;
		double frequency = parameters[1].second;
		double tr = 1.0/frequency;
		return amplitude*(1. - 2.*pow(PI*frequency*(t - tr),2))*exp(-pow(PI*frequency*(t - tr),2));
	}
	return 0;
}
double Excitation::GetMaximumFrequency() {
	double frequency = 0;
	if (type == "Senoidal") {
		frequency = parameters[1].second;
	} else if (type == "Gaussian") {
		frequency = parameters[1].second;
	} else if (type == "Gaussian Derivative") {
		frequency = parameters[1].second;
	} else if (type == "Ricker Wavelet") {
		frequency = parameters[1].second;
	}
	return frequency;
}
void Excitation::Init() {
	if (type != "Generic")
		return;

	genericExcitation.DefineConstants();
	genericExcitation.DefineVariables();
}
void Excitation::Unnormalize(Units units) {
	//	double time = units.GetUserDefinedTimeUnit().second;
	double frequency = units.GetUserDefinedFrequencyUnit().second;

	if (type == "Senoidal") {
		SetParameter(1, GetParameter(1).second * frequency);
	} else if (type == "Gaussian") {
		SetParameter(1, GetParameter(1).second * frequency);
//		SetParameter(2, GetParameter(2).second * time);
	} else if (type == "Gaussian Derivative") {
		SetParameter(1, GetParameter(1).second * frequency);
	} else if (type == "Generic") {
		// Don't do anything
	} else if (type == "Ricker Wavelet") {
		SetParameter(1, GetParameter(1).second * frequency);
	}
}

wxString Excitation::GetType() {
	return type;
}
wxArrayString Excitation::GetTypes() {
	return types;
}

std::vector<std::pair<wxString,double> > Excitation::GetParameters() {
	return parameters;
}
//void Excitation::SetParameter(int parameterNumber, std::pair<wxString, double> parameter) {
//	parameters[parameterNumber] = parameter;
//}
void Excitation::SetParameter(int parameterNumber, double parameter) {
	parameters[parameterNumber].second = parameter;
}
std::pair<wxString, double> Excitation::GetParameter(int parameterNumber) {
	return parameters[parameterNumber];
}
