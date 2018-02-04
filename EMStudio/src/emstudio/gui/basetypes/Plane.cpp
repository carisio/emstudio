/*
 * Plane.cpp
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#include "Plane.h"

Plane::Plane() {
	IntWrapper::SetValue(XY);
}

Plane::~Plane() {

}


void Plane::SetUserFriendlyStringRepresentation(wxString str) {
	if (str == "XY") {
		IntWrapper::SetValue(XY);
	} else if (str == "XZ") {
		IntWrapper::SetValue(XZ);
	} else if (str == "YZ") {
		IntWrapper::SetValue(YZ);
	}
}
wxString Plane::GetUserFriendlyStringRepresentation() {
	wxString result = "";
	switch(GetValue()) {
	case XY:
		result = "XY";
		break;
	case XZ:
		result = "XZ";
		break;
	case YZ:
		result = "YZ";
		break;
	}
	return result;
}

wxString Plane::GetBaseTypeClassName() {
	return "Plane";
}

wxArrayString Plane::GetPossibleOrientations() {
	wxArrayString result = wxArrayString();
	result.Add("XY");
	result.Add("XZ");
	result.Add("YZ");
	return result;
}
