/*
 * ElementManager.h
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#ifndef ELEMENTMANAGER_H_
#define ELEMENTMANAGER_H_

#include "ElementGUI.h"
#include "ElementType.h"
#include <map>
#include <list>
#include <tr1/memory>
class ElementManager;
class ElementGUI;
typedef std::tr1::shared_ptr<ElementGUI> ElementGUISmartPointer;
typedef std::tr1::shared_ptr<ElementManager> ElementManagerSmartPointer;

using namespace::std;

// TODO: ORDENAÇÃO DOS METHOD/SOURCE/OBJECT/PROBE
// VERIFICAR UMA FORMA MELHOR DE FAZER ISSO!
struct ElementTypeComparator {
	bool operator()(ElementTypeSmartPointer e1, ElementTypeSmartPointer e2) const {

		return e1->GetSortIndex() < e2->GetSortIndex();
//		int i1, i2;
//		if (e1->GetName() == "Method")
//			i1 = 1;
//		else if (e1->GetName() == "Source")
//			i1 = 2;
//		else if (e1->GetName() == "2D Object")
//			i1 = 3;
//		else if (e1->GetName() == "3D Object")
//			i1 = 4;
//		else
//			i1 = 5;
//
//		if (e2->GetName() == "Method")
//			i2 = 1;
//		else if (e2->GetName() == "Source")
//			i2 = 2;
//		else if (e2->GetName() == "2D Object")
//			i2 = 3;
//		else if (e2->GetName() == "3D Object")
//			i2 = 4;
//		else
//			i2 = 5;
//
//
//		return i1 < i2;
//		return e1->GetName() < e2->GetName();
	}
};

class ElementManager {
public:
	typedef list<ElementTypeSmartPointer> ElementTypeList;
	typedef list<ElementGUISmartPointer> ElementList;
	typedef map<ElementTypeSmartPointer, list<ElementGUISmartPointer>, ElementTypeComparator> ElementMap;

private:
	ElementMap elements;
public:
	ElementManager();
	virtual ~ElementManager();

	void InformProjectChanged();
	void RegisterElement(ElementGUISmartPointer element);
	void Clear();
	void Remove(ElementGUISmartPointer element);
	int GetNumberOfElements();

	ElementMap GetElementMap();
	ElementTypeList GetElementTypeList();
	ElementList& GetElementList(ElementTypeSmartPointer type);
	ElementList GetElementList();
	ElementGUISmartPointer NewElementGUI(wxString registeredName);

	ElementGUISmartPointer NewElementGUIByDTOClassName(wxString DTOClassName);
	bool CheckIfElementsAreOK(wxString& errorMessage);

	void InvalidateAllElements();
};


#endif /* ELEMENTMANAGER_H_ */
