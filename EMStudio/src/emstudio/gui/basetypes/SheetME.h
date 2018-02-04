/*
 * SheetME.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef SHEETME_H_
#define SHEETME_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "BaseType.h"
#include "Sheet.h"
#include "wx/wx.h"

class SheetME : public BaseType {
private:
	enum SheetCutAtPlane{XY, YZ, ZX};
	/* Representa o plano em que a placa está */
	int plane;
	/* Representa as coordenadas da placa. */
	MathParser x0Parser, y0Parser, z0Parser;
	MathParser x1Parser, y1Parser, z1Parser;
public:
	SheetME();

	/* Métodos acessores para as coordenadas da placa */
	void SetX0Expression(wxString x);
	void SetY0Expression(wxString y);
	void SetZ0Expression(wxString z);
	void SetX1Expression(wxString x);
	void SetY1Expression(wxString y);
	void SetZ1Expression(wxString z);
	wxString GetX0Expression();
	wxString GetY0Expression();
	wxString GetZ0Expression();
	wxString GetX1Expression();
	wxString GetY1Expression();
	wxString GetZ1Expression();

	bool IsX0ExpressionValid();
	bool IsY0ExpressionValid();
	bool IsZ0ExpressionValid();
	bool IsX1ExpressionValid();
	bool IsY1ExpressionValid();
	bool IsZ1ExpressionValid();
	bool IsSheetValid();
	bool EvalExpressions();

	double GetX0() const;
	double GetY0() const;
	double GetZ0() const;
	double GetX1() const;
	double GetY1() const;
	double GetZ1() const;

	bool IsCutAtX();
	bool IsCutAtY();
	bool IsCutAtZ();
	void SetCutAtX(wxString x);
	void SetCutAtY(wxString y);
	void SetCutAtZ(wxString z);
	wxString GetCutAtExpression();
	double GetCutAt();

	Sheet ConvertToSheet();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	virtual ~SheetME();
};

#endif /* SHEETME_H_ */
