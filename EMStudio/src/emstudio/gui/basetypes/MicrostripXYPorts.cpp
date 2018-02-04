/*
 * MicrostripXYPorts.cpp
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#include "MicrostripXYPorts.h"

MicrostripXYPorts::MicrostripXYPorts() : coordinates() {

}

MicrostripXYPorts::~MicrostripXYPorts() {
}

/* Métodos acessores para as coordenadas da placa */
std::vector<std::pair<double, double> > MicrostripXYPorts::GetCoordinates() {
	return coordinates;
}
void MicrostripXYPorts::SetCoordinates(std::vector<std::pair<double, double> > coor) {
	coordinates = coor;
}
