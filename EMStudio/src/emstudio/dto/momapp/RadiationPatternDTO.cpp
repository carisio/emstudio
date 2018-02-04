/*
 * RadiationPatternDTO.cpp
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#include "RadiationPatternDTO.h"

namespace mom {

RadiationPatternDTO::RadiationPatternDTO() {

}

RadiationPatternDTO::~RadiationPatternDTO() {
}

void RadiationPatternDTO::DoUnnormalize(Units units) {
	// No caso do NEC, espera-se que os dados de frequência sejam informados em MHz para a camada Core.

	double frequency = units.GetUserDefinedFrequencyUnit().second;
	double space = units.GetUserDefinedSpaceUnit().second;

	SetInitialFrequency(GetInitialFrequency() * frequency / 1e6);
	SetFrequencyStep(GetFrequencyStep() * frequency / 1e6);

}
wxString RadiationPatternDTO::GetDTOClassName() {
	return "mom::RadiationPatternDTO";
}

double RadiationPatternDTO::GetFrequencyStep() const {
    return frequencyStep;
}

int RadiationPatternDTO::GetNFrequency() const {
    return nFrequency;
}

double RadiationPatternDTO::GetInitialFrequency() const {
    return initialFrequency;
}


void RadiationPatternDTO::SetFrequencyStep(double frequencyStep) {
    this->frequencyStep = frequencyStep;
}

void RadiationPatternDTO::SetNFrequency(int nFrequency) {
    this->nFrequency = nFrequency;
}

void RadiationPatternDTO::SetInitialFrequency(double initialFrequency) {
    this->initialFrequency = initialFrequency;
}

} /* namespace mom */
