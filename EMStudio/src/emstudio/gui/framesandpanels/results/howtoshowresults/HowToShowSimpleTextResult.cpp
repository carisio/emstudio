/*
 * HowToShowSimpleTextResult.cpp
 *
 *  Created on: 30/09/2015
 *      Author: Leandro
 */

#include <emstudio/gui/framesandpanels/results/howtoshowresults/HowToShowSimpleTextResult.h>

HowToShowSimpleTextResult::HowToShowSimpleTextResult() : HowToShowResults() {

}

HowToShowSimpleTextResult::~HowToShowSimpleTextResult() {
}

int HowToShowSimpleTextResult::GetNumberOfTabs() {
	return 1;
}
wxString HowToShowSimpleTextResult::GetTabName(int tabIndex) {
	ResultSmartPointer ptr = GetResult();
	SimpleTextResult* stResult = static_cast<SimpleTextResult*>(ptr.get());
	return stResult->GetName();
}
wxWindow* HowToShowSimpleTextResult::GetWindow(int tabIndex, wxWindow* parent) {
	ResultSmartPointer ptr = GetResult();
	SimpleTextResult* stResult = static_cast<SimpleTextResult*>(ptr.get());

//	wxStaticText* window = new wxStaticText(parent, wxID_ANY, stResult->GetContents());
	wxTextCtrl* window = new wxTextCtrl(parent, wxID_ANY, stResult->GetContents(), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
	return window;
}
