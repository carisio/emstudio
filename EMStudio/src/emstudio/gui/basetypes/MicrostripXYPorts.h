/*
 * MicrostripXYPorts.h
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#ifndef MICROSTRIPXYPORTS_H_
#define MICROSTRIPXYPORTS_H_

#include <vector>

class MicrostripXYPorts {
private:
	std::vector<std::pair<double, double> > coordinates;
public:
	MicrostripXYPorts();
	virtual ~MicrostripXYPorts();

	/* Métodos acessores para as coordenadas da placa */
	std::vector<std::pair<double, double> > GetCoordinates();
	void SetCoordinates(std::vector<std::pair<double, double> >);
};

#endif /* MICROSTRIPXYPORTS_H_ */
