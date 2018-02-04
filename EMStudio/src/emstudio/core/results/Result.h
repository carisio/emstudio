/*
 * Result.h
 *
 *  Created on: 09/01/2012
 *      Author: leandrocarisio
 */

#ifndef RESULT_H_
#define RESULT_H_

#include "emstudio/gui/basetypes/StringWrapper.h"
#include "emstudio/gui/elements/ElementManager.h"

#include "wx/wx.h"

#include <tr1/memory>
#include <list>

class Result;
class EngineResults;

typedef std::tr1::shared_ptr<Result> ResultSmartPointer;

class ResultTree {
private:
	std::list<EngineResults> engineResults;
	wxString projectCode;
public:
	ResultTree();
	virtual ~ResultTree();

	void SetEngineResults(std::list<EngineResults>);
	std::list<EngineResults>& GetEngineResults();

    void SetProjectCode(wxString prjCode);
    wxString GetProjectCode();

    void ClearResults();
    void AddEngineResults(EngineResults er);
};

class Result : public Propertyable {
private:
	StringWrapper name;
	wxString md5Project;

public:
	Result();
	virtual ~Result();

    wxString GetName();
    void SetName(wxString name);

    PropertyableSmartPointer NewPropertyable();
    virtual ResultSmartPointer NewResult() = 0;
    virtual wxIcon GetIcon() = 0;
    virtual bool ExportData(wxString fileName) = 0;
    virtual wxString GetResultClassName() = 0;
};

class ElementResults {
private:
	wxString DTOClassName;
	wxString name;
	std::list<ResultSmartPointer> results;

public:
	ElementResults(wxString DTOClassName, wxString userDefinedName, std::list<ResultSmartPointer> results = std::list<ResultSmartPointer>());
	~ElementResults();

    wxIcon GetIcon(ElementManagerSmartPointer em);

    std::list<ResultSmartPointer>& GetResults();
    void SetResults(std::list<ResultSmartPointer> results);

    wxString GetName() const;
    void SetName(wxString name);

    wxString GetDTOClassName() const;
    void SetDTOClassName(wxString dtoclassname);
};

class EngineResults {
private:
	wxString DTOClassName;
	wxString name;
	std::list<ElementResults> elementResults;
	std::list<ResultSmartPointer> myOwnResults;
public:
	EngineResults(wxString DTOClassName, wxString userDefinedName, std::list<ElementResults> elementResults = std::list<ElementResults>(), std::list<ResultSmartPointer> myOwnResults = std::list<ResultSmartPointer>());
	~EngineResults();

    wxIcon GetIcon(ElementManagerSmartPointer em);

    wxString GetName() const;
    void SetName(wxString name);

    wxString GetDTOClassName() const;
    void SetDTOClassName(wxString dtoclassname);

    std::list<ElementResults>& GetElementsResults();
    void SetElementsResults(std::list<ElementResults> results);

    std::list<ResultSmartPointer>& GetMyResults();
    void SetMyResults(std::list<ResultSmartPointer> results);
};
#endif /* RESULT_H_ */
