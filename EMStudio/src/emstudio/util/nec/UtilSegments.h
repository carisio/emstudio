/*
 * UtilSegments.h
 *
 *  Created on: 27/05/2014
 *      Author: leandrocarisio
 */

#ifndef UTILSEGMENTS_H_
#define UTILSEGMENTS_H_

#include "Segment.h"

class UtilSegments {
public:
	UtilSegments();
	virtual ~UtilSegments();

	static Segments GetWireSegments(int nseg, double x1, double y1, double z1, double x2, double y2, double z2, double rad);
	static Segments GetHelixSegments(int nseg, double bottomRadius, double topRadius, double length, double spaceBetweenTurns, double rad);
};

#endif /* UTILSEGMENTS_H_ */
