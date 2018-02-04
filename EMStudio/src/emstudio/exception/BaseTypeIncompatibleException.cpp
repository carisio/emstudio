/*
 * BaseTypeIncompatibleExcepation.cpp
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#include "BaseTypeIncompatibleException.h"

BaseTypeIncompatibleException::BaseTypeIncompatibleException(wxString baseTypeName)
	: baseTypeName(baseTypeName) {

}

BaseTypeIncompatibleException::~BaseTypeIncompatibleException() {
}

wxString BaseTypeIncompatibleException::GetBaseTypeName() {
	return baseTypeName;
}
