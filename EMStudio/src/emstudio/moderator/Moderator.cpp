/*
 * EMStudio.cpp
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */

//#define NDEBUG
//#include <assert.h>

#include "Moderator.h"
#include "wx/toolbar.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/util/time/TicTac.h"
#include "emstudio/util/md5/MD5.h"
#include <exception>
#include "wx/filename.h"
#include "emstudio/gui/framesandpanels/main/MainFrameFactory.h"
#include "emstudio/gui/framesandpanels/main/InformSimulationStatusAsProgressBar.h"

DECLARE_APP(Moderator)
IMPLEMENT_APP(Moderator)

Moderator::Moderator()
	: wxApp() {
//	O frame não pode ser criado aqui. Se for, o arquivo de recursos é lido, mas as imagens
//	não aparecem na barra de tarefas.
//	Além disso, nessa versão da wxWidgets é necessário ter um arquivo de recursos. Caso contrário, a barra de
//	tarefas fica transparente.
//	O frame tem que ser criado no OnInit.
//	frame = new MainFrame(wxT("EM Studio"), this);
}
Moderator::~Moderator() {

}

const wxCmdLineEntryDesc Moderator::cmdLineDesc[] =
{
    { wxCMD_LINE_PARAM,  NULL, NULL, "input file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_MULTIPLE },
    { wxCMD_LINE_NONE }
};
bool Moderator::OnInit() {
	// Altera o locale para colocar todos os campos numéricos com ponto como separador de casas decimais
	locale.Init(wxLANGUAGE_ENGLISH);

	frame = MainFrameFactory::NewMainFrame(this);
	frame->Initialize();
	frame->Maximize(true);
	frame->Show(true);

	// O ideial seria usar wxCmdLineParser, mas parece que nessa versão não está funcionando
	if (argc > 1) {
		wxString cmdFilename = argv[1];
		cout << "Antes: " << cmdFilename << endl;
		// Under Windows when invoking via a document
		// in Explorer, we are passed the short form.
		// So normalize and make the long form.
		wxFileName fName(cmdFilename);
		fName.Normalize(wxPATH_NORM_LONG|wxPATH_NORM_DOTS|
		wxPATH_NORM_TILDE|wxPATH_NORM_ABSOLUTE);
		cmdFilename = fName.GetFullPath();
		cout << "Depois: " << cmdFilename << endl;
		frame->Open(cmdFilename);
	}
	return true;
}

ResultTree Moderator::StartSimulation() {
	// Apaga os resultados atuais
	ResultTree resultTree;
	// Retorna a lista de métodos que devem ser simulados
	ElementTypeSmartPointer methodType = ElementTypeSmartPointer(new MethodType);
	ElementManager::ElementList methodsToSimulate = frame->GetElementsInProject()->GetElementList(methodType);
	ElementManager::ElementList::iterator it = methodsToSimulate.begin();
	ElementManager::ElementList::iterator end = methodsToSimulate.end();

	// elementDTOList contém os elementos de projeto (os métodos não estão na lista)
	EMStudioDTOList elementDTOList = GetUnnormalizedElementDTOList();

	resultTree.SetProjectCode(frame->GetProjectCode());
	while (it != end) {
		ElementDTOSmartPointer dto = (*it)->GetDTO();
		UnnormalizeDTO(dto);

		InformSimulationStatusSmartPointer informStatus = InformSimulationStatusSmartPointer(new InformSimulationStatusAsProgressBar);
		EngineSmartPointer engine = EngineFactory::NewEngine(dto, informStatus);
		engine->CreateProject(elementDTOList);

		// É necessário checar de novo pois algum material pode ter sido alterado após a definição do projeto.
		// Nesse caso, alguns elementos poderiam deixar de funcionar, como o MoM.
		// No geral, esses casos são irrelevantes
		wxString errorMessage;
		bool elementsInProjectAreStillValid = frame->GetElementsInProject()->CheckIfElementsAreOK(errorMessage);
		bool projectIsConsistent = engine->IsProjectConsistent();
		cout << "Passou por bool projectIsConsistent = engine->IsProjectConsistent();" << endl;
		if (elementsInProjectAreStillValid && projectIsConsistent) {
			EngineResults engineResult = engine->StartSimulation(frame->GetUnits());
			resultTree.GetEngineResults().push_back(engineResult);
		} else {
			if (!elementsInProjectAreStillValid) {
				wxString title = "Errors found in elements.";
				UtilDialog::ShowErrorMessage(errorMessage, title);
			}
			if (!projectIsConsistent) {
				wxString title = "Inconsistencies founded in ";
				title.Append(engine->GetEngineDTO()->GetName()).Append(".");
				UtilDialog::ShowErrorMessage(engine->GetErrorMessage(), title);
			}
		}
		it++;
		cout << "Iterou" << endl;
	}
	cout << "Saiu do loop" << endl;

//	.....TEMP.....
//	ElementDTOSmartPointer dto = (*it)->GetDTO();
//	UnnormalizeDTO(dto);
//
//	cout << "Criou uma Engine para " << dto->GetName() << endl;
//	EngineSmartPointer engine = EngineFactory::NewEngine(dto);
//	engine->CreateProject(elementDTOList);
//	if (engine->IsProjectConsistent()) {
//		EngineResults engineResult = engine->StartSimulation(frame->GetUnits());
//		resultTree.GetEngineResults().push_back(engineResult);
//	} else {
//		wxString title = "Inconsistencies founded in ";
//		title.Append(engine->GetEngineDTO()->GetName()).Append(".");
//		UtilDialog::ShowErrorMessage(engine->GetErrorMessage(), title);
//	}
	/* TEMP */
	cout << "Pegando engineResults" << endl;
	list<EngineResults> er = resultTree.GetEngineResults();
	cout << "OK" << endl;
	list<EngineResults>::iterator itBegin = er.begin();
	list<EngineResults>::iterator itEnd = er.end();
	cout << "iterando EngineResults" << endl;
	while (itBegin!=itEnd) {
		cout << "\tNome da engine: " << itBegin->GetName() << endl;
		list<ResultSmartPointer> myOwnResults = itBegin->GetMyResults();
		cout << "\titerando MyOwnResults" << endl;
		list<ResultSmartPointer>::iterator myOwnResultsBegin = myOwnResults.begin();
		list<ResultSmartPointer>::iterator myOwnResultsEnd = myOwnResults.end();
		while (myOwnResultsBegin!=myOwnResultsEnd) {
			cout << "\t\tNome do resultado: " << (*myOwnResultsBegin)->GetName() << endl;
			myOwnResultsBegin++;
		}
		list<ElementResults> elementsResults = itBegin->GetElementsResults();
		list<ElementResults>::iterator eitBegin = elementsResults.begin();
		list<ElementResults>::iterator eitEnd = elementsResults.end();
		cout << "\titerando ElementResults" << endl;
		while (eitBegin!=eitEnd) {
			cout << "\t\tNome do elemento: " << eitBegin->GetName() << endl;
			list<ResultSmartPointer> listaResultados = eitBegin->GetResults();
			list<ResultSmartPointer>::iterator rbegin = listaResultados.begin();
			list<ResultSmartPointer>::iterator rend = listaResultados.end();
			while (rbegin != rend) {
				cout << "\t\t\tNome do resultado: " << (*rbegin)->GetName() << endl;
				rbegin++;
			}
			eitBegin++;
		}
		itBegin++;
	}
	cout << "OK, iterou tudo" << endl;
	return resultTree;
}
void Moderator::UnnormalizeDTO(ElementDTOSmartPointer dto) {
	dto->Unnormalize(*frame->GetUnits());
}
/*
 * Retorna os elementos em seus valores reais (unidades MKS).
 * Desconsidera os métodos.
 */
Moderator::EMStudioDTOList Moderator::GetUnnormalizedElementDTOList() {
	MethodType methodType;

	EMStudioDTOList result;
	ElementManager::ElementMap projectMap = frame->GetElementsInProject()->GetElementMap();

	ElementManager::ElementMap::iterator it = projectMap.begin();
	ElementManager::ElementMap::iterator end = projectMap.end();

	while(it != end) {
		ElementTypeSmartPointer type = it->first;

		if (type->GetName() != 	methodType.GetName()) {
			ElementManager::ElementList eList = it->second;

			ElementManager::ElementList::iterator itList = eList.begin();
			ElementManager::ElementList::iterator itListEnd = eList.end();

			while (itList != itListEnd) {
				ElementGUISmartPointer element = *itList;
				ElementDTOSmartPointer dto = element->GetDTO();
				ElementsWithFacetsDTOSmartPointer emStudioDTO = std::tr1::static_pointer_cast<ElementsWithFacetsDTO>(dto);
				UnnormalizeDTO(emStudioDTO);
				result.push_back(emStudioDTO);
				itList++;
			}
		}
		it++;
	}
	return result;
}
