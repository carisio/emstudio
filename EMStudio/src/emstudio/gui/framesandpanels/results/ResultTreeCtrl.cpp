/*
 * ResultTreeCtrl.cpp
 *
 *  Created on: 13/01/2012
 *      Author: leandrocarisio
 */

#include "ResultTreeCtrl.h"
#include "emstudio/util/dialogs/UtilDialog.h"
#include "emstudio/util/file/FileManager.h"
#include "ResultsContainerPanel.h"

#include <iostream>
using namespace::std;

ResultTreeCtrl::ResultTreeCtrl(wxWindow* parent, wxWindowID id, ResultTree& tree, ElementManagerSmartPointer availableElements)
	: wxTreeCtrl(parent, id),
	  popupMenu(0),
	  resultsTree(tree),
	  availableElements(availableElements) {

	this->icons = new wxImageList(16, 16, 0);
	SetImageList(icons);

	BuildTree();

	Connect(this->GetId(), wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(ResultTreeCtrl::ResultSelected));
	Connect(this->GetId(), wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler(ResultTreeCtrl::OnItemRightClick));
}
void ResultTreeCtrl::OnItemRightClick(wxTreeEvent& event) {
	wxTreeItemId itemId = event.GetItem();
	ResultItemsTree *item = (ResultItemsTree *)GetItemData(itemId);
	if (! (item->IsLeaf()))
		return;

	resultToExport = item->GetResult();
	wxString textMenu = "Export ";
	textMenu.Append(resultToExport->GetName()).Append(" to...");

	if (popupMenu) {
		delete popupMenu;
	}
	popupMenu = new wxMenu;
	wxMenuItem* menuItem = popupMenu->Append(wxID_ANY, textMenu);
	Connect(menuItem->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ResultTreeCtrl::OnExportResultsTo));

	PopupMenu(popupMenu, event.GetPoint());
}
void ResultTreeCtrl::OnExportResultsTo(wxCommandEvent& event) {
	wxString fileName = FileManager::ShowFileDialog(this, wxT("Save"), wxT("Text files (*.txt)|*.txt"), wxFD_SAVE);

	if (fileName == FileManager::FILE_NOT_CHOOSEN) {
		return;
	}

	bool exportOk = resultToExport->ExportData(fileName);

	if (exportOk) {
		wxString msg = resultToExport->GetName();
		msg.Append(" exported to ").Append(fileName);
		UtilDialog::ShowInfoMessage(msg, "Result exported");
	} else {
		wxString msg = "Error exporting ";
		msg.Append(resultToExport->GetName()).
				Append(" to ").Append(fileName);
		UtilDialog::ShowErrorMessage(msg, "Error");
	}
}
void ResultTreeCtrl::ResultSelected(wxTreeEvent& event) {
	ResultsContainerPanel* resultsContainerPanel = static_cast<ResultsContainerPanel*>(GetParent()->GetParent());

    wxTreeItemId itemId = event.GetItem();
    ResultItemsTree *item = (ResultItemsTree *)GetItemData(itemId);
    if (item->IsLeaf()) {
    	ResultSmartPointer e = item->GetResult();
    	resultsContainerPanel->UpdateResultVisualizationPanel(e);
    }
}

void ResultTreeCtrl::BuildTree() {
	root = new ResultItemsTree("Simulation results");
	wxTreeItemId rootId = this->AddRoot("Simulation results", -1, -1, root);

	// Cria os nós dos resultados das engines
	list<EngineResults> engineResults = resultsTree.GetEngineResults();
	list<EngineResults>::iterator engineIterator = engineResults.begin();
	list<EngineResults>::iterator itEnd = engineResults.end();
	while (engineIterator != itEnd) {
		wxString engineName = engineIterator->GetName();
		wxIcon engineIcon = engineIterator->GetIcon(availableElements);
		// Vincula à raiz
		int iconIndex = icons->Add(engineIcon);
		wxTreeItemId engineItemId = this->AppendItem(rootId, engineName, iconIndex, iconIndex, new ResultItemsTree(engineName));
		// Adiciona os próprios resultados da Engine, se houver
		std::list<ResultSmartPointer>::iterator myOwnResultsIt = engineIterator->GetMyResults().begin();
		std::list<ResultSmartPointer>::iterator myOwnResultsEnd = engineIterator->GetMyResults().end();
		cout << "Tamanho dos meus proprios resultados: " << engineIterator->GetMyResults().size() << endl;
		while (myOwnResultsIt != myOwnResultsEnd) {
			ResultSmartPointer result = *myOwnResultsIt;
			iconIndex = icons->Add(result->GetIcon());
			this->AppendItem(engineItemId, result->GetName(), iconIndex, iconIndex, new ResultItemsTree(result));
			myOwnResultsIt++;
		}
		// Pega a lista de elementos que foram simulados
		list<ElementResults>::iterator elementsResultsIterator = engineIterator->GetElementsResults().begin();
//		// Percorre a lista de elementos
		while (elementsResultsIterator != engineIterator->GetElementsResults().end()) {
			InsertElementsResultsNode(elementsResultsIterator, engineItemId);
			elementsResultsIterator++;
		}

		engineIterator++;
	}
	ExpandAll();
}
void ResultTreeCtrl::InsertElementsResultsNode(list<ElementResults>::iterator elementsResultsIterator, wxTreeItemId engineItemId_FatherNode) {
	// Cria o nó representando o elemento
	wxString elementName = elementsResultsIterator->GetName();
	wxIcon elementIcon = elementsResultsIterator->GetIcon(availableElements);

	int iconIndex = icons->Add(elementIcon);
	wxTreeItemId elementItemId = this->AppendItem(engineItemId_FatherNode, elementName, iconIndex, iconIndex, new ResultItemsTree(elementName));

	// Pega a lista de resultados
	list<ResultSmartPointer> results = elementsResultsIterator->GetResults();
	list<ResultSmartPointer>::iterator resultsIterator = results.begin();
	while (resultsIterator != results.end()) {
		ResultSmartPointer result = *resultsIterator;
		iconIndex = icons->Add(result->GetIcon());
		this->AppendItem(elementItemId, result->GetName(), iconIndex, iconIndex, new ResultItemsTree(result));

		resultsIterator++;
	}
}
ResultTreeCtrl::~ResultTreeCtrl() {
	if (popupMenu) {
		delete popupMenu;
	}
}

/////////////////////////////////
// ResultItemsTree
/////////////////////////////////
ResultItemsTree::ResultItemsTree(ResultSmartPointer result)
	: result(result) , leaf(true) {
}

ResultSmartPointer ResultItemsTree::GetResult() const {
    return result;
}

wxString ResultItemsTree::GetName() const {
    return name;
}

ResultItemsTree::ResultItemsTree(wxString name)
	: name(name), leaf(false) {
}

bool ResultItemsTree::IsLeaf() const {
	return leaf;
}

ResultItemsTree::~ResultItemsTree() {
}
