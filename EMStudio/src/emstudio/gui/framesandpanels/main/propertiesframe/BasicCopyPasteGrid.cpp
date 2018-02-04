/*
 * BasicCopyPasteGrid.cpp
 *
 *  Created on: 10/02/2012
 *      Author: leandrocarisio
 */

#include "BasicCopyPasteGrid.h"

BEGIN_EVENT_TABLE(BasicCopyPasteGrid,wxGrid)
   EVT_MENU(wxID_COPY,BasicCopyPasteGrid::Copy)
   EVT_MENU(wxID_PASTE,BasicCopyPasteGrid::Paste)
   EVT_GRID_CELL_RIGHT_CLICK(BasicCopyPasteGrid::OnRightMouseDown)
   EVT_KEY_DOWN(BasicCopyPasteGrid::OnKeyDown)
END_EVENT_TABLE()

BasicCopyPasteGrid::BasicCopyPasteGrid(wxWindow *parent, wxWindowID id, bool pasteAvailable, const wxPoint& pos, const wxSize& size)
	: wxGrid(parent,id,pos,size),
	  showPasteInPopup(pasteAvailable) {

}

BasicCopyPasteGrid::~BasicCopyPasteGrid() {
}

void BasicCopyPasteGrid::Copy() {
	wxString copy_data;
	    bool something_in_this_line;

	    copy_data.Clear();

	    for (int i=0; i<GetRows();i++) {
	        something_in_this_line = false;
	        for (int j=0; j<GetCols(); j++) {
	            if (IsInSelection(i,j)) {
	                if (something_in_this_line == false) {
	                    if (copy_data.IsEmpty() == false) {
	                        copy_data.Append(wxT("\n"));
	                    }
	                    something_in_this_line = true;
	                }
	                else {
	                    copy_data.Append(wxT("\t"));
	                }
	                copy_data = copy_data + GetCellValue(i,j);
	            }
	        }
	    }

	    if (wxTheClipboard->Open()) {
	    	wxTheClipboard->SetData(new wxTextDataObject(copy_data));
	    	wxTheClipboard->Close();
	    }
}
void BasicCopyPasteGrid::Paste() {
	if (!showPasteInPopup)
			return;

	    wxString copy_data;
	    wxString cur_field;
	    wxString cur_line;

	    if (wxTheClipboard->Open()) {
	    	if (wxTheClipboard->IsSupported( wxDF_TEXT )) {
				wxTextDataObject data;
				wxTheClipboard->GetData(data);
				copy_data = data.GetText();
			}
	    	wxTheClipboard->Close();
	    }

	    int i = GetGridCursorRow();
	    int j = GetGridCursorCol();
	    int k = j;

	    while(!copy_data.IsEmpty()) {
	        cur_line = copy_data.BeforeFirst('\n');
	        while(!cur_line.IsEmpty()) {
	            cur_field = cur_line.BeforeFirst('\t');
	            SetCellValue(i,j,cur_field);
	            j++;
	            cur_line  = cur_line.AfterFirst ('\t');
	        }
	        i++;
	        j=k;
	        copy_data = copy_data.AfterFirst('\n');
	    }
}

void BasicCopyPasteGrid::Copy(wxCommandEvent &event) {
    Copy();
}
void BasicCopyPasteGrid::Paste(wxCommandEvent &event) {
	Paste();
}
void BasicCopyPasteGrid::OnRightMouseDown(wxGridEvent &event) {
    wxMenu *pmenuPopUp = new wxMenu;
    wxMenuItem* pItem;
    pItem = new wxMenuItem(pmenuPopUp, wxID_COPY, wxT("Copy"));
    pmenuPopUp->Append(pItem);

    if (showPasteInPopup) {
		pItem = new wxMenuItem(pmenuPopUp, wxID_PASTE, wxT("Paste"));
		pmenuPopUp->Append(pItem);
		if(!CanEnableCellControl())
			pItem->Enable(false);
    }

    PopupMenu(pmenuPopUp, event.GetPosition());
    delete pmenuPopUp;
}
void BasicCopyPasteGrid::OnKeyDown(wxKeyEvent& event) {
	if ((event.GetUnicodeKey() == 'C' || event.GetUnicodeKey() == 'c') && (event.ControlDown() == true)) {
		Copy();
	} else if ((event.GetUnicodeKey() == 'V' || event.GetUnicodeKey() == 'v') && (event.ControlDown() == true)) {
		Paste();
	}
}
