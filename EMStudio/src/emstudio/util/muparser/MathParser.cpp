/*
 * MathParser.cpp
 *
 *  Created on: 23/09/2013
 *      Author: leandrocarisio
 */

#include "MathParser.h"

// Inicializa o pointeiro para o mapa de constantes.
// Cria um temporário qualquer, apenas para começar.
SymbolsMapSmartPointer MathParser::symbolsMap = SymbolsMapSmartPointer();

std::map<wxString, double> MathParser::variableMap = std::map<wxString, double>();
mu::Parser MathParser::p = mu::Parser();

MathParser::MathParser(wxString expression) : expression(expression) {
	if (MathParser::symbolsMap == 0) {
		cout << "MathParser::symbolsMap eh 0. Inicializando com um ponteiro vazio" << endl;
		MathParser::symbolsMap = SymbolsMapSmartPointer(new SymbolsMap);
	}
}

MathParser::~MathParser() {

}
void MathParser::SetExpression(wxString exp) {
	expression = exp;
}
wxString MathParser::GetExpression() const {
	return expression;
}
wxString MathParser::GetExpressionWithDecimalSeparatorInformation() {
	wxString s = wxNumberFormatter::GetDecimalSeparator();
	s = s + GetExpression();
	return s;
}
void MathParser::SetExpressionWithDecimalSeparatorInformation(wxString exp) {
	char decSavedSeparator = exp.at(0);
	expression = exp.AfterFirst(decSavedSeparator);

	if (wxNumberFormatter::GetDecimalSeparator() != decSavedSeparator) {
		expression.Replace(decSavedSeparator, wxNumberFormatter::GetDecimalSeparator(), true);
	}
}
void MathParser::DefineVariables() {
	p.ClearVar();

	/* Define variables. The only allowed variable name is 't', for time */
	wxString t = "t";
	ChangeVariable(t, 0);
	p.DefineVar(t.ToStdString(), &(variableMap["t"]));
}
void MathParser::DefineConstants() {
	/* Clear map */
	p.ClearConst();

	/* Define constants */
	list<wxString> constantsName = symbolsMap->GetSymbolsName();
	list<wxString>::iterator it = constantsName.begin();
	list<wxString>::iterator end = constantsName.end();
	while (it != end) {
		mu::string_type cteName = it->ToStdString();
		p.DefineConst(cteName, symbolsMap->GetSymbol(*it));
		it++;
	}
}
bool MathParser::DefineConstantsAndCheckIfIsValid() {
	DefineConstants();
	return IsValid();
}
bool MathParser::IsValid() {
    try {
//        p.SetArgSep(';');
//        p.SetDecSep(wxNumberFormatter::GetDecimalSeparator());
//        p.SetThousandsSep('&');

        mu::string_type str = expression.ToStdString();
       	p.SetExpr(str);
        value = p.Eval();
//        std::cout << "Chegando validade ... ok" << std::endl;
//        std::cout << str << " convertido para " << value << std::endl;

	} catch (mu::Parser::exception_type &e) {
		return false;
	}
	return true;
}
void MathParser::ChangeVariable(wxString varName, double varValue) {
	variableMap[varName] = varValue;
}

double MathParser::Eval() const {
	return value;
}

std::map<wxString, double> MathParser::GetSymbolsMap() {
	 return MathParser::symbolsMap->GetMap();
}
//////////////////////////////////////////////////////////////////////////////////////
// MAPA DE CONSTANTES
SymbolsMap::SymbolsMap() {
	ClearMap();
}
SymbolsMap::~SymbolsMap() {
}

void SymbolsMap::ClearMap() {
	symbolsMap.clear();

	AddSymbol("pi", 3.14159265358);
	AddSymbol("e", 2.71828182846);
}
void SymbolsMap::AddSymbol(wxString name, double value) {
	symbolsMap[name] = value;
}
void SymbolsMap::AddSymbols(std::map<wxString, double> symbols) {
	symbolsMap = symbols;
}
double SymbolsMap::GetSymbol(wxString name) {
	return symbolsMap[name];
}
std::list<wxString> SymbolsMap::GetSymbolsName() {
	std::list<wxString> names;
	for(std::map<wxString, double>::iterator it = symbolsMap.begin(); it != symbolsMap.end(); ++it) {
	  names.push_back(it->first);
	}
	return names;
}
std::map<wxString, double> SymbolsMap::GetMap() {
	return symbolsMap;
}
