/*
 * SelectField.h
 *
 *  Created on: 25/04/2013
 *      Author: Leandro
 */

#ifndef SELECTFIELD_H_
#define SELECTFIELD_H_

#include "IntWrapper.h"

class SelectField : public IntWrapper {
public:
	enum FieldName{EX, EY, EZ, ALL_E_FIELDS, HX, HY, HZ, ALL_H_FIELDS, ALL_FIELDS};

public:
	SelectField();

	static wxArrayString GetPossiblePriorities();

	virtual wxString GetUserFriendlyStringRepresentation();
	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetBaseTypeClassName();

	virtual ~SelectField();
};

#endif /* SELECTFIELD_H_ */
