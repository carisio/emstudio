/*
 * ElementCore.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef ELEMENTCORE_H_
#define ELEMENTCORE_H_

#include "Engine.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/dto/ElementDTO.h"
#include "wx/wx.h"

#include <tr1/memory>
#include <list>

using std::list;

class ElementCore;
typedef std::tr1::shared_ptr<ElementCore> ElementCoreSmartPointer;
class Engine;

class ElementCore {
private:
	ElementDTOSmartPointer dto;
	wxString name;
	Engine* engine;
//	int priority;
public:
	ElementCore();
//
//	int GetPriority() const;
//	void SetPriority(int p);

	wxString GetName() const;
	void SetName(wxString name);

	void SetDTO(ElementDTOSmartPointer dto);
	ElementDTOSmartPointer GetDTO();

	Engine* GetEngine();
	void SetEngine(Engine* e);
	virtual ElementCoreSmartPointer NewElementCore() = 0;
	void Configure(ElementDTOSmartPointer dto);
	virtual void DoConfigure(ElementDTOSmartPointer dto) = 0; // Obs.: Antes de chamar Configure é necessário chamar SetEngine()!

	virtual bool HasResults();
	virtual ElementResults GetElementsResults();

	virtual bool IsElementConsistent();
	void AppendErrorMessage(wxString msg);

	virtual ~ElementCore();
};

#endif /* ELEMENTCORE_H_ */
