/*
 * IntMathExpressionParserRenderer.cpp
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#include "IntMathExpressionParserRenderer.h"

IntMathExpressionParserRenderer::IntMathExpressionParserRenderer() {

}

IntMathExpressionParserRenderer::~IntMathExpressionParserRenderer() {

}



wxGridCellRenderer* IntMathExpressionParserRenderer::Clone() const {
	MathExpressionParserRenderer* clone = new IntMathExpressionParserRenderer;

	return clone;
}
