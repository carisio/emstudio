/*
 * GenericSheetSizeValidator.h
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETSIZEVALIDATOR_H_
#define GENERICSHEETSIZEVALIDATOR_H_

#include "../BaseTypeValidator.h"

class GenericSheetSizeValidator : public BaseTypeValidator {
private:
	int minSize;
public:
	GenericSheetSizeValidator(int minSize, BaseTypeValidatorSmartPointer parent = BaseTypeValidatorSmartPointer());
	virtual ~GenericSheetSizeValidator();

	virtual wxString DoGetErrorMessage(BaseType* b, wxString baseTypeName);
	virtual bool DoIsValid(BaseType* b);
};

#endif /* GENERICSHEETSIZEVALIDATOR_H_ */
