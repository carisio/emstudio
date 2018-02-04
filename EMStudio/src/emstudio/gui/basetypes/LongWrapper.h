/*
 * LongWrapper.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef LONGWRAPPER_H_
#define LONGWRAPPER_H_

#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"

class LongWrapper : public BaseType {
private:
	long value;
public:
	LongWrapper();
	virtual ~LongWrapper();
	virtual void Copy(BaseType* b);
    long GetValue() const;
    void SetValue(long value);
    virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* LONGWRAPPER_H_ */
