/*
 * MoMDTO.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef MOMDTO_H_
#define MOMDTO_H_

#include "ElementsWithSegmentsDTO.h"
#include "emstudio/gui/basetypes/Material.h"

namespace mom {

class MoMDTO : public ElementsWithSegmentsDTO {
private:
	bool useExtendedThinWireKernel;
	double initialFrequency;
	double frequencyStep;
	int nFrequency;

	// GroundParameters
	bool hasMedium1;
	Material medium1;
	bool currentsInterpolated;
	bool currentsGoToZero;

	bool hasMedium2;
	Material medium2;
	bool linearCliff;
	bool circularCliff;
	double distBelowGround;
	double distFromOrigin;

	int numberOfRadials;
	double wireLength;
	double wireRadius;
public:
	MoMDTO();
	virtual ~MoMDTO();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();

	bool IsUseExtendedThinWireKernel() const;
	void SetUseExtendedThinWireKernel(bool use);
	double GetFrequencyStep() const;
	int GetNFrequency() const;
	double GetInitialFrequency() const;
    void SetFrequencyStep(double finalFrequency);
    void SetNFrequency(int nFrequency);
    void SetInitialFrequency(double initialFrequency);

	bool IsCircularCliff() const;
	void SetCircularCliff(bool circularCliff);
	bool IsCurrentsGoToZero() const;
	void SetCurrentsGoToZero(bool currentsGoToZero);
	bool IsCurrentsInterpolated() const;
	void SetCurrentsInterpolated(bool currentsInterpolated);
	double GetDistBelowGround() const;
	void SetDistBelowGround(double distBelowGround);
	double GetDistFromOrigin() const;
	void SetDistFromOrigin(double distFromOrigin);
	bool HasMedium1() const;
	void SetHasMedium1(bool hasMedium1);
	bool HasMedium2() const;
	void SetHasMedium2(bool hasMedium2);
	bool IsLinearCliff() const;
	void SetLinearCliff(bool linearCliff);
	int GetNumberOfRadials() const;
	void SetNumberOfRadials(int numberOfRadials);
	double GetWireLength() const;
	void SetWireLength(double wireLength);
	double GetWireRadius() const;
	void SetWireRadius(double wireRadius);

	Material GetMedium1();
	void SetMedium1(Material medium1);
	Material GetMedium2();
	void SetMedium2(Material medium2);

};

} /* namespace mom */
#endif /* MOMDTO_H_ */
