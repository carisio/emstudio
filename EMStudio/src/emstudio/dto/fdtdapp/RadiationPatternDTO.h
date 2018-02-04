/*
 * RadiationPatternDTO.h
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#ifndef RADIATIONPATTERNDTO_H_
#define RADIATIONPATTERNDTO_H_

#include "ElementsWithFacetsDTO.h"

class RadiationPatternDTO : public ElementsWithFacetsDTO {
private:
	double initialFrequency;
	double frequencyStep;
	int nFrequency;

	double xmin;
	double xmax;
	double ymin;
	double ymax;
	double zmin;
	double zmax;
public:
	RadiationPatternDTO();

	virtual wxString GetDTOClassName();
	virtual void DoUnnormalize(Units units);
	virtual Priority GetPriority();

	double GetFrequencyStep() const;
	int GetNFrequency() const;
	double GetInitialFrequency() const;
    void SetFrequencyStep(double finalFrequency);
    void SetNFrequency(int nFrequency);
    void SetInitialFrequency(double initialFrequency);

    double GetXmax() const;
    double GetXmin() const;
    double GetYmax() const;
    double GetYmin() const;
    double GetZmax() const;
    double GetZmin() const;
    void SetXmax(double xmax);
    void SetXmin(double xmin);
    void SetYmax(double ymax);
    void SetYmin(double ymin);
    void SetZmax(double zmax);
    void SetZmin(double zmin);
	virtual ~RadiationPatternDTO();
};

#endif /* RADIATIONPATTERNDTO_H_ */
