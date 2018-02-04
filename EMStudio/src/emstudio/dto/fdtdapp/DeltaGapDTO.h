/*
 * DeltaGapDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef DELTAGAPDTO_H_
#define DELTAGAPDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "emstudio/gui/basetypes/Excitation.h"

class DeltaGapDTO : public ElementsWithFacetsDTO {
private:
	Excitation excitation;
	double x; double y; double z;
//	double resistance;
	Orientation orientation;
	double initialFrequency;
	double frequencyStep;
	int nFrequency;
//	bool resistiveSource;
public:

	DeltaGapDTO();

    virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual Priority GetPriority();

    Excitation& GetExcitation();
    double GetFrequencyStep() const;
    int GetNFrequency() const;
    double GetInitialFrequency() const;
    Orientation GetOrientation() const;
//    double GetResistance() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
//    bool IsResistiveSource() const;
    void SetExcitation(Excitation excitation);
    void SetFrequencyStep(double frequencyStep);
    void SetNFrequency(int nFrequency);
//    void SetResistiveSource(bool b);
    void SetInitialFrequency(double initialFrequency);
    void SetOrientation(Orientation orientation);
//    void SetResistance(double resistance);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

	virtual ~DeltaGapDTO();
};

#endif /* DELTAGAPDTO_H_ */
