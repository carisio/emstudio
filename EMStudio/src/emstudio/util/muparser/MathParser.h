/*
 * MathParser.h
 *
 *  Created on: 23/09/2013
 *      Author: leandrocarisio
 */

#ifndef MATHPARSER_H_
#define MATHPARSER_H_

#include "muParser.h"
#include <map>
#include <list>
#include <tr1/memory>
#include "emstudio/util/converters/Converter.h"
#include "wx/numformatter.h"
#include "wx/wx.h"

class SymbolsMap;
typedef std::tr1::shared_ptr<SymbolsMap> SymbolsMapSmartPointer;

class MathParser {
private:
	static SymbolsMapSmartPointer symbolsMap;
	static std::map<wxString, double> variableMap;
	static mu::Parser p;

	wxString expression;
	double value;
public:
	MathParser(wxString expression = "0");
	virtual ~MathParser();

	/* GetExpression retorna apenas a expressão digitada pelo usuário */
	void SetExpression(wxString exp);
	wxString GetExpression() const;

	/* GetExpressionWithDecimalSeparatorInformation concatena o caracter representando o separador decimal
	 * usado com a expressão digitada pelo usuário. Isso é necessário na hora de abrir e salvar arquivos.
	 * Se um arquivo de projeto foi criado com determinado locale, é necessário guardar a informação do separador
	 * decimal para, quando for abrir o projeto com diferente locale, não haver problemas. */
	wxString GetExpressionWithDecimalSeparatorInformation();
	void SetExpressionWithDecimalSeparatorInformation(wxString exp);

	void DefineConstants();
	void DefineVariables();
	bool DefineConstantsAndCheckIfIsValid();

	bool IsValid();
	void ChangeVariable(wxString varName, double varValue);

	double Eval() const;

	static void SetSymbolsMap(SymbolsMapSmartPointer symMap) { symbolsMap = symMap; }
	static std::map<wxString, double> GetSymbolsMap();
};

class SymbolsMap {
private:
	std::map<wxString, double> symbolsMap;

public:
	SymbolsMap();
	virtual ~SymbolsMap();

	void ClearMap();
	void AddSymbol(wxString name, double value);
	void AddSymbols(std::map<wxString, double> symbols);
	std::list<wxString> GetSymbolsName();
	double GetSymbol(wxString name);

	std::map<wxString, double> GetMap();
};

#endif /* MATHPARSER_H_ */
