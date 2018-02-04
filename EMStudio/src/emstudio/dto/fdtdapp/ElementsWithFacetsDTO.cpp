/*
 * EMStudioDTO.cpp
 *
 *  Created on: 17/10/2011
 *      Author: leandrocarisio
 */

#include "ElementsWithFacetsDTO.h"

ElementsWithFacetsDTO::ElementsWithFacetsDTO() {

}

ElementsWithFacetsDTO::~ElementsWithFacetsDTO() {

}

void ElementsWithFacetsDTO::Unnormalize(Units units) {
	if (HasFaces()) {
		double space = units.GetUserDefinedSpaceUnit().second;

		std::vector<Facet>::iterator it = facets.begin();
		std::vector<Facet>::iterator itEnd = facets.end();

		while (it != itEnd) {
			it->MultiplyVertex(space);

			it++;
		}
	}

	DoUnnormalize(units);
}
void ElementsWithFacetsDTO::DoUnnormalize(Units units) {

}

Priority ElementsWithFacetsDTO::GetPriority() {
	return priority;
}
void ElementsWithFacetsDTO::SetPriority(Priority priority) {
	this->priority = priority;
}

bool ElementsWithFacetsDTO::HasFaces() {
	return facets.size() > 0;
}
void ElementsWithFacetsDTO::SetFacets(std::vector<Facet> v) {
	facets = v;
}
std::vector<Facet> ElementsWithFacetsDTO::GetFacets() {
	return facets;
}
Material ElementsWithFacetsDTO::GetMaterial() {
    return material;
}
void ElementsWithFacetsDTO::SetMaterial(Material material) {
    this->material = material;
}
