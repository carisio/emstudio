/*
 * DirectionPlaneWaveMEME.h
 *
 *  Created on: 07/11/2013
 *      Author: leandrocarisio
 */

#ifndef DIRECTIONPLANEWAVEME_H_
#define DIRECTIONPLANEWAVEME_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "BaseType.h"
#include "wx/wx.h"

class DirectionPlaneWaveME : public BaseType {
private:
	MathParser thetaParser, phiParser, psiParser;
//	wxString thetaExpression, phiExpression, psiExpression;
public:
	DirectionPlaneWaveME();
	virtual ~DirectionPlaneWaveME();

	void SetThetaExpression(wxString theta);
	void SetPhiExpression(wxString phi);
	void SetPsiExpression(wxString psi);
	wxString GetThetaExpression();
	wxString GetPhiExpression();
	wxString GetPsiExpression();

	bool isThetaExpressionValid();
	bool isPhiExpressionValid();
	bool isPsiExpressionValid();
	bool isExpressionsValid();
	bool EvalExpressions();

	double GetTheta() const;
	double GetPhi() const;
	double GetPsi() const;

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* DIRECTIONPLANEWAVEME_H_ */
