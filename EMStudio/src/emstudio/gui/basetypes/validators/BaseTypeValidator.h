/*
 * BaseTypeValidator.h
 *
 *  Created on: 27/03/2012
 *      Author: leandrocarisio
 */

#ifndef BASETYPEVALIDATOR_H_
#define BASETYPEVALIDATOR_H_

#include "../BaseType.h"
#include "wx/wx.h"

#include <tr1/memory>

class BaseTypeValidator;
typedef std::tr1::shared_ptr<BaseTypeValidator> BaseTypeValidatorSmartPointer;

class BaseTypeValidator {
private:
	BaseTypeValidatorSmartPointer parent;

public:
	BaseTypeValidator(BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());

	BaseTypeValidatorSmartPointer GetParent();
	void SetParent(BaseTypeValidatorSmartPointer p);

	bool IsValid(BaseType* b);
	virtual bool DoIsValid(BaseType* b) = 0;

	wxString GetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName) = 0;

	virtual ~BaseTypeValidator();
};

#endif /* BASETYPEVALIDATOR_H_ */
