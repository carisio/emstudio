/*
 * PropertyNotFoundException.cpp
 *
 *  Created on: 23/11/2011
 *      Author: leandrocarisio
 */

#include "PropertyNotFoundException.h"

PropertyNotFoundException::PropertyNotFoundException(wxString propertyName)
	: propertyName(propertyName) {

}

PropertyNotFoundException::~PropertyNotFoundException() {

}

wxString PropertyNotFoundException::GetPropertyName() {
	return propertyName;
}

