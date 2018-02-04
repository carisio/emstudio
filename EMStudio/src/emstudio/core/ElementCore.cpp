/*
 * ElementCore.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "ElementCore.h"
//#include <iostream>
//using namespace::std;

ElementCore::ElementCore() {

}

ElementCore::~ElementCore() {

}

/* Não é necessário fazer (delete engine) nesse código,
 * pois o que está acontecendo é que cada ElementCore manterá um ponteiro
 * para a Engine. A Engine tem que existir independente do ElementCore. Quem
 * apagará a Engine será o SmartPointer que a contém.
 */
void ElementCore::SetEngine(Engine* e) {
	engine = e;
}

ElementDTOSmartPointer ElementCore::GetDTO() {
	return dto;
}
void ElementCore::SetDTO(ElementDTOSmartPointer dto) {
	this->dto = dto;
}
Engine* ElementCore::GetEngine() {
	return engine;
}

void ElementCore::Configure(ElementDTOSmartPointer dto) {
	SetName(dto->GetName());
	DoConfigure(dto);
}
//int ElementCore::GetPriority() const {
//	return priority;
//}
//void ElementCore::SetPriority(int p) {
//	priority = p;
//}
wxString ElementCore::GetName() const {
	return name;
}
void ElementCore::SetName(wxString name) {
	this->name = name;
}
bool ElementCore::IsElementConsistent() {
	return true;
}
void ElementCore::AppendErrorMessage(wxString msg) {
	engine->AppendErrorMessage(msg);
}

// TODO: ASSIM QUE TUDO ESTIVER IMPLEMENTADO, DEFINIR ESSE MÉTODO COMO VIRTUAL:
bool ElementCore::HasResults() {
//	cout << "ElementCore::HasResults() - " << dto->GetName() << endl;
	return false;
}
ElementResults ElementCore::GetElementsResults() {
	return ElementResults("TODO: ASSIM QUE TUDO ESTIVER IMPLEMENTADO, DEFINIR ESSE MÉTODO COMO VIRTUAL", "TODO: ASSIM QUE TUDO ESTIVER IMPLEMENTADO, DEFINIR ESSE MÉTODO COMO VIRTUAL");
}
