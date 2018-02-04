/*
 * MathExpressionParserRenderer.cpp
 *
 *  Created on: 20/09/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionParserRenderer.h"

MathExpressionParserRenderer::MathExpressionParserRenderer() {

}

MathExpressionParserRenderer::~MathExpressionParserRenderer() {
}

wxGridCellRenderer* MathExpressionParserRenderer::Clone() const {
	MathExpressionParserRenderer* clone = new MathExpressionParserRenderer;

	return clone;
}
