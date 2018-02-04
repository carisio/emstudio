/*
 * IntMathExpressionParserEditor.h
 *
 *  Created on: 15/10/2013
 *      Author: leandrocarisio
 */

#ifndef INTMATHEXPRESSIONPARSEREDITOR_H_
#define INTMATHEXPRESSIONPARSEREDITOR_H_

#include "MathExpressionParserEditor.h"

class IntMathExpressionParserEditor : public MathExpressionParserEditor {
public:
	IntMathExpressionParserEditor();
	virtual ~IntMathExpressionParserEditor();

	virtual wxGridCellEditor *Clone () const;
};

#endif /* INTMATHEXPRESSIONPARSEREDITOR_H_ */
