/*
 * ColourWrapper.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef COLOURWRAPPER_H_
#define COLOURWRAPPER_H_

#include "wx/wx.h"
#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

class ColourWrapper : public BaseType {
private:
	wxColour value;
public:
	ColourWrapper();
	virtual ~ColourWrapper();
	virtual void Copy(BaseType* b);
    wxColour GetValue() const;
    void SetValue(wxColour value);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* COLOURWRAPPER_H_ */
