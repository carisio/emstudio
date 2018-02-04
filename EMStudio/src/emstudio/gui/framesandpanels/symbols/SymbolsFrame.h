/*
 * SymbolsFrame.h
 *
 *  Created on: 23/09/2013
 *      Author: leandrocarisio
 */

#ifndef SYMBOLSFRAME_H_
#define SYMBOLSFRAME_H_

#include "emstudio/util/muparser/BasicMathParser.h"
#include "emstudio/gui/elements/ElementManager.h"
#include <map>
#include "emstudio/util/dialogs/UtilDialog.h"
#include "wx/wx.h"
#include "wx/grid.h"

class SymbolsFrame : public wxDialog {
private:
	SymbolsMapSmartPointer symbolsMap;
	ElementManagerSmartPointer elementsInProject;
	wxGrid* grid;
	std::map<wxString, double> currentMap;

	wxString errorMessage;
	void CreateNewRow(wxGridEvent& event);
	void CreateAndInsertControls();
	void CreateAndConfigureGrid();
	void PopulateInitialGrid();

	bool CheckIfProjectIsOK();
	bool CheckSymbolsName();
	bool CheckSymbolsValue();
public:
	SymbolsFrame(wxWindow* parent, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer elementsInProject, wxWindowID id = wxID_ANY, const wxString& title = wxT("Symbols"));
	virtual ~SymbolsFrame();

	virtual bool TransferDataFromWindow();
};

#endif /* SYMBOLSFRAME_H_ */
