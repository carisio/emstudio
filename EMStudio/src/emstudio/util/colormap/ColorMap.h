/*
 * ColorMap.h
 *
 *  Created on: 10/07/2014
 *      Author: leandrocarisio
 */

#ifndef COLORMAP_H_
#define COLORMAP_H_

#include "wx/wx.h"
#include <vector>

class Range {
private:
	double begin;
	double end;
public:
	Range(double b, double e) { begin = b; end = e; }
	bool At(double d) { return d <= end && d >= begin; }
};

class ColorMap {
private:
	int colorNumber;
	double begin;
	double end;
	std::vector<std::pair<Range, wxColour> > colors;

	void CreateMap();
public:
	ColorMap(int colorNumber = 5, double begin = 0, double end = 1);
	wxColour GetColor(double value);
	double Min() {return begin;}
	double Max() {return end;}
};

#endif /* COLORMAP_H_ */
