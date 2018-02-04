/*
 * Point3DME.h
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#ifndef POINT3DME_H_
#define POINT3DME_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "BaseType.h"
#include "wx/wx.h"

class Point3DME : public BaseType {
private:
	MathParser xParser, yParser, zParser;
//	wxString xExpression, yExpression, zExpression;
public:
	Point3DME();
	virtual ~Point3DME();

	void SetXExpression(wxString x);
	void SetYExpression(wxString y);
	void SetZExpression(wxString z);
	wxString GetXExpression();
	wxString GetYExpression();
	wxString GetZExpression();

	bool isXExpressionValid();
	bool isYExpressionValid();
	bool isZExpressionValid();
	bool isPointValid();
	bool EvalExpressions();

	double GetX() const;
	double GetY() const;
	double GetZ() const;

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* POINT3DME_H_ */
