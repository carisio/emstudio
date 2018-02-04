/*
 * StringWrapper.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef STRINGWRAPPER_H_
#define STRINGWRAPPER_H_

#include "wx/wx.h"
#include "BaseType.h"

class StringWrapper : public BaseType {
private:
	wxString value;
public:
	StringWrapper();
	virtual ~StringWrapper();
	virtual void Copy(BaseType* b);
    wxString GetValue() const;
    void SetValue(wxString s);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();

    virtual void DoWrite(OutputBuffer& buffer);
    virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* STRINGWRAPPER_H_ */
