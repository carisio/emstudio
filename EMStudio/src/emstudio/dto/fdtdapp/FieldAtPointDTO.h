/*
 * FieldAtPointDTO.h
 *
 *  Created on: 02/03/2012
 *      Author: Administrador
 */

#ifndef FIELDATPOINTDTO_H_
#define FIELDATPOINTDTO_H_

#include "ElementsWithFacetsDTO.h"

class FieldAtPointDTO : public ElementsWithFacetsDTO {
private:
	double x;
	double y;
	double z;
	double initialFrequency;
	double frequencyStep;
	int nFrequency;
	bool showTimeResponse;

public:
	FieldAtPointDTO();
	virtual ~FieldAtPointDTO();

	double GetX() const;
	double GetY() const;
	double GetZ() const;
	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);

	double GetFrequencyStep() const;
	int GetNFrequency() const;
	double GetInitialFrequency() const;
    void SetFrequencyStep(double finalFrequency);
    void SetNFrequency(int nFrequency);
    void SetInitialFrequency(double initialFrequency);
    void SetShowTimeResponse(bool t);
    bool IsShowTimeResponse() const;
    virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual Priority GetPriority();
};

#endif /* FIELDATPOINTDTO_H_ */
