/*
 * DoubleWrapper.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef DOUBLEWRAPPER_H_
#define DOUBLEWRAPPER_H_

#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"

class DoubleWrapper : public BaseType {
private:
	double value;
public:
	DoubleWrapper();
	virtual ~DoubleWrapper();
	virtual void Copy(BaseType* b);
    double GetValue() const;
    void SetValue(double value);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

};

#endif /* DOUBLEWRAPPER_H_ */
