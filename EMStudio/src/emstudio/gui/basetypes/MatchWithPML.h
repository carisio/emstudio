/*
 * MatchWithPML.h
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#ifndef MATCHWITHPML_H_
#define MATCHWITHPML_H_

#include "wx/wx.h"
#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/util/constants/Constants.h"

class MatchWithPML : public BaseType {
private:
	char matchWithPML;

	void SetBit(char bit);
	void UnsetBit(char bit);
public:
	MatchWithPML();
	virtual ~MatchWithPML();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	void SetMatchedWithPML(char boundary, bool state);
	bool IsMatchedWithPML(char boundary);
};

#endif /* MATCHWITHPML_H_ */
