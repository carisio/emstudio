/*
 * GroundParameters.h
 *
 *  Created on: 18/03/2015
 *      Author: Leandro
 */

#ifndef SRC_EMSTUDIO_GUI_BASETYPES_GROUNDPARAMETERS_H_
#define SRC_EMSTUDIO_GUI_BASETYPES_GROUNDPARAMETERS_H_


#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "BaseType.h"
#include "wx/wx.h"
#include "Material.h"

namespace mom {

class GroundParameters  : public BaseType {
private:
	Material ground1;
	Material ground2;
	int gpflag; // Like (GE) card, 0 = Free space, 1 = Currents on segments touching ground are interpolated, -1 = go to zero
	int cliff; // Like (RP) card, 2 = linear and 3 = circular
	bool ground2Exists;

	MathParser distanceBelowGround;
	MathParser distanceFromOrigin;
	MathParser numberOfWires;
	MathParser wireLength;
	MathParser wireRadius;
public:
	GroundParameters();
	virtual ~GroundParameters();

	/* Herdados de BaseType */
	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	/* Getters and setters */
	Material GetGround1();
	Material GetGround2();
	bool IsGround2();
	bool IsCircularCliff();
	bool IsLinearCliff();
	bool IsCurrentsOnSegmentsTouchingGroundGoToZero();
	bool IsCurrentsOnSegmentsTouchingGroundInterpolated();
	wxString GetDistanceBelowGroundExpression();
	wxString GetDistanceFromOriginExpression();
	wxString GetNumberOfWiresExpression();
	wxString GetWireLengthExpression();
	wxString GetWireRadiusExpression();
	double GetDistanceBelowGround();
	double GetDistanceFromOrigin();
	int GetNumberOfWires();
	double GetWireLength();
	double GetWireRadius();
	void SetGround1(Material m);
	void SetGround2(Material m);
	void SetGround2Exists(bool b);
	void SetCircularCliff();
	void SetLinearCliff();
	void SetCurrentsOnSegmentsTouchingGroundGoToZero();
	void SetCurrentsOnSegmentsTouchingGroundInterpolated();
	void SetDistanceBelowGroundExpression(wxString expr);
	void SetDistanceFromOriginExpression(wxString expr);
	void SetNumberOfWiresExpression(wxString expr);
	void SetWireLengthExpression(wxString expr);
	void SetWireRadiusExpression(wxString expr);
	/* Check if the expressions are valid */
	bool IsDistanceBelowGroundExpressionValid();
	bool IsDistanceFromOriginExpressionValid();
	bool IsNumberOfWiresExpressionValid();
	bool IsWireLengthExpressionValid();
	bool IsWireRadiusExpressionValid();
	bool IsGroundParametersValid();
	/* Other methods */
	int GetNumberOfGround(); /* return 0, 1 or 2 */
};

} /* namespace mom */

#endif /* SRC_EMSTUDIO_GUI_BASETYPES_GROUNDPARAMETERS_H_ */
