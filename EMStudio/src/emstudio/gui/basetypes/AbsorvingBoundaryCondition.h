/*
 * AbsorvingBoundaryCondition.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef ABSORVINGBOUNDARYCONDITION_H_
#define ABSORVINGBOUNDARYCONDITION_H_


#include "BaseType.h"
#include "emstudio/exception/BaseTypeIncompatibleException.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/constants/Constants.h"
#include "wx/wx.h"
#include "wx/tokenzr.h"
#include "wx/arrstr.h"

class AbsorvingBoundaryCondition : public BaseType {
private:
	wxArrayString abcTypesXDirection;
	wxArrayString abcTypesYDirection;
	wxArrayString abcTypesZDirection;

	char pec;
	char pml;
	char periodic;
	int Npml;

	void SetBit(wxString abcType, char bit);
	void SetBit(char& c, char bit);
	void UnsetBit(char& c, char bit);

	wxString GetABC(char bit);
public:
	AbsorvingBoundaryCondition();
	virtual ~AbsorvingBoundaryCondition();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	wxArrayString GetAvailableABCsXDirection();
	wxArrayString GetAvailableABCsYDirection();
	wxArrayString GetAvailableABCsZDirection();

	void SetABCXNeg(wxString abcType);
	void SetABCXPos(wxString abcType);
	void SetABCYNeg(wxString abcType);
	void SetABCYPos(wxString abcType);
	void SetABCZNeg(wxString abcType);
	void SetABCZPos(wxString abcType);
	void SetNpml(int npml);
	wxString GetABCXNeg();
	wxString GetABCXPos();
	wxString GetABCYNeg();
	wxString GetABCYPos();
	wxString GetABCZNeg();
	wxString GetABCZPos();
	int GetNpml();

	bool IsPML(char wall);
	bool IsPeriodic(char wall);
	bool IsPEC(char wall);
};

#endif /* ABSORVINGBOUNDARYCONDITION_H_ */
