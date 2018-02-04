/*
 * MonopoleDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef MONOPOLEDTO_H_
#define MONOPOLEDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "emstudio/gui/basetypes/Orientation.h"

class MonopoleDTO : public ElementsWithFacetsDTO {
private:
	Excitation excitation;
	double x;
	double y;
	double z;
	double length;
	Orientation orientation;
	int linePoints;
	int sourcePoints;
	double wireRadius;
	double lineImpedance;
//	double velocityFactor;
	double initialFrequency;
	double frequencyStep;
	int nFrequency;
public:
	MonopoleDTO();

    virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual Priority GetPriority();

	virtual ~MonopoleDTO();

    Excitation& GetExcitation();
    double GetFrequencyStep() const;
    int GetNFrequency() const;
    double GetInitialFrequency() const;
    double GetLength() const;
    double GetLineImpedance() const;
    int GetLinePoints() const;
    Orientation GetOrientation() const;
    int GetSourcePoints() const;
//    double GetVelocityFactor() const;
    double GetWireRadius() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetExcitation(Excitation excitation);
    void SetFrequencyStep(double finalFrequency);
    void SetNFrequency(int frequency);
    void SetInitialFrequency(double initialFrequency);
    void SetLength(double length);
    void SetLineImpedance(double lineImpedance);
    void SetLinePoints(int linePoints);
    void SetOrientation(Orientation orientation);
    void SetSourcePoints(int sourcePoints);
//    void SetVelocityFactor(double velocityFactor);
    void SetWireRadius(double wireRadius);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);
};

#endif /* MONOPOLEDTO_H_ */
