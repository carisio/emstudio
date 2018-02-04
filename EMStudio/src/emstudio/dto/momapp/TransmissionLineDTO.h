/*
 * TransmissionLineDTO.h
 *
 *  Created on: 06/06/2014
 *      Author: leandrocarisio
 */

#ifndef TRANSMISSIONLINEDTO_H_
#define TRANSMISSIONLINEDTO_H_

#include "ElementsWithSegmentsDTO.h"
#include "emstudio/util/vector/Rvector3.h"

namespace mom {

class TransmissionLineDTO : public ElementsWithSegmentsDTO {
private:
	Rvector3 port1, port2;
	double impedance, length;
	double admittanceRealPort1, admittanceImagPort1;
	double admittanceRealPort2, admittanceImagPort2;
public:
	TransmissionLineDTO();
	virtual ~TransmissionLineDTO();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();


	double GetAdmittanceImagPort1();
	void SetAdmittanceImagPort1(double admittanceImagPort1);
	double GetAdmittanceImagPort2();
	void SetAdmittanceImagPort2(double admittanceImagPort2);
	double GetAdmittanceRealPort1();
	void SetAdmittanceRealPort1(double admittanceRealPort1);
	double GetAdmittanceRealPort2();
	void SetAdmittanceRealPort2(double admittanceRealPort2);
	double GetImpedance();
	void SetImpedance(double impedance);
	double GetLength();
	void SetLength(double length);
	Rvector3& GetPort1();
	void SetPort1(Rvector3 port1);
	Rvector3& GetPort2();
	void SetPort2(Rvector3 port2);
};

} /* namespace mom */
#endif /* TRANSMISSIONLINEDTO_H_ */
