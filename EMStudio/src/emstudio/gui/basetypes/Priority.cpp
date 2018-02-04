/*
 * Priority.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "Priority.h"

Priority::Priority() {
	IntWrapper::SetValue(MINIMUM);
}

Priority::~Priority() {
}


void Priority::SetUserFriendlyStringRepresentation(wxString str) {
	if (str == "Minimum") {
		IntWrapper::SetValue(MINIMUM);
	} else if (str == "Very low") {
		IntWrapper::SetValue(VERY_LOW);
	} else if (str == "Low") {
		IntWrapper::SetValue(LOW);
	} else if (str == "Medium") {
		IntWrapper::SetValue(MEDIUM);
	} else if (str == "High") {
		IntWrapper::SetValue(HIGH);
	} else if (str == "Very high") {
		IntWrapper::SetValue(VERY_HIGH);
	} else if (str == "Maximum") {
		IntWrapper::SetValue(MAXIMUM);
	}
}
wxString Priority::GetUserFriendlyStringRepresentation() {
	wxString result = "";
	switch(GetValue()) {
	case MINIMUM:
		result = "Minimum";
		break;
	case VERY_LOW:
		result = "Very low";
		break;
	case LOW:
		result = "Low";
		break;
	case MEDIUM:
		result = "Medium";
		break;
	case HIGH:
		result = "High";
		break;
	case VERY_HIGH:
		result = "Very high";
		break;
	case MAXIMUM:
		result = "Maximum";
		break;
	}
	return result;
}

wxString Priority::GetBaseTypeClassName() {
	return "Priority";
}

wxArrayString Priority::GetPossiblePriorities() {
	wxArrayString result = wxArrayString();
	result.Add("Minimum");
	result.Add("Very low");
	result.Add("Low");
	result.Add("Medium");
	result.Add("High");
	result.Add("Very High");
	result.Add("Maximum");
	return result;
}
