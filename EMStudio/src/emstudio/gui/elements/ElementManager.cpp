/*
 * ElementManager.cpp
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#include "ElementManager.h"

#include <iostream>
using namespace::std;

ElementManager::ElementManager() {
	elements = ElementMap();
}

ElementManager::~ElementManager() {
	Clear();
}
void ElementManager::InformProjectChanged() {
	ElementManager::ElementMap::iterator it = elements.begin();
	ElementManager::ElementMap::iterator end = elements.end();

	while(it != end) {
		ElementTypeSmartPointer type = it->first;

		ElementManager::ElementList eList = it->second;

		ElementManager::ElementList::iterator itList = eList.begin();
		ElementManager::ElementList::iterator itListEnd = eList.end();

		while (itList != itListEnd) {
			ElementGUISmartPointer element = *itList;
			element->ProjectChanged();
			itList++;
		}
		it++;
	}
}
void ElementManager::RegisterElement(ElementGUISmartPointer element) {
	ElementManager::ElementList& elementsList = GetElementList(element->GetType());
	elementsList.push_back(element);
	InformProjectChanged();
}
ElementManager::ElementMap ElementManager::GetElementMap() {
	return elements;
}
ElementManager::ElementTypeList ElementManager::GetElementTypeList() {
	ElementManager::ElementTypeList result = list<ElementTypeSmartPointer>();

	for(ElementMap::iterator it = elements.begin(); it != elements.end(); ++it) {
		result.push_back(it->first);
	}
	return result;
}

ElementManager::ElementList& ElementManager::GetElementList(ElementTypeSmartPointer type) {
	if (elements.find(type) == elements.end()) {
		elements[type] = list<ElementGUISmartPointer>();
	}
	return elements[type];
}

ElementManager::ElementList ElementManager::GetElementList() {
	ElementManager::ElementList allElements;

	ElementTypeList typeList = GetElementTypeList();
	ElementTypeList::iterator it = typeList.begin();
	ElementTypeList::iterator endTypes = typeList.end();

	while (it != endTypes) {
		ElementList& elementsList = GetElementList(*it);
		ElementList::iterator itElements = elementsList.begin();
		ElementList::iterator endElements = elementsList.end();

		while (itElements != endElements) {
			allElements.push_back(*itElements);
			itElements++;
		}
		it++;
	}
	return allElements;
}

ElementGUISmartPointer ElementManager::NewElementGUI(wxString registeredName) {
	ElementTypeList typeList = GetElementTypeList();
	ElementTypeList::iterator it = typeList.begin();
	ElementTypeList::iterator endTypes = typeList.end();

	ElementGUISmartPointer e;

	while (it != endTypes) {
		ElementList& elementsList = GetElementList(*it);
		ElementList::iterator itElements = elementsList.begin();
		ElementList::iterator endElements = elementsList.end();

		while (itElements != endElements) {
			if (registeredName == (*itElements)->GetRegisteredName()) {
				e = (*itElements)->NewElementGUI();
				return e;
			}
			itElements++;
		}
		it++;
	}
	return e;
}

void ElementManager::Clear() {
	elements.clear();
}
int ElementManager::GetNumberOfElements() {
	int num = 0;

	for(ElementMap::iterator it = elements.begin(); it != elements.end(); ++it) {
		list<ElementGUISmartPointer> elementsByType = it->second;

		num += elementsByType.size();
	}
	return num;
}
void ElementManager::Remove(ElementGUISmartPointer e) {

	ElementTypeList typeList = GetElementTypeList();
	ElementTypeList::iterator it = typeList.begin();
	ElementTypeList::iterator endTypes = typeList.end();

	bool removeKey = false;

	while (it != endTypes) {
		if (e->GetType()->GetName() == it->get()->GetName()) {
			ElementList& elementsList = GetElementList(*it);
			elementsList.remove(e);
			if (elementsList.size() == 0) {
				removeKey = true;
			}
			break;
		}
		it++;
	}

	if (removeKey) {
		ElementMap::iterator chave = elements.find(e->GetType());
		elements.erase(chave);
	}
	InformProjectChanged();
}

bool ElementManager::CheckIfElementsAreOK(wxString& errorMessage) {
	errorMessage = "";
	bool ok = true;

	ElementManager::ElementList elementList = GetElementList();
	ElementManager::ElementList::iterator it = elementList.begin();
	ElementManager::ElementList::iterator itEnd = elementList.end();

	while (it != itEnd) {
		wxString elementError = "";
		bool elementOK = true;
		/* Verifica se as propriedades individuais do elemento estão OK */
		if ((*it)->IsPropertiesValid()) {
			/* Se as propriedades individuais estão ok, é necessário testar as propriedades conjuntas */
			if ((*it)->IsAllPropertiesTogetherValid()) {

			} else {
				elementOK = false;
				elementError.Append((*it)->GetAllPropertiesTogetherErrorMessage());
			}
		} else {
			elementOK = false;
			elementError.Append((*it)->GetPropertiesErrorMessage());
		}

		if (!elementOK) {
			errorMessage.Append("Errors found in element " + (*it)->GetUserDefinedName() + ":\n\n");
			errorMessage.Append(elementError).Append("\n");
		}
		ok = ok && elementOK;

		it++;
	}
	return ok;
}
void ElementManager::InvalidateAllElements() {
	ElementTypeList typeList = GetElementTypeList();
	ElementTypeList::iterator it = typeList.begin();
	ElementTypeList::iterator endTypes = typeList.end();

	ElementGUISmartPointer e;

	while (it != endTypes) {
		ElementList& elementsList = GetElementList(*it);
		ElementList::iterator itElements = elementsList.begin();
		ElementList::iterator endElements = elementsList.end();

		while (itElements != endElements) {
			(*itElements)->SetChanged(true);
			itElements++;
		}
		it++;
	}
	InformProjectChanged();
}

ElementGUISmartPointer ElementManager::NewElementGUIByDTOClassName(wxString DTOClassName) {

	ElementTypeList typeList = GetElementTypeList();
	ElementTypeList::iterator it = typeList.begin();
	ElementTypeList::iterator endTypes = typeList.end();

	ElementGUISmartPointer e;

	while (it != endTypes) {
		ElementList& elementsList = GetElementList(*it);
		ElementList::iterator itElements = elementsList.begin();
		ElementList::iterator endElements = elementsList.end();

		while (itElements != endElements) {
			if (DTOClassName == (*itElements)->GetDTO()->GetDTOClassName()) {
				e = (*itElements)->NewElementGUI();
				return e;
			}
			itElements++;
		}
		it++;
	}
	return e;
}
