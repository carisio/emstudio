/*
 * MathExpressionParserRenderer.h
 *
 *  Created on: 20/09/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONPARSERRENDERER_H_
#define MATHEXPRESSIONPARSERRENDERER_H_

#include "wx/grid.h"

class MathExpressionParserRenderer : public wxGridCellAutoWrapStringRenderer{
public:
	MathExpressionParserRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~MathExpressionParserRenderer();
};

#endif /* MATHEXPRESSIONPARSERRENDERER_H_ */
