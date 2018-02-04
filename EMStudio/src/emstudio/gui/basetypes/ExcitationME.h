/*
 * ExcitationME.h
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#ifndef EXCITATIONME_H_
#define EXCITATIONME_H_

#include <vector>

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "Excitation.h"
#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/units/Units.h"
#include "emstudio/util/constants/Constants.h"

#include "wx/tokenzr.h"
#include "wx/wx.h"
#include "wx/arrstr.h"


class ExcitationME : public BaseType {
private:
	MathParser parser;
	wxArrayString types;
	wxString type;
	std::vector< std::pair<wxString, wxString> > parameters;
public:
	ExcitationME();

	void SetType(wxString type);
	wxString GetType();
	wxArrayString GetTypes();
	int GetNumberOfParameters();
	std::vector<std::pair<wxString, wxString> > GetParameters();
	void SetParameter(int parameterNumber, wxString parameter);
	std::pair<wxString, wxString> GetParameter(int parameterNumber);

	bool IsExcitationValid();
	Excitation ConvertToExcitation();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual wxString GetUserFriendlyStringRepresentation();
	virtual void SetUserFriendlyStringRepresentation(wxString s);

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	virtual ~ExcitationME();
};


#endif /* EXCITATIONME_H_ */
