/*
 * EMStudioDTO.h
 *
 *  Created on: 17/10/2011
 *      Author: leandrocarisio
 */

#ifndef EMSTUDIODTO_H_
#define EMSTUDIODTO_H_

#include "../ElementDTO.h"
#include "emstudio/gui/basetypes/Priority.h"
#include "emstudio/gui/basetypes/Material.h"
#include "emstudio/util/facet/Facet.h"

#include "wx/wx.h"

#include <vector>

class ElementsWithFacetsDTO;

typedef std::tr1::shared_ptr<ElementsWithFacetsDTO> ElementsWithFacetsDTOSmartPointer;

class ElementsWithFacetsDTO : public ElementDTO {
private:
	Priority priority;

	/* Variáveis usadas para representar um objeto que tem material */
	std::vector<Facet> facets;
	Material material;

public:
	ElementsWithFacetsDTO();

	virtual void Unnormalize(Units units);
	virtual void DoUnnormalize(Units units);

    virtual Priority GetPriority();
    void SetPriority(Priority priority);

    bool HasFaces();
    void SetFacets(std::vector<Facet> v);
    std::vector<Facet> GetFacets();
    Material GetMaterial();
    void SetMaterial(Material material);

    virtual ~ElementsWithFacetsDTO();
};

#endif /* EMSTUDIODTO_H_ */
