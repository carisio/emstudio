/*
 * MathExpressionParserEditor.cpp
 *
 *  Created on: 20/09/2013
 *      Author: leandrocarisio
 */

#include "MathExpressionParserEditor.h"
#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "../../PropertiesGridTable.h"
#include <iostream>
using namespace::std;

MathExpressionParserEditor::MathExpressionParserEditor() {
	cout << "MathExpressionParserEditor()" << endl;
}

MathExpressionParserEditor::~MathExpressionParserEditor() {
}

wxGridCellEditor* MathExpressionParserEditor::Clone() const {
	MathExpressionParserEditor* clone = new MathExpressionParserEditor;

	return clone;
}
/* Diferentemente dos outros editores baseados em string, nesse caso o que deve ser enviado
 * para edi��o n�o � o conte�do da c�lula (parser.Eval()), e sim a express�o. Por isso, � necess�rio
 * alterar o m�todo BeginEdit de wxGridCellTextEditor. */
void MathExpressionParserEditor::BeginEdit(int row, int col, wxGrid* grid) {
    wxASSERT_MSG(m_control, wxT("The wxGridCellEditor must be created first!"));

    // wxGridCellTextEditor:
    // m_value = grid->GetTable()->GetValue(row, col);
	PropertiesGridTable* table = static_cast<PropertiesGridTable*>(grid->GetTable());
	MathExpressionParser mep = *(static_cast<MathExpressionParser*>(table->GetValueAsBaseType(row, col)));
//	grid->SetGridCursor(row,col);

    DoBeginEdit(mep.GetExpression());
}
