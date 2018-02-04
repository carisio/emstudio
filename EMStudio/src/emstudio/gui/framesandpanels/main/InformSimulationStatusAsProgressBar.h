/*
 * InformStatusAsProgressBar.h
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#ifndef INFORMSTATUSASPROGRESSBAR_H_
#define INFORMSTATUSASPROGRESSBAR_H_

#include "wx/progdlg.h"
#include "emstudio/core/InformSimulationStatus.h"

class InformSimulationStatusAsProgressBar : public InformSimulationStatus {
private:
	wxProgressDialog* dialog;
public:
	InformSimulationStatusAsProgressBar();
	virtual ~InformSimulationStatusAsProgressBar();

	virtual bool SimulationWasCanceled();
	virtual bool Update(int percentage);
	virtual void StartSimulation(std::string name);
	virtual bool InformStatus(std::string newMessage);
	virtual int GetPercentage();
};

#endif /* INFORMSTATUSASPROGRESSBAR_H_ */
