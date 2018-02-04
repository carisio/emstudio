/*
 * InformStatusAsProgressBar.cpp
 *
 *  Created on: 07/04/2015
 *      Author: leandrocarisio
 */

#include "InformSimulationStatusAsProgressBar.h"
#include <iostream>

InformSimulationStatusAsProgressBar::InformSimulationStatusAsProgressBar() {

}

InformSimulationStatusAsProgressBar::~InformSimulationStatusAsProgressBar() {
	if (dialog) {
		delete dialog;
		dialog = 0;
	}
}

void InformSimulationStatusAsProgressBar::StartSimulation(std::string name) {
	dialog = new wxProgressDialog("Simulation progress", "Simulating " + name, 100, NULL,
			wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME |
			wxPD_AUTO_HIDE | wxPD_APP_MODAL);
	dialog->Show(true);
	dialog->Update(0);
}
bool InformSimulationStatusAsProgressBar::Update(int percentage) {
	// ret = false se o usuário clicar no botão cancelar
	std::cout << "InformSimulationStatusAsProgressBar::Update = " << percentage << std::endl;
	bool ret = dialog->Update(percentage);
	return ret;
}

bool InformSimulationStatusAsProgressBar::SimulationWasCanceled() {
	return dialog->WasCancelled();
}

bool InformSimulationStatusAsProgressBar::InformStatus(std::string newMessage) {
	// Se o usuário tiver clicado no botão cancelar, o retorno é false
	return dialog->Update(dialog->GetValue(), newMessage);
}

int InformSimulationStatusAsProgressBar::GetPercentage() {
	return dialog->GetValue();
}

