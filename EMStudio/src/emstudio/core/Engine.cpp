/*
 * Engine.cpp
 *
 *  Created on: 11/10/2011
 *      Author: leandrocarisio
 */

#include "Engine.h"

Engine::Engine(ElementDTOSmartPointer dto, InformSimulationStatusSmartPointer status)
	: listDTOCore(), projectList(), dto(dto), status(status) {

}

void Engine::Register(ElementDTOSmartPointer elementDTO, ElementCoreSmartPointer elementCore) {
	Register(PairDTOCore(elementDTO, elementCore));
}

void Engine::Register(Engine::PairDTOCore pairDTOCore) {
	listDTOCore.push_back(pairDTOCore);
}

ElementDTOSmartPointer Engine::GetEngineDTO(){
	return dto;
}
/*
 * Cria a lista de projeto com os elementos de núcleo
 */
void Engine::CreateProject(EMStudioDTOList dtoProjectList) {
	EMStudioDTOList::iterator it = dtoProjectList.begin();
	EMStudioDTOList::iterator end = dtoProjectList.end();

	while (it != end) {
		ElementCoreSmartPointer core = NewConfiguredElementCore(*it);
		if (core) {
			projectList.push_back(core);
		}
		it++;
	}
	DoCreateProject();
}
void Engine::DoCreateProject() {

}
Engine::ProjectList& Engine::GetProjectList() {
	return projectList;
}

UnitsSmartPointer Engine::GetUnits() {
	return units;
}

ElementCoreSmartPointer Engine::NewConfiguredElementCore(ElementDTOSmartPointer dto) {
	ListPairDTOCore::iterator it = listDTOCore.begin();
	ListPairDTOCore::iterator end = listDTOCore.end();

	while (it != end) {
		if (dto->GetDTOClassName() ==  it->first->GetDTOClassName()) {
    		ElementCoreSmartPointer core = it->second->NewElementCore();
			core->SetEngine(this);
			core->SetDTO(dto);
    		core->Configure(dto);
//			core->SetPriority(dto->GetPriority().GetValue());

			return core;
		}
		it++;
	}
	cout << "Elemento " << dto->GetDTOClassName() << " não cadastrado. Ver o que fazer se chegar aqui. Talvez emitir um warning. " << endl;
	return ElementCoreSmartPointer();
}

EngineResults Engine::StartSimulation(UnitsSmartPointer units) {
	status->StartSimulation(dto->GetName().ToStdString());
	this->units = units;
	DoStartSimulation();

	list<ElementResults> results;

	ProjectList::iterator it = projectList.begin();
	ProjectList::iterator end = projectList.end();

	while (!(SimulationWasCanceled()) && it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		if (elementCore->HasResults()) {
			results.push_back(elementCore->GetElementsResults());
		}

		it++;
	}
	std::list<ResultSmartPointer> myOwnResults = GetMyOwnResults();
	cout << "Em Engine, qtos resultados eu msm tenho: " << myOwnResults.size() << endl;
	UpdateProgress(100);
	return EngineResults(dto->GetDTOClassName(), dto->GetName(), results, myOwnResults);
}
std::list<ResultSmartPointer> Engine::GetMyOwnResults() {
	return std::list<ResultSmartPointer>();
}
bool Engine::UpdateProgress(int percentage) {
	status->Update(percentage);
}
bool Engine::SimulationWasCanceled() {
	return status->SimulationWasCanceled();
}
bool Engine::InformStatus(wxString status) {
	wxString newMessage = "Simulating " + dto->GetName();
	if (status != "") {
		newMessage += "\n";
		newMessage += wxT("(") + status + wxT(").");
	} else {
		newMessage += ".";
	}
	return this->status->InformStatus(newMessage.ToStdString());
}
bool Engine::IsProjectConsistent() {
	ProjectList::iterator itElementsInProject = projectList.begin();
	ProjectList::iterator itElementsInProjectEnd = projectList.end();

	/*
	 * Pré-processamento da verificação:
	 * Primeiro verifica o método DoIsProjectConsistentBegin()
	 */
	bool projectConsistent = true;
	projectConsistent = projectConsistent && DoIsProjectConsistentBegin();
//	cout << "Engine passou pela pre verificacao do projeto" << endl;
	/*
	 * Processamento da verificação:
	 * A verificação dos elementos é feita apenas se DoIsProjectConsistentBegin() == true.
	 */
	while (projectConsistent && (itElementsInProject != itElementsInProjectEnd)) {
		projectConsistent = projectConsistent && (*itElementsInProject)->IsElementConsistent();
		itElementsInProject++;
	}
//	cout << "Engine passou pela verificacao dos elementos" << endl;
	/*
	 * Pós processamento da verificação:
	 */
	if (projectConsistent) {
		projectConsistent = projectConsistent && DoIsProjectConsistentEnd();
	}
//	cout << "Engine passou pela pós verificacao do projeto" << endl;
	return projectConsistent;
}
bool Engine::DoIsProjectConsistentBegin() {
	return true;
}
bool Engine::DoIsProjectConsistentEnd() {
	return true;
}
void Engine::SetErrorMessage(wxString msg) {
	errorMessage = msg;
}
void Engine::AppendErrorMessage(wxString msg) {
	errorMessage.Append(msg).Append("\n");
}
wxString Engine::GetErrorMessage() {
	return errorMessage;
}

Engine::~Engine() {
	listDTOCore.clear();
	projectList.clear();
}

InformSimulationStatusSmartPointer Engine::GetInformSimulationStatusSmartPointer() {
	return status;
}
