/*
 * ResultFrame.cpp
 *
 *  Created on: 13/01/2012
 *      Author: leandrocarisio
 */

#include "ResultFrame.h"

ResultFrame::ResultFrame(wxWindow* parent, ResultTree& results, ElementManagerSmartPointer availableElements, HowToShowResultsManagerSmartPointer howToShowResultsManager)
	: wxDialog(parent, wxID_ANY, "Simulation results", wxDefaultPosition, parent->GetSize()*0.80, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX),
	  resultTree(results) {

	mainPanel = new ResultsContainerPanel(this, resultTree, availableElements, howToShowResultsManager);

	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(ResultFrame::Resize));
}

ResultFrame::~ResultFrame() {

}


void ResultFrame::Resize(wxSizeEvent& event) {
	wxSize newSize = this->GetClientSize();
	mainPanel->SetSize(newSize);
}
