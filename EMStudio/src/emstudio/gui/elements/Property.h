/*
 * Property.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include "wx/wx.h"
#include "emstudio/gui/basetypes/validators/BaseTypeValidator.h"
#include "emstudio/gui/basetypes/validators/DefaultValidator.h"

class Property {
private:
	wxString name;
	BaseType* baseType;
	wxString baseTypeName;
	BaseTypeValidatorSmartPointer validator;

public:
	Property(wxString name, BaseType* baseType);
	Property(wxString name, BaseType* baseType, BaseTypeValidatorSmartPointer validator);
	virtual ~Property();

	BaseType* GetValue();
	void SetValue(BaseType* baseType);
	wxString GetName() const;
    wxString GetBaseTypeClassName();

    BaseTypeValidatorSmartPointer GetValidator();
    void SetValidator(BaseTypeValidatorSmartPointer validator);

    bool IsValid();
    wxString GetErrorMessage();
};


#endif /* PROPERTY_H_ */
