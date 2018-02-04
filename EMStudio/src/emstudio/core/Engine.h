/*
 * Engine.h
 *
 *  Created on: 11/10/2011
 *      Author: leandrocarisio
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "wx/wx.h"
#include "ElementCore.h"
#include "emstudio/dto/ElementDTO.h"
#include "emstudio/units/Units.h"
#include "emstudio/core/results/Result.h"
#include "InformSimulationStatus.h"

#include <list>
#include <tr1/memory>

class Engine;
class ElementCore;

typedef std::tr1::shared_ptr<ElementCore> ElementCoreSmartPointer;
typedef std::tr1::shared_ptr<Engine> EngineSmartPointer;

class Engine {
public:
	typedef pair<ElementDTOSmartPointer, ElementCoreSmartPointer> PairDTOCore;
	typedef list<PairDTOCore> ListPairDTOCore;
	typedef list<ElementDTOSmartPointer> EMStudioDTOList;
	typedef list<ElementCoreSmartPointer> ProjectList;
	InformSimulationStatusSmartPointer status;

public:
	Engine(ElementDTOSmartPointer dto, InformSimulationStatusSmartPointer status);
	virtual ~Engine();

	ProjectList& GetProjectList();

	UnitsSmartPointer GetUnits();

	void Register(ElementDTOSmartPointer elementDTO, ElementCoreSmartPointer elementCore);
	void Register(PairDTOCore pairDTOCore);

	ElementDTOSmartPointer GetEngineDTO();
	void CreateProject(EMStudioDTOList list);
	virtual void DoCreateProject();
	EngineResults StartSimulation(UnitsSmartPointer units);
	virtual bool UpdateProgress(int percentage);
	bool SimulationWasCanceled();
	bool InformStatus(wxString status);
	virtual std::list<ResultSmartPointer> GetMyOwnResults();
	virtual void DoStartSimulation() = 0;

	bool IsProjectConsistent();
	virtual bool DoIsProjectConsistentBegin();
	virtual bool DoIsProjectConsistentEnd();

	void SetErrorMessage(wxString msg);
	void AppendErrorMessage(wxString msg);
	wxString GetErrorMessage();

	InformSimulationStatusSmartPointer GetInformSimulationStatusSmartPointer();
private:
	ListPairDTOCore listDTOCore;
	ProjectList projectList;

	ElementCoreSmartPointer NewConfiguredElementCore(ElementDTOSmartPointer dto);
	UnitsSmartPointer units;
	ElementDTOSmartPointer dto;

	wxString errorMessage;
};

#endif /* ENGINE_H_ */
