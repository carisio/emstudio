/*
 * RectangularTubeGeometryME.h
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#ifndef RECTANGULARTUBEGEOMETRYME_H_
#define RECTANGULARTUBEGEOMETRYME_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "Point3DME.h"
#include "BaseType.h"
#include "wx/wx.h"

class RectangularTubeGeometryME : public BaseType {
private:
	enum Orientation{X, Y, Z};
	/* Representa a orientação do tubo */
	int orientation;

	/* Face 1 (base): */
	MathParser bCutAt;
	MathParser bCoord1Begin, bCoord1End, bCoord2Begin, bCoord2End;
	MathParser bCoord1Thickness, bCoord2Thickness;

	/* Face 2 (topo): */
	MathParser tCutAt;
	MathParser tCoord1Begin, tCoord1End, tCoord2Begin, tCoord2End;
	MathParser tCoord1Thickness, tCoord2Thickness;

public:
	RectangularTubeGeometryME();
	virtual ~RectangularTubeGeometryME();

	void SetXOriented();
	void SetYOriented();
	void SetZOriented();

	bool IsXOriented();
	bool IsYOriented();
	bool IsZOriented();

	void SetBaseCutAtExpression(wxString expr);
	void SetBaseCoord1BeginExpression(wxString expr);
	void SetBaseCoord1EndExpression(wxString expr);
	void SetBaseCoord2BeginExpression(wxString expr);
	void SetBaseCoord2EndExpression(wxString expr);
	void SetBaseCoord1ThicknessExpression(wxString expr);
	void SetBaseCoord2ThicknessExpression(wxString expr);
	void SetTopCutAtExpression(wxString expr);
	void SetTopCoord1BeginExpression(wxString expr);
	void SetTopCoord1EndExpression(wxString expr);
	void SetTopCoord2BeginExpression(wxString expr);
	void SetTopCoord2EndExpression(wxString expr);
	void SetTopCoord1ThicknessExpression(wxString expr);
	void SetTopCoord2ThicknessExpression(wxString expr);

	wxString GetBaseCutAtExpression();
	wxString GetBaseCoord1BeginExpression();
	wxString GetBaseCoord1EndExpression();
	wxString GetBaseCoord2BeginExpression();
	wxString GetBaseCoord2EndExpression();
	wxString GetBaseCoord1ThicknessExpression();
	wxString GetBaseCoord2ThicknessExpression();
	wxString GetTopCutAtExpression();
	wxString GetTopCoord1BeginExpression();
	wxString GetTopCoord1EndExpression();
	wxString GetTopCoord2BeginExpression();
	wxString GetTopCoord2EndExpression();
	wxString GetTopCoord1ThicknessExpression();
	wxString GetTopCoord2ThicknessExpression();

	double GetBaseCutAt();
	double GetBaseCoord1Begin();
	double GetBaseCoord1End();
	double GetBaseCoord2Begin();
	double GetBaseCoord2End();
	double GetBaseCoord1Thickness();
	double GetBaseCoord2Thickness();
	double GetTopCutAt();
	double GetTopCoord1Begin();
	double GetTopCoord1End();
	double GetTopCoord2Begin();
	double GetTopCoord2End();
	double GetTopCoord1Thickness();
	double GetTopCoord2Thickness();

	bool IsBaseCutAtExpressionValid();
	bool IsBaseCoord1BeginExpressionValid();
	bool IsBaseCoord1EndExpressionValid();
	bool IsBaseCoord2BeginExpressionValid();
	bool IsBaseCoord2EndExpressionValid();
	bool IsBaseCoord1ThicknessExpressionValid();
	bool IsBaseCoord2ThicknessExpressionValid();
	bool IsTopCutAtExpressionValid();
	bool IsTopCoord1BeginExpressionValid();
	bool IsTopCoord1EndExpressionValid();
	bool IsTopCoord2BeginExpressionValid();
	bool IsTopCoord2EndExpressionValid();
	bool IsTopCoord1ThicknessExpressionValid();
	bool IsTopCoord2ThicknessExpressionValid();
	bool IsGeometryValid();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* RECTANGULARTUBEGEOMETRYME_H_ */
