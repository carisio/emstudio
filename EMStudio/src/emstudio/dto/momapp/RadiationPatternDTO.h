/*
 * RadiationPatternDTO.h
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#ifndef RADIATIONPATTERNDTO_H_
#define RADIATIONPATTERNDTO_H_

#include "ElementsWithSegmentsDTO.h"

namespace mom {

class RadiationPatternDTO : public ElementsWithSegmentsDTO {
private:
	double initialFrequency;
	double frequencyStep;
	int nFrequency;

public:
	RadiationPatternDTO();
	virtual ~RadiationPatternDTO();

	double GetFrequencyStep() const;
	int GetNFrequency() const;
	double GetInitialFrequency() const;
    void SetFrequencyStep(double finalFrequency);
    void SetNFrequency(int nFrequency);
    void SetInitialFrequency(double initialFrequency);

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
};

} /* namespace mom */
#endif /* RADIATIONPATTERNDTO_H_ */
