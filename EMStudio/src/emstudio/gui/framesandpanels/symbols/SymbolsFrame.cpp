/*
 * SymbolsFrame.cpp
 *
 *  Created on: 23/09/2013
 *      Author: leandrocarisio
 */

#include "SymbolsFrame.h"
#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */

SymbolsFrame::SymbolsFrame(wxWindow* parent, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer elementsInProject, wxWindowID id, const wxString& title)
	: wxDialog(parent, id, title, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX), symbolsMap(symbolsMap), elementsInProject(elementsInProject) {

	/* Save current symbol table */
	currentMap = symbolsMap->GetMap();

	CreateAndInsertControls();
}

SymbolsFrame::~SymbolsFrame() {
}

void SymbolsFrame::CreateAndConfigureGrid() {
	int minRows = 20;

	grid->CreateGrid(minRows, 2);
	grid->HideRowLabels();

	grid->SetColLabelValue(0, "Symbol");
	grid->SetColLabelValue(1, "Value");

	Connect(grid->GetId(), wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(SymbolsFrame::CreateNewRow));
	Connect(grid->GetId(), wxEVT_GRID_SELECT_CELL, wxGridEventHandler(SymbolsFrame::CreateNewRow));
}
void SymbolsFrame::CreateNewRow(wxGridEvent& event) {
    int row = event.GetRow();
    int lastRow = grid->GetNumberRows() - 1;
    if(row == lastRow) {
    	grid->AppendRows(1);
		grid->SetCellEditor(row+1, 0, new wxGridCellTextEditor);
		grid->SetCellEditor(row+1, 1, new wxGridCellFloatEditor);
    }

  event.Skip();
}
void SymbolsFrame::PopulateInitialGrid() {
	/* Quantidade inicial de símbolos */
	int nSymbols = symbolsMap->GetSymbolsName().size();
	/* Quantidade de linhas na tabela */
	int nRows = grid->GetTable()->GetRowsCount();
	cout << "0"<< endl;
	/* Se a quantidade de símbolos for maior que a de linhas, é necessário adicionar mais linhas ao grid */
	if (nSymbols > nRows) {
		grid->AppendRows(nSymbols-nRows+1);
	}
	/* Configura o editor do grid */
	nRows = grid->GetTable()->GetRowsCount();
	for (int i = 0; i < nRows; i++) {
		grid->SetCellEditor(i, 0, new wxGridCellTextEditor);
		grid->SetCellEditor(i, 1, new wxGridCellTextEditor);
	}

	/* Adiciona a lista de símbolos ao grid*/
	std::list<wxString> symbolsName = symbolsMap->GetSymbolsName();
	std::list<wxString>::iterator it = symbolsName.begin();
	std::list<wxString>::iterator end = symbolsName.end();

	int rowNumber = 0;
	while (it != end) {
		wxString symbolName = *it;
		if (symbolName != "t" && symbolName != "T") {
			grid->SetCellValue(rowNumber, 0, *it);
			grid->SetCellValue(rowNumber, 1, Converter::DoubleToFormattedString_MaxPrecision(symbolsMap->GetSymbol(*it)));

			rowNumber++;
		}
		it++;
	}
}
void SymbolsFrame::CreateAndInsertControls() {
	/* Sizer */
	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);

	/* Cria grid */
	grid = new wxGrid(this, wxID_ANY);
	CreateAndConfigureGrid();

	/* Coloca o grid em cima */
	topSizer->Add(grid, 1, wxALL | wxALIGN_CENTER, 10);

	/* Cria a parte de botões */
	wxBoxSizer *buttonSizer = new wxBoxSizer( wxHORIZONTAL );
	buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL | wxALIGN_CENTER, 5);
	buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL | wxALIGN_CENTER, 5);

	/* Adiciona os botões ao sizer */
	topSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

	/* Estabelece que o sizer é a tela */
	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);

	PopulateInitialGrid();
}
/* Chamado quando o usuário clica no botão OK */
bool SymbolsFrame::TransferDataFromWindow() {
	/* Verifica se o nome dos símbolos estão ok */
	bool ok = CheckSymbolsName();
	if (!ok) {
		UtilDialog::ShowErrorMessage(errorMessage, "Validation error");
		return false;
	}
	ok = CheckSymbolsValue();
	if (!ok) {
		UtilDialog::ShowErrorMessage(errorMessage, "Validation error");
		return false;
	}

	if (!ok) {
		UtilDialog::ShowErrorMessage(errorMessage, "Validation error");
		return false;
	}

	/* Transfere todos os símbolos para o mapa. Considera que os valores já foram validados */
	BasicMathParser p;
	symbolsMap->ClearMap();
	for (int i = 0; i < grid->GetNumberRows(); i++) {
		wxString symbolName = grid->GetCellValue(i,0);
		symbolName = symbolName.Trim();
		if (symbolName != "") {
			p.SetExpression(grid->GetCellValue(i,1));
			p.IsValid();
			symbolsMap->AddSymbol(symbolName, p.Eval());
		}
	}

	/* Verifica se o novo mapa de símbolos está consistente com o projeto */
	ok = CheckIfProjectIsOK();
	if (ok) {
		// OK, o mapa de símbolos já está atualizado
		return true;
	} else {
		// Desfaz a alteração no mapa de símboos
		symbolsMap->ClearMap();
		symbolsMap->AddSymbols(currentMap);

		UtilDialog::ShowErrorMessage(errorMessage, "Validation error");
		return false;
	}
}
bool SymbolsFrame::CheckSymbolsName() {
	errorMessage = "";
	bool ok = true;
	bool symbolNameT = false;

	for (int i = 0; i < grid->GetNumberRows(); i++) {
		wxString symbolName = grid->GetCellValue(i,0);
		symbolName = symbolName.Trim();
		if (symbolName == "t" || symbolName == "T") {
			symbolNameT = true;
			break;
		}
		if (symbolName != "") {

			size_t l = 0;
			if (!((symbolName.at(l) >= 'a' && symbolName.at(l) <= 'z') ||
					(symbolName.at(l) >= 'A' && symbolName.at(l) <= 'Z'))) {
				errorMessage += symbolName + "\n";
				ok = false;
				break;
			}
			for (size_t l = 1; l < symbolName.Len(); l++) {
				if (!((symbolName.at(l) >= 'a' && symbolName.at(l) <= 'z') ||
						(symbolName.at(l) >= 'A' && symbolName.at(l) <= 'Z') ||
						(symbolName.at(l) >= '0' && symbolName.at(l) <= '9'))) {
					errorMessage += symbolName + "\n";
					ok = false;
					break;
				}
			}
		}
	}

	if (symbolNameT) {
		errorMessage = "Don't use t and T. They are bad symbols names.\n" + errorMessage;
	}
	if (!ok) {
		errorMessage = "The name of the symbol must begin with a letter and can be followed by letters and numbers. The following symbols have not a valid name:\n\n" + errorMessage;
	}

	return ok && !symbolNameT;
}
bool SymbolsFrame::CheckSymbolsValue() {
	errorMessage = "";
	bool ok = true;

	BasicMathParser p;
	for (int i = 0; i < grid->GetNumberRows(); i++) {
		wxString symbolName = grid->GetCellValue(i,0);
		symbolName = symbolName.Trim();
		if (symbolName != "") {
			p.SetExpression(grid->GetCellValue(i,1));
			if (!p.IsValid()) {
				errorMessage += "\"" + grid->GetCellValue(i,1) + "\" is an invalid expression\n";
				ok = false;
			}
		}
	}
	return ok;
}
bool SymbolsFrame::CheckIfProjectIsOK() {
	errorMessage = "";
	bool ok = elementsInProject->CheckIfElementsAreOK(errorMessage);
	return ok;
}
