/*
 * DipoleDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef DIPOLEDTO_H_
#define DIPOLEDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "emstudio/gui/basetypes/Orientation.h"

class DipoleDTO : public ElementsWithFacetsDTO {
private:
	double x;
	double y;
	double z;
	double length;
	Orientation orientation;
	Excitation excitation;
	int linePoints;
	int sourcePoints;
	double wireRadius;
	double lineImpedance;
	double initialFrequency;
	double frequencyStep;
	int nFrequency;

public:
	DipoleDTO();

	Orientation GetOrientation() const;
    Excitation& GetExcitation();
    double GetFrequencyStep() const;
    int GetNFrequency() const;
    double GetInitialFrequency() const;
    double GetLength() const;
    double GetLineImpedance() const;
    int GetLinePoints() const;
    int GetSourcePoints() const;
    double GetWireRadius() const;
    double GetX() const;
    double GetY() const;
    double GetZ() const;
    void SetOrientation(Orientation o);
    void SetExcitation(Excitation e);
    void SetFrequencyStep(double frequencyStep);
    void SetNFrequency(int frequency);
    void SetInitialFrequency(double initialFrequency);
    void SetLength(double length);
    void SetLineImpedance(double lineImpedance);
    void SetLinePoints(int linePoints);
    void SetSourcePoints(int sourcePoints);
    void SetWireRadius(double wireRadius);
    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual Priority GetPriority();

	virtual ~DipoleDTO();
};

#endif /* DIPOLEDTO_H_ */
