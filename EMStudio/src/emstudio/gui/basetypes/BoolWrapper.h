/*
 * BoolWrapper.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef BOOLWRAPPER_H_
#define BOOLWRAPPER_H_

#include "BaseType.h"

class BoolWrapper : public BaseType {
private:
	bool value;
public:
	BoolWrapper();
	virtual ~BoolWrapper();
    bool IsValue() const;
    void SetValue(bool value);

    virtual void Copy(BaseType* b);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* BOOLWRAPPER_H_ */
