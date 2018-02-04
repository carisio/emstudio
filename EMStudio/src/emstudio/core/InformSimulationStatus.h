/*
 * InformSimulationStatus.h
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#ifndef INFORMSIMULATIONSTATUS_H_
#define INFORMSIMULATIONSTATUS_H_

#include <tr1/memory>

class InformSimulationStatus;
typedef std::tr1::shared_ptr<InformSimulationStatus> InformSimulationStatusSmartPointer;

class InformSimulationStatus {
public:
	InformSimulationStatus();
	virtual ~InformSimulationStatus();

	virtual int GetPercentage() = 0;
	virtual bool SimulationWasCanceled() = 0;
	virtual bool Update(int percentage) = 0;
	virtual void StartSimulation(std::string name) = 0;
	virtual bool InformStatus(std::string newMessage) = 0;
};

#endif /* INFORMSIMULATIONSTATUS_H_ */
