/*
 * ElementGUI.cpp
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#include "ElementGUI.h"
#include "Property.h"

// Inicializa o pointeiro para a biblioteca de materiais.
// Cria um temporário qualquer, apenas para começar.
ElementManagerSmartPointer ElementGUI::elementsInProjectSmartPointer = ElementManagerSmartPointer();

ElementGUI::ElementGUI(ElementTypeSmartPointer eType)
	: Propertyable(), type(eType), name() {

	AddProperty(Property("Name", &name));
}
void ElementGUI::SetElementsInProject(ElementManagerSmartPointer em) {
	ElementGUI::elementsInProjectSmartPointer = em;
}
ElementManagerSmartPointer ElementGUI::GetElementsInProject() {
	return elementsInProjectSmartPointer;
}
void ElementGUI::ProjectChanged() {

}
wxString ElementGUI::GetUserDefinedName() {
	if (name.GetValue() == "") {
		name.SetValue(GetRegisteredName());
	}
	return name.GetValue();
}

ElementTypeSmartPointer ElementGUI::GetType() {
	return type;
}

ElementGUI::~ElementGUI() {

}

PropertyableSmartPointer ElementGUI::NewPropertyable() {
	return std::tr1::static_pointer_cast<Propertyable>(NewElementGUI());
}

void ElementGUI::Draw(OpenGLStateMachine* opengl) {
}

/*
 * Retorna true se esse ElementGUI possui informações aproximadas sobre suas dimensões (para desenhar na tela).
 * Se possuir, preenche as coordenadas de sua dimensão.
 */
bool ElementGUI::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	return false;
}
void ElementGUI::Move(Point3DME p) {
	DoMove(p);
	SetChanged(true);
	ElementGUI::GetElementsInProject()->InformProjectChanged();
}
ElementDTOSmartPointer ElementGUI::GetDTO() {
	ElementDTOSmartPointer result = NewElementDTO();
	DoPopulateDTO(result);
	return result;
}

void ElementGUI::DoPopulateDTO(ElementDTOSmartPointer p) {
	p->SetName(GetUserDefinedName());
}
