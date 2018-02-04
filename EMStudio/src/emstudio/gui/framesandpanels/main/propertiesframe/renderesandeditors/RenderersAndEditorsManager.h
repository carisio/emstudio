/*
 * RenderersAndEditorsManager.h
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#ifndef RENDERERSANDEDITORSMANAGER_H_
#define RENDERERSANDEDITORSMANAGER_H_

#include <map>
#include <wx/wx.h>
#include <wx/grid.h>
#include <tr1/memory>

class RenderersAndEditorsManager;

typedef std::tr1::shared_ptr<RenderersAndEditorsManager> RenderersAndEditorsManagerSmartPointer;
typedef std::tr1::shared_ptr<wxGridCellEditor> wxGridCellEditorSmartPointer;
typedef std::tr1::shared_ptr<wxGridCellRenderer> wxGridCellRendererSmartPointer;

using namespace::std;

class RenderersAndEditorsManager {
public:
	typedef map<wxString, wxGridCellEditorSmartPointer> EditorMap;
	typedef map<wxString, wxGridCellRendererSmartPointer> RendererMap;
private:
	EditorMap editorMap;
	RendererMap rendererMap;
public:
	RenderersAndEditorsManager();
	virtual ~RenderersAndEditorsManager();
	void Register(wxString baseTypeName, wxGridCellEditorSmartPointer editor, wxGridCellRendererSmartPointer renderer);
	EditorMap& GetEditorMap();
	RendererMap& GetRendererMap();
};

#endif /* RENDERERSANDEDITORSMANAGER_H_ */
