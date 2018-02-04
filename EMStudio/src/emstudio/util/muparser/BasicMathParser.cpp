/*
 * BasicMathParser.cpp
 *
 *  Created on: 23/07/2014
 *      Author: leandrocarisio
 */

#include "BasicMathParser.h"

BasicMathParser::BasicMathParser(wxString expression)
	: expression(expression), val(0) {

}

BasicMathParser::~BasicMathParser() {
}

bool BasicMathParser::IsValid() {
    try {
        mu::string_type str = expression.ToStdString();
       	p.SetExpr(str);
        val = p.Eval();
	} catch (mu::Parser::exception_type &e) {
		return false;
	}
	return true;
}
double BasicMathParser::Eval() const {
	return val;
}
void BasicMathParser::SetExpression(wxString exp) {
	expression = exp;
}
