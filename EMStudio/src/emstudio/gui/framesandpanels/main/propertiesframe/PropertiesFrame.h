/*
 * PropertiesFrame.h
 *
 *  Created on: 21/09/2011
 *      Author: leandrocarisio
 */

#ifndef PROPERTIESFRAME_H_
#define PROPERTIESFRAME_H_

#include "wx/grid.h"
#include "wx/wx.h"
#include "emstudio/gui/elements/Propertyable.h"
#include "renderesandeditors/RenderersAndEditorsManager.h"
#include "PropertiesGridTable.h"

class PropertiesFrame : public wxDialog {
private:
	wxGrid* grid;
	PropertyableSmartPointer originalObject;
	PropertyableSmartPointer copiedObject;

	bool TestPropertiesValidator();
	bool TestAllPropertiesTogether();
public:
	PropertiesFrame(wxWindow* parent, PropertyableSmartPointer obj, RenderersAndEditorsManagerSmartPointer rendererAndEditors, wxWindowID id = wxID_ANY, const wxString& title = wxT("Properties"));
	virtual ~PropertiesFrame();

	void ConfigureGridLayout();
	void SetObject(PropertyableSmartPointer obj);
	void RegisterRenderersAndEditors(RenderersAndEditorsManagerSmartPointer rendererAndEditors);
	virtual bool TransferDataFromWindow();
};

#endif /* PROPERTIESFRAME_H_ */
