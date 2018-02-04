/*
 * IntWrapper.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef INTWRAPPER_H_
#define INTWRAPPER_H_

#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"

class IntWrapper : public BaseType {
	int value;
public:
	IntWrapper();
	virtual ~IntWrapper();
	virtual void Copy(BaseType* b);
    int GetValue() const;
    void SetValue(int value);
    virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* INTWRAPPER_H_ */
