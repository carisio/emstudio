/*
 * EMStudioGUI.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef EMSTUDIOGUI_H_
#define EMSTUDIOGUI_H_

#include "../ElementGUI.h"
#include "../ElementType.h"
#include "emstudio/gui/basetypes/Priority.h"
#include "emstudio/gui/basetypes/Material.h"

#include "emstudio/util/facet/Facet.h"
#include "wx/wx.h"
#include <vector>

class ElementsWithFacets : public ElementGUI {
private:
	Priority priority;
	Material material;
	std::vector<Facet> facets;
public:
	ElementsWithFacets(ElementTypeSmartPointer type);

	void SetPriority(PriorityType number);
	virtual void DoPopulateDTO(ElementDTOSmartPointer p);
	void AddMaterialProperty(wxString propertyName, wxString defaultMaterial = "Air");
	void AddPriorityProperty(wxString propertyName = "Priority", PriorityType number = MINIMUM);
	void AddPriorityProperty(PriorityType number = MINIMUM);
	wxColour GetMaterialColor();
	wxColour GetPECColor();

	bool HasFacets();
	virtual std::vector<Facet> BuildFacets();
	std::vector<Facet>& GetFacets();
	void SetFacets(std::vector<Facet>& v);
	void FillApproximateDimensionsWithFacets(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual ~ElementsWithFacets();
};

#endif /* EMSTUDIOGUI_H_ */
