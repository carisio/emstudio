/*
 * TransmissionLineDTO.cpp
 *
 *  Created on: 06/06/2014
 *      Author: leandrocarisio
 */

#include "TransmissionLineDTO.h"

namespace mom {

TransmissionLineDTO::TransmissionLineDTO() {

}
TransmissionLineDTO::~TransmissionLineDTO() {

}
void TransmissionLineDTO::DoUnnormalize(Units units) {
	double space = units.GetUserDefinedSpaceUnit().second;
	SetPort1(GetPort1() * space);
	SetPort2(GetPort2() * space);
	SetLength(GetLength() * space);
}
wxString TransmissionLineDTO::GetDTOClassName() {
	return "mom::TransmissionLineDTO";
}

double TransmissionLineDTO::GetAdmittanceImagPort1()  {
	return admittanceImagPort1;
}

void TransmissionLineDTO::SetAdmittanceImagPort1(double admittanceImagPort1) {
	this->admittanceImagPort1 = admittanceImagPort1;
}

double TransmissionLineDTO::GetAdmittanceImagPort2()  {
	return admittanceImagPort2;
}

void TransmissionLineDTO::SetAdmittanceImagPort2(double admittanceImagPort2) {
	this->admittanceImagPort2 = admittanceImagPort2;
}

double TransmissionLineDTO::GetAdmittanceRealPort1()  {
	return admittanceRealPort1;
}

void TransmissionLineDTO::SetAdmittanceRealPort1(double admittanceRealPort1) {
	this->admittanceRealPort1 = admittanceRealPort1;
}

double TransmissionLineDTO::GetAdmittanceRealPort2()  {
	return admittanceRealPort2;
}

void TransmissionLineDTO::SetAdmittanceRealPort2(double admittanceRealPort2) {
	this->admittanceRealPort2 = admittanceRealPort2;
}

double TransmissionLineDTO::GetImpedance()  {
	return impedance;
}

void TransmissionLineDTO::SetImpedance(double impedance) {
	this->impedance = impedance;
}

double TransmissionLineDTO::GetLength()  {
	return length;
}

void TransmissionLineDTO::SetLength(double length) {
	this->length = length;
}

 Rvector3& TransmissionLineDTO::GetPort1()  {
	return port1;
}

void TransmissionLineDTO::SetPort1(Rvector3 port1) {
	this->port1 = port1;
}

 Rvector3& TransmissionLineDTO::GetPort2()  {
	return port2;
}

void TransmissionLineDTO::SetPort2(Rvector3 port2) {
	this->port2 = port2;
}

} /* namespace mom */
