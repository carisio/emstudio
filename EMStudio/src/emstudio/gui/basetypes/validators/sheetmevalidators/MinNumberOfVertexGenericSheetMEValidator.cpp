/*
 * MinNumberOfVertexGenericSheetMEValidator.cpp
 *
 *  Created on: 19/11/2013
 *      Author: leandrocarisio
 */

#include "MinNumberOfVertexGenericSheetMEValidator.h"

MinNumberOfVertexGenericSheetMEValidator::MinNumberOfVertexGenericSheetMEValidator(int minSize, BaseTypeValidatorSmartPointer parent)
	: BaseTypeValidator(parent) , minSize(minSize) {

}

MinNumberOfVertexGenericSheetMEValidator::~MinNumberOfVertexGenericSheetMEValidator() {

}


wxString MinNumberOfVertexGenericSheetMEValidator::DoGetErrorMessage(BaseType* b, wxString baseTypeName) {
	return baseTypeName.Append(" should have at least ").Append(Converter::IntToFormattedString(minSize)).Append(" vertex.");
}

bool MinNumberOfVertexGenericSheetMEValidator::DoIsValid(BaseType* b) {
	return (static_cast<GenericSheetME*>(b))->GetCoordinates().size() >= minSize;
}
