/*
 * BasicMathParser.h
 *
 *  Created on: 23/07/2014
 *      Author: leandrocarisio
 */

#ifndef BASICMATHPARSER_H_
#define BASICMATHPARSER_H_

#include "muParser.h"
#include "wx/wx.h"

class BasicMathParser {
	wxString expression;
	double val;
	mu::Parser p;
public:
	BasicMathParser(wxString expression = "0");
	virtual ~BasicMathParser();

	bool IsValid();
	void SetExpression(wxString exp);
	double Eval() const;
};

#endif /* BASICMATHPARSER_H_ */
