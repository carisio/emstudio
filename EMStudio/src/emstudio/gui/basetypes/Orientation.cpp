/*
 * Orientation.cpp
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#include "Orientation.h"

Orientation::Orientation() {
	IntWrapper::SetValue(X);
}

Orientation::~Orientation() {

}

void Orientation::SetUserFriendlyStringRepresentation(wxString str) {
	if (str == "X") {
		IntWrapper::SetValue(X);
	} else if (str == "Y") {
		IntWrapper::SetValue(Y);
	} else if (str == "Z") {
		IntWrapper::SetValue(Z);
	}
}
wxString Orientation::GetUserFriendlyStringRepresentation() {
	wxString result = "";
	switch(GetValue()) {
	case X:
		result = "X";
		break;
	case Y:
		result = "Y";
		break;
	case Z:
		result = "Z";
		break;
	}
	return result;
}

wxString Orientation::GetBaseTypeClassName() {
	return "Orientation";
}

wxArrayString Orientation::GetPossibleOrientations() {
	wxArrayString result = wxArrayString();
	result.Add("X");
	result.Add("Y");
	result.Add("Z");
	return result;
}
