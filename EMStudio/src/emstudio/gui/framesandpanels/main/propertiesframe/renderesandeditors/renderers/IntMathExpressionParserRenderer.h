/*
 * IntMathExpressionParserRenderer.h
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#ifndef INTMATHEXPRESSIONPARSERRENDERER_H_
#define INTMATHEXPRESSIONPARSERRENDERER_H_

#include "MathExpressionParserRenderer.h"

class IntMathExpressionParserRenderer : public MathExpressionParserRenderer {
public:
	IntMathExpressionParserRenderer();
	virtual ~IntMathExpressionParserRenderer();
	virtual wxGridCellRenderer* Clone() const;
};

#endif /* INTMATHEXPRESSIONPARSERRENDERER_H_ */
