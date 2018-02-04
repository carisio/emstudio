/*
 * Priority.h
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#ifndef PRIORITY_H_
#define PRIORITY_H_

#include "IntWrapper.h"
#include "wx/wx.h"
#include "wx/arrstr.h"

enum PriorityType{MINIMUM, VERY_LOW, LOW, MEDIUM, HIGH, VERY_HIGH, MAXIMUM};

class Priority : public IntWrapper {
public:
	Priority();

	static wxArrayString GetPossiblePriorities();

	virtual wxString GetUserFriendlyStringRepresentation();
	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetBaseTypeClassName();

	virtual ~Priority();
};

#endif /* PRIORITY_H_ */
