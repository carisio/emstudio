/*
 * GenericSheetSizeValidator.cpp
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetSizeValidator.h"
#include "emstudio/gui/basetypes/GenericSheet.h"
#include "emstudio/util/converters/Converter.h"

GenericSheetSizeValidator::GenericSheetSizeValidator(int minSize, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent), minSize(minSize) {

}

GenericSheetSizeValidator::~GenericSheetSizeValidator() {
}

wxString GenericSheetSizeValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should have at least ").Append(Converter::IntToFormattedString(minSize)).Append(" vertex.");
}

bool GenericSheetSizeValidator::DoIsValid(BaseType* b) {
	return (static_cast<GenericSheet*>(b))->GetCoordinates().size() >= minSize;
}
