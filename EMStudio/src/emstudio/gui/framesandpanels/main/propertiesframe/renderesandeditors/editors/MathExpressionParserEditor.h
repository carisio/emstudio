/*
 * MathExpressionParserEditor.h
 *
 *  Created on: 20/09/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONPARSEREDITOR_H_
#define MATHEXPRESSIONPARSEREDITOR_H_

#include "wx/grid.h"

class MathExpressionParserEditor  : public wxGridCellTextEditor {
public:
	MathExpressionParserEditor();
	virtual ~MathExpressionParserEditor();

	virtual wxGridCellEditor *Clone () const;
	virtual void BeginEdit(int row, int col, wxGrid* grid);
};

#endif /* MATHEXPRESSIONPARSEREDITOR_H_ */
