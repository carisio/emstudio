/*
 * MathExpressionParser.h
 *
 *  Created on: 20/09/2013
 *      Author: leandrocarisio
 */

#ifndef MATHEXPRESSIONPARSER_H_
#define MATHEXPRESSIONPARSER_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "BaseType.h"

using namespace::std;

class MathExpressionParser : public BaseType {
private:
	MathParser parser;

public:
	MathExpressionParser();
	virtual ~MathExpressionParser();

	wxString GetExpression() const;
	void SetExpression(wxString expression);

	/* Antes e chamar Eval é necessário chamar IsExpressionValid. Se tiver certeza que não há erro na fórmula, ForceEval pode ser chamado */
	virtual double Eval();
	double ForceEval();
	virtual bool IsExpressionValid();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* MATHEXPRESSIONPARSER_H_ */
