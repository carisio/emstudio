/*
 * ColorMap.cpp
 *
 *  Created on: 10/07/2014
 *      Author: leandrocarisio
 */

#include "ColorMap.h"

ColorMap::ColorMap(int colorNumber, double begin, double end)
		: begin(begin), end(end), colors(std::vector<std::pair<Range, wxColour> >()) {
	while (colorNumber % 5 != 0) {
		colorNumber++;
	}
	this->colorNumber = colorNumber;
	CreateMap();
}

void ColorMap::CreateMap() {
	colors = std::vector<std::pair<Range, wxColour> >();

	double deltaX = (end-begin)/colorNumber;
	int i = 0, cont = 0;
	int numberOfColorsInInterval = colorNumber/5;

	for (; i < numberOfColorsInInterval; i++) {
		Range subRange(begin + i*deltaX, begin + (i+1)*deltaX);
		wxColor c(0, 0, 128 + (int)((cont*(128))/numberOfColorsInInterval));
		colors.push_back(std::pair<Range, wxColour>(subRange, c));
		cont++;
	}
	cont = 0;
	for (; i < 2*numberOfColorsInInterval; i++) {
		Range subRange = Range(begin + i*deltaX, begin + (i+1)*deltaX);
		wxColor c(0, (int)((cont*255.0)/numberOfColorsInInterval), 255);
		colors.push_back(std::pair<Range, wxColour>(subRange, c));
		cont++;
	}
	cont = 0;
	for (; i < 3*numberOfColorsInInterval; i++) {
		Range subRange = Range(begin + i*deltaX, begin + (i+1)*deltaX);
		wxColor c((int)((cont*255.0)/numberOfColorsInInterval), 255, 255 - (int)((cont*255.0)/numberOfColorsInInterval));
		colors.push_back(std::pair<Range, wxColour>(subRange, c));
		cont++;
	}
	cont = 0;
	for (; i < 4*numberOfColorsInInterval; i++) {
		Range subRange = Range(begin + i*deltaX, begin + (i+1)*deltaX);
		wxColor c(255, 255 - (int)((cont*255.0)/numberOfColorsInInterval), 0);
		colors.push_back(std::pair<Range, wxColour>(subRange, c));
		cont++;
	}
	cont = 0;
	for (; i < 5*numberOfColorsInInterval; i++) {
		Range subRange = Range(begin + i*deltaX, begin + (i+1)*deltaX);
		if (i == 5*numberOfColorsInInterval-1) {
			// Por conta das divisões entre pontos flutuantes, é necessário criar o último range diretamente até end.
			subRange = Range(begin + i*deltaX, end);
		}
		wxColor c(255 - (int)((cont*(128))/numberOfColorsInInterval) ,0,0);
		colors.push_back(std::pair<Range, wxColour>(subRange, c));
		cont++;
	}
}

wxColour ColorMap::GetColor(double value) {
	wxColour c;
	for (size_t i = 0; i < colors.size(); i++) {
		if (colors[i].first.At(value)) {
			c = colors[i].second;
			break;
		}
	}
	return c;
}
