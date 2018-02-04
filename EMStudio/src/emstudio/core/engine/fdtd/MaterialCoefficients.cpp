/*
 * MaterialCoefficients.cpp
 *
 *  Created on: 23/04/2012
 *      Author: leandrocarisio
 */

#include "MaterialCoefficients.h"
#include "emstudio/util/constants/Constants.h"

MaterialCoefficients::MaterialCoefficients(Material& m, double dt) {
    if (m.IsPec()) {
        gax = 0;
        gbx = 1.0;

        gay = 0;
        gby = 1.0;

        gaz = 0;
        gbz = 1.0;
    } else {
    	cout << "---------------------" << endl;
    	cout << "MaterialCoefficients" << endl;
    	cout << "m.GetEx() = " << m.GetEx() << endl;
    	cout << "m.GetEy() = " << m.GetEy() << endl;
    	cout << "m.GetEz() = " << m.GetEz() << endl;
    	cout << "m.GetSx() = " << m.GetSx() << endl;
    	cout << "m.GetSy() = " << m.GetSy() << endl;
    	cout << "m.GetSz() = " << m.GetSz() << endl;
        gax = 1.0/(m.GetEx()+m.GetSx()*dt/EPS0);
        gbx = m.GetSx()*dt/EPS0;

        gay = 1.0/(m.GetEy()+m.GetSy()*dt/EPS0);
        gby = m.GetSy()*dt/EPS0;

        gaz = 1.0/(m.GetEz()+m.GetSz()*dt/EPS0);
        gbz = m.GetSz()*dt/EPS0;
    }

    material = m;
}

MaterialCoefficients::~MaterialCoefficients() {
}

const double& MaterialCoefficients::GetGax() const {
	return gax;
}
const double& MaterialCoefficients::GetGay() const {
	return gay;
}
const double& MaterialCoefficients::GetGaz() const {
	return gaz;
}
const double& MaterialCoefficients::GetGbx() const {
	return gbx;
}
const double& MaterialCoefficients::GetGby() const {
	return gby;
}
const double& MaterialCoefficients::GetGbz() const {
	return gbz;
}
wxString MaterialCoefficients::GetName() {
	return material.GetDescription();
}
const Material& MaterialCoefficients::GetMaterial() const {
	return material;
}
