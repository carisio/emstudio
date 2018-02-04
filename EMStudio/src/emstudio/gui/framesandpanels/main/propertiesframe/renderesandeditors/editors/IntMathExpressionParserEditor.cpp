/*
 * IntMathExpressionParserEditor.cpp
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#include "IntMathExpressionParserEditor.h"

IntMathExpressionParserEditor::IntMathExpressionParserEditor() {

}

IntMathExpressionParserEditor::~IntMathExpressionParserEditor() {
}

wxGridCellEditor* IntMathExpressionParserEditor::Clone() const {
	MathExpressionParserEditor* clone = new IntMathExpressionParserEditor;

	return clone;
}
