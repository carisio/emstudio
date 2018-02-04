/*
 * MaterialLibraryFrame.h
 *
 *  Created on: 28/09/2011
 *      Author: leandrocarisio
 */

#ifndef MATERIALLIBRARYFRAME_H_
#define MATERIALLIBRARYFRAME_H_

#include <list>
#include "emstudio/util/dialogs/UtilDialog.h"
#include "wx/wx.h"
#include "wx/listbox.h"
#include "wx/arrstr.h"
#include "emstudio/gui/basetypes/Material.h"
#include "emstudio/gui/basetypes/MaterialLibrary.h"
#include "emstudio/gui/framesandpanels/materials/NewMaterialFrame.h"
#include "emstudio/util/file/FileManager.h"

class MaterialLibraryFrame : public wxDialog {
private:
	wxListBox* materialList;
	MaterialLibrarySmartPointer library;

	void CreateAndInsertControls();
public:
	MaterialLibraryFrame(wxWindow* parent, MaterialLibrarySmartPointer ml, wxWindowID id = wxID_ANY, const wxString& title = wxT("Material Library"));
	void RebuildListBox();

	void NewMaterial(wxCommandEvent& event);
	void EditMaterial(wxCommandEvent& event);
	void DeleteMaterial(wxCommandEvent& event);
	void ExportMaterial(wxCommandEvent& event);
	void ImportMaterial(wxCommandEvent& event);

	virtual ~MaterialLibraryFrame();

};

#endif /* MATERIALLIBRARYFRAME_H_ */
