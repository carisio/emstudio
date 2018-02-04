/*
 * GeneralSourceDTO.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef MICROSTRIPDTO_H_
#define MICROSTRIPDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/Material.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"
#include "emstudio/gui/basetypes/MicrostripXYPorts.h"

class MicrostripDTO : public ElementsWithFacetsDTO {
private:
	double x1;
	double y1;
	double z1;
	double x2;
	double y2;
	double z2;
	Excitation excitation;
	int linePoints;
	int sourcePoint;
	double lineImpedance;
	double initialFrequency;
	double frequencyStep;
	int nFrequency;
	double linePositionX;
	double lineLength;
	double lineWidth;
	bool pecUnderSubstrate;
	MatchWithPML matchWithPML;
	MicrostripXYPorts ports;
public:
	MicrostripDTO();
	virtual wxString GetDTOClassName();
	virtual void DoUnnormalize(Units units);

    double GetX1() const;
    double GetX2() const;
    double GetY1() const;
    double GetY2() const;
    double GetZ1() const;
    double GetZ2() const;
    void SetX1(double x1);
    void SetX2(double x2);
    void SetY1(double y1);
    void SetY2(double y2);
    void SetZ1(double z1);
    void SetZ2(double z2);

    MatchWithPML GetMatchWithPML();
    void SetMatchWithPML(MatchWithPML m);

    Excitation& GetExcitation();
    double GetFrequencyStep() const;
    int GetNFrequency() const;
    double GetInitialFrequency() const;
    void SetExcitation(Excitation e);
	void SetFrequencyStep(double frequencyStep);
	void SetNFrequency(int frequency);
	void SetInitialFrequency(double initialFrequency);

	double GetLinePositionX() const;
	double GetLineLength() const;
	double GetLineWidth() const;
	void SetLinePositionX(double linePosition);
	void SetLineLength(double lineLength);
	void SetLineWidth(double lineWidth);

    int GetLinePoints() const;
    int GetSourcePoint() const;
    double GetLineImpedance() const;
    void SetLinePoints(int linePoints);
    void SetSourcePoint(int sourcePoints);
    void SetLineImpedance(double lineImpedance);

	void SetPecUnderSubstrate(bool yn);
	bool IsPecUnderSubstrate();

	void SetPorts(MicrostripXYPorts ports);
	MicrostripXYPorts GetPorts();

	virtual ~MicrostripDTO();
};

#endif /* MICROSTRIPDTO_H_ */
