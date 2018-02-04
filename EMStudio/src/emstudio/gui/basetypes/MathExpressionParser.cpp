/*
 * MathExpressionParser.cpp
 *
 *  Created on: 20/09/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionParser.h"

MathExpressionParser::MathExpressionParser() {
	SetWriteVersion(1);
}

MathExpressionParser::~MathExpressionParser() {
}

wxString MathExpressionParser::GetExpression() const {
	return parser.GetExpression();
}
void MathExpressionParser::SetExpression(wxString expression) {
	parser.SetExpression(expression);
}

double MathExpressionParser::Eval() {
	return parser.Eval();
}
double MathExpressionParser::ForceEval() {
	IsExpressionValid();
	return Eval();
}
bool MathExpressionParser::IsExpressionValid() {
	return parser.DefineConstantsAndCheckIfIsValid();
}
void MathExpressionParser::Copy(BaseType* b) {
	this->SetExpression((static_cast<MathExpressionParser*>(b))->GetExpression());
}

wxString MathExpressionParser::GetBaseTypeClassName() {
	return "MathExpressionParser";
}

wxString MathExpressionParser::GetUserFriendlyStringRepresentation() {
	wxString result;
	if (IsExpressionValid()) {
		result = Converter::DoubleToFormattedString(Eval());
	} else {
		result = "Invalid expression";
	}
	return result;
}

void MathExpressionParser::SetUserFriendlyStringRepresentation(wxString str) {
	SetExpression(str);
}
void MathExpressionParser::DoWrite(OutputBuffer& buffer) {
	wxString str = parser.GetExpressionWithDecimalSeparatorInformation();
	buffer.WriteString(str);
}
void MathExpressionParser::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	wxString expression = buffer.ReadString();
	parser.SetExpressionWithDecimalSeparatorInformation(expression);
}
