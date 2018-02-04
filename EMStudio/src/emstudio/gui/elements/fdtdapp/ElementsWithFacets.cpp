/*
 * EMStudioGUI.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "ElementsWithFacets.h"
#include "emstudio/dto/ElementDTO.h"
#include "emstudio/dto/fdtdapp/ElementsWithFacetsDTO.h"
#include <tr1/memory>

ElementsWithFacets::ElementsWithFacets(ElementTypeSmartPointer type)
	: ElementGUI(type) {

}

ElementsWithFacets::~ElementsWithFacets() {

}

void ElementsWithFacets::SetPriority(PriorityType number) {
	priority.SetValue(number);
}

void ElementsWithFacets::AddPriorityProperty(wxString propertyName, PriorityType number) {
	SetPriority(number);
	AddProperty(Property(propertyName, &priority));
}
void ElementsWithFacets::AddPriorityProperty(PriorityType number) {
	SetPriority(number);
	AddProperty(Property("Priority", &priority));
}
void ElementsWithFacets::AddMaterialProperty(wxString propertyName, wxString defaultMaterial) {
	// Altera o nome do material
	material.SetDescription(defaultMaterial);
	// Verifica se o nome é PEC. Se for, atualiza o tipo e coloca ele na biblioteca
	if (defaultMaterial == "PEC") {
		material.SetType(PEC);
		material.SetColor(wxColour(0,0,255));
	}
	// É necessário sincronizar o material com os dados da biblioteca. É possível que tenha sido alterado.
	material.Sync(false);
	AddProperty(Property(propertyName, &material));
}
wxColour ElementsWithFacets::GetMaterialColor() {
	// Atualiza o material com os dados da bilioteca. É possível que o usuário tenha alterado a cor do material.
	material.Sync(false);

	return material.GetColor();
}
wxColour ElementsWithFacets::GetPECColor() {
	Material pec;
	pec.SetDescription("PEC");
	pec.SetType(PEC);
	pec.Sync(false);

	return pec.GetColor();
}
void ElementsWithFacets::DoPopulateDTO(ElementDTOSmartPointer p) {
	ElementGUI::DoPopulateDTO(p);

	ElementsWithFacetsDTOSmartPointer emStudioDTO = std::tr1::static_pointer_cast<ElementsWithFacetsDTO>(p);
	emStudioDTO->SetPriority(priority);

	if (HasFacets()) {
		emStudioDTO->SetFacets(GetFacets());
	}
	/* Preenche o material para todos os elementos. Caso o elemento não esteja associado a um material, a propriedade será preenchida com ar.
	 * Caso o material tenha sido atualizado na biblioteca, é necessário sincronizar, para pegar a informação mais recente.
	 */
	material.Sync(false);
	emStudioDTO->SetMaterial(material);
}

bool ElementsWithFacets::HasFacets() {
	return GetFacets().size() > 0;
}
std::vector<Facet> ElementsWithFacets::BuildFacets() {
	std::vector<Facet> v;
	return v;
}
std::vector<Facet>& ElementsWithFacets::GetFacets() {
	if (IsChanged()) {
		std::vector<Facet> v = BuildFacets();
		SetFacets(v);
		SetChanged(false);
	}
	return facets;
}
void ElementsWithFacets::SetFacets(std::vector<Facet>& v) {
	facets = v;
}

void ElementsWithFacets::FillApproximateDimensionsWithFacets(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	Rvector3 max;
	Rvector3 min;

	std::vector<Facet> v = GetFacets();
	FillBoundaries(v, min, max);
	xmin = min.X; ymin = min.Y; zmin = min.Z;
	xmax = max.X; ymax = max.Y; zmax = max.Z;
}
