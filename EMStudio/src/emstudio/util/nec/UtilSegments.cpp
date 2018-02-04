/*
 * UtilSegments.cpp
 *
 *  Created on: 27/05/2014
 *      Author: leandrocarisio
 */

#include "UtilSegments.h"
#include "code/c_geometry.h"
#include "code/nec_context.h"
#include "code/nec_exception.h"

#include <iostream>
using namespace::std;

UtilSegments::UtilSegments() {

}

UtilSegments::~UtilSegments() {
}

Segments UtilSegments::GetWireSegments(int nseg, double x1, double y1, double z1, double x2, double y2, double z2, double rad) {
	nec_context nec;
	nec.initialize();
	c_geometry* geo = nec.get_geometry();
//	cout << "Util: Pegou geo: " << geo << endl;
	geo->wire(1, nseg, x1, y1, z1, x2, y2, z2, rad, 1, 1);

	Segments segs;
	for (int i = 0; i < geo->x.size(); i++) {
		Segment s = Segment(Rvector3(geo->x[i], geo->y[i], geo->z[i]), Rvector3(geo->x2[i], geo->y2[i], geo->z2[i]), rad);
		segs.push_back(s);
	}

//	nec.geometry_complete(0,0);
//	nec.fr_card(0, 20, 200, 5);
//	nec.ex_card(EXCITATION_VOLTAGE, 1, 5, 0, 1, 0, 0, 0, 0, 0);
//	nec.xq_card(0);
	return segs;
}

Segments UtilSegments::GetHelixSegments(int nseg, double bottomRadius, double topRadius, double length, double spaceBetweenTurns, double rad) {
	nec_context nec;
	nec.initialize();
	c_geometry* geo = nec.get_geometry();
	geo->helix(spaceBetweenTurns, length, bottomRadius, bottomRadius, topRadius, topRadius, rad, nseg, 0);

	Segments segs;
	for (int i = 0; i < geo->x.size(); i++) {
		Segment s = Segment(Rvector3(geo->x[i], geo->y[i], geo->z[i]), Rvector3(geo->x2[i], geo->y2[i], geo->z2[i]), rad);
		segs.push_back(s);
	}
	return segs;
}
