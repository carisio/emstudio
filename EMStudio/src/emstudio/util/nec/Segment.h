/*
 * Segment.h
 *
 *  Created on: 28/05/2014
 *      Author: leandrocarisio
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <vector>
#include "emstudio/util/vector/Rvector3.h"

class Segment;

typedef std::vector<Segment> Segments;

class Segment {
private:
	Rvector3 p1, p2;
	double radius;
public:
	Segment(Rvector3 p1 = Rvector3 (0,0,0), Rvector3 p2 = Rvector3(1,1,1), double radius = 0.01);
	virtual ~Segment();

	void MultiplyByConstant(double c);
	void SetP1(Rvector3& p1);
	void SetP2(Rvector3& p1);
	void SetRadius(double& radius);
	Rvector3 GetP1();
	Rvector3 GetP2();
	double GetRadius();
	double GetDistanceToCenter(double x, double y, double z);
};

#endif /* SEGMENT_H_ */
