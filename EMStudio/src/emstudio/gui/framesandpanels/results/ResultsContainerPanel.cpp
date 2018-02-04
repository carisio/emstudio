/*
 * ResultsContainerPanel.cpp
 *
 *  Created on: 13/01/2012
 *      Author: leandrocarisio
 */

#include "ResultsContainerPanel.h"
#include <iostream>
using namespace::std;

ResultsContainerPanel::ResultsContainerPanel(wxWindow* parent, ResultTree& tree, ElementManagerSmartPointer availableElements, HowToShowResultsManagerSmartPointer howToShowResultsManager, double leftSizeRelation)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize),
	  resultTree(tree),
	  howToShowResultsManagerPtr(howToShowResultsManager),
	  leftSizeRelation(leftSizeRelation) {

	splitter = new wxSplitterWindow(this);
	resultVisualizationPanel = new wxNotebook(splitter, wxID_ANY);
	resultTreeGUI = new ResultTreeCtrl(splitter, wxID_ANY, resultTree, availableElements);
	splitter->SplitVertically(resultTreeGUI, resultVisualizationPanel);
	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(ResultsContainerPanel::Resize));
}

void ResultsContainerPanel::UpdateResultVisualizationPanel(ResultSmartPointer resultSmartPtr) {
//	cout << "Apagando todas as páginas" << endl;
	resultVisualizationPanel->Show(false);
	resultVisualizationPanel->DeleteAllPages();

//	cout << "Pesquisando um HowToShowResults" << endl;
	HowToShowResultsSmartPointer htsr = howToShowResultsManagerPtr->GetHowToShowResultsMap()[resultSmartPtr->GetResultClassName()];
//	cout << "resultSmartPtr->GetName() = " << resultSmartPtr->GetName() << endl;
//	cout << "resultSmartPtr->GetResultClassName() = " << resultSmartPtr->GetResultClassName() << endl;

	htsr->SetResult(resultSmartPtr);

//	cout << "Iterando um HowToShowResults" << endl;
	for (int i = 0; i < htsr->GetNumberOfTabs(); ++i) {
//		cout << "Pegando uma window" << endl;
		wxWindow* page = htsr->GetWindow(i, resultVisualizationPanel);
//		wxWindow* page = new wxPanel;
//		cout << "Pegando um nome" << endl;
		wxString tabName = htsr->GetTabName(i);
//		cout << "Adicionando uma página" << endl;
		resultVisualizationPanel->AddPage(page, tabName);
	}
//	cout << "OK, fechou o update" << endl;
	resultVisualizationPanel->Show(true);
}

void ResultsContainerPanel::Resize(wxSizeEvent& event) {
	wxSize size = event.GetSize();
	int width = size.GetWidth();

	splitter->SetSize(size);
	splitter->SetSashPosition(width*leftSizeRelation);
}

void ResultsContainerPanel::BuildResultsTree() {

}
ResultsContainerPanel::~ResultsContainerPanel() {
}
