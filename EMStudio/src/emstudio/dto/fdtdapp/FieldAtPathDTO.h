/*
 * FieldAtPathDTO.h
 *
 *  Created on: 21/03/2012
 *      Author: Leandro
 */

#ifndef FIELDATPATHDTO_H_
#define FIELDATPATHDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Orientation.h"

class FieldAtPathDTO : public ElementsWithFacetsDTO {
private:
	double x; double y; double z; double length;
	Orientation orientation;
	double initialFrequency;
	double frequencyStep;
	int nFrequency;
public:
	FieldAtPathDTO();
	virtual ~FieldAtPathDTO();

    double GetLength() const;
    Orientation GetOrientation() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetLength(double length);
    void SetOrientation(Orientation orientation);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

	double GetFrequencyStep() const;
	int GetNFrequency() const;
	double GetInitialFrequency() const;
    void SetFrequencyStep(double finalFrequency);
    void SetNFrequency(int nFrequency);
    void SetInitialFrequency(double initialFrequency);

    virtual Priority GetPriority();
    virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
};

#endif /* FIELDATPATHDTO_H_ */
