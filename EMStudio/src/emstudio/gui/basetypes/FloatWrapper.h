/*
 * FloatWrapper.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef FLOATWRAPPER_H_
#define FLOATWRAPPER_H_

#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"

class FloatWrapper : public BaseType {
private:
	float value;
public:
	FloatWrapper();
	virtual ~FloatWrapper();
	virtual void Copy(BaseType* b);
	float GetValue() const;
    void SetValue(float value);
    virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

};

#endif /* FLOATWRAPPER_H_ */
