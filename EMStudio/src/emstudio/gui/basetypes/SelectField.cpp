/*
 * SelectField.cpp
 *
 *  Created on: 25/04/2013
 *      Author: Leandro
 */

#include "SelectField.h"

SelectField::SelectField()  {
	IntWrapper::SetValue(SelectField::EZ);
}

SelectField::~SelectField() {
}

void SelectField::SetUserFriendlyStringRepresentation(wxString str) {
	int value;

	if (str == "Ex") {
		value = EX;
	} else if (str == "Ey") {
		value = EY;
	} else if (str == "Ez") {
		value = EZ;
	} else if (str == "All E Fields") {
		value = ALL_E_FIELDS;
	} else if (str == "Hx") {
		value = HX;
	} else if (str == "Hy") {
		value = HY;
	} else if (str == "Hz") {
		value = HZ;
	} else if (str == "All H Fields") {
		value = ALL_H_FIELDS;
	} else if (str == "All Fields") {
		value = ALL_FIELDS;
	}
	IntWrapper::SetValue(value);
}
wxString SelectField::GetUserFriendlyStringRepresentation() {
	wxString result = "";

	switch(GetValue()) {
	case EX:
		result = "Ex";
		break;
	case EY:
		result = "Ey";
		break;
	case EZ:
		result = "Ez";
		break;
	case ALL_E_FIELDS:
		result = "All E Fields";
		break;
	case HX:
		result = "Hx";
		break;
	case HY:
		result = "Hy";
		break;
	case HZ:
		result = "Hz";
		break;
	case ALL_H_FIELDS:
		result = "All H Fields";
		break;
	case ALL_FIELDS:
		result = "All Fields";
		break;
	}
	return result;
}

wxString SelectField::GetBaseTypeClassName() {
	return "SelectField";
}

wxArrayString SelectField::GetPossiblePriorities() {
	wxArrayString result = wxArrayString();
	result.Add("Ex");
	result.Add("Ey");
	result.Add("Ez");
	result.Add("Hx");
	result.Add("Hy");
	result.Add("Hz");
	result.Add("All E Fields");
	result.Add("All H Fields");
	result.Add("All Fields");
	return result;
}
