/*
 * Result.cpp
 *
 *  Created on: 09/01/2012
 *      Author: leandrocarisio
 */

#include "Result.h"
#include <iostream>
using namespace::std;
//////////////////////////////////////////
// ResultTree
//////////////////////////////////////////
ResultTree::ResultTree() {

}
ResultTree::~ResultTree() {
}

void ResultTree::SetEngineResults(std::list<EngineResults>) {
	this->SetEngineResults(engineResults);
}
std::list<EngineResults>& ResultTree::GetEngineResults() {
	return engineResults;
}

void ResultTree::SetProjectCode(wxString prjCode) {
	this->projectCode = prjCode;
}
wxString ResultTree::GetProjectCode() {
	return projectCode;
}
void ResultTree::ClearResults() {
	engineResults.clear();
}
void ResultTree::AddEngineResults(EngineResults er) {
	engineResults.push_back(er);
}
//////////////////////////////////////////
// Result
//////////////////////////////////////////

Result::Result() : name() {
	AddProperty(Property("Name", &name));
}

wxString Result::GetName() {
    return name.GetUserFriendlyStringRepresentation();
}

void Result::SetName(wxString name) {
    this->name.SetUserFriendlyStringRepresentation(name);
}

PropertyableSmartPointer Result::NewPropertyable() {
	return std::tr1::static_pointer_cast<Propertyable>(NewResult());
}

Result::~Result() {
}


//////////////////////////////////////////
// ElementResults
//////////////////////////////////////////

ElementResults::ElementResults(wxString DTOClassName, wxString userDefinedName, std::list<ResultSmartPointer> results)
	: DTOClassName(DTOClassName), name(userDefinedName), results(results) {

}
ElementResults::~ElementResults() {

}
wxIcon ElementResults::GetIcon(ElementManagerSmartPointer em) {
	return em->NewElementGUIByDTOClassName(DTOClassName)->GetIcon();
}

wxString ElementResults::GetName() const {
    return name;
}

wxString ElementResults::GetDTOClassName() const {
    return DTOClassName;
}

std::list<ResultSmartPointer>& ElementResults::GetResults()  {
    return results;
}

void ElementResults::SetName(wxString name) {
    this->name = name;
}

void ElementResults::SetDTOClassName(wxString dtoname) {
    this->DTOClassName = dtoname;
}

void ElementResults::SetResults(std::list<ResultSmartPointer> results) {
    this->results = results;
}


//////////////////////////////////////////
// EngineResults
//////////////////////////////////////////

EngineResults::EngineResults(wxString DTOClassName, wxString userDefinedName, std::list<ElementResults> elementResults, std::list<ResultSmartPointer> myOwnResults)
	: DTOClassName(DTOClassName), name(userDefinedName), elementResults(elementResults), myOwnResults(myOwnResults) {
}
EngineResults::~EngineResults() {

}
wxIcon EngineResults::GetIcon(ElementManagerSmartPointer em) {
	return em->NewElementGUIByDTOClassName(DTOClassName)->GetIcon();
}

wxString EngineResults::GetName() const {
    return name;
}
wxString EngineResults::GetDTOClassName() const {
	return DTOClassName;
}
std::list<ElementResults>& EngineResults::GetElementsResults() {
    return elementResults;
}
void EngineResults::SetDTOClassName(wxString dtoName) {
	DTOClassName = dtoName;
}
void EngineResults::SetName(wxString name) {
    this->name = name;
}

void EngineResults::SetElementsResults(std::list<ElementResults> results) {
    this->elementResults = results;
}
std::list<ResultSmartPointer>& EngineResults::GetMyResults() {
	return myOwnResults;
}
void EngineResults::SetMyResults(std::list<ResultSmartPointer> results) {
	this->myOwnResults = results;
}
