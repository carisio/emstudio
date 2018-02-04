/*
 * PropertyNotFoundException.h
 *
 *  Created on: 23/11/2011
 *      Author: leandrocarisio
 */

#ifndef PROPERTYNOTFOUNDEXCEPTION_H_
#define PROPERTYNOTFOUNDEXCEPTION_H_

#include "wx/wx.h"

class PropertyNotFoundException {
private:
	wxString propertyName;
public:
	PropertyNotFoundException(wxString propertyName);
	virtual ~PropertyNotFoundException();

	wxString GetPropertyName();
};

#endif /* PROPERTYNOTFOUNDEXCEPTION_H_ */
