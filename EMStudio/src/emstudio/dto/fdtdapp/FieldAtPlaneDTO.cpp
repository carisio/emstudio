/*
 * FieldAtPlaneDTO.cpp
 *
 *  Created on: 13/03/2013
 *      Author: leandrocarisio
 */

#include "FieldAtPlaneDTO.h"

FieldAtPlaneDTO::FieldAtPlaneDTO() {

}

FieldAtPlaneDTO::~FieldAtPlaneDTO() {
}

wxString FieldAtPlaneDTO::GetDTOClassName() {
	return "FieldAtPlaneDTO";
}
int FieldAtPlaneDTO::GetNumberOfSamples() {
	return numberOfSamples;
}
void FieldAtPlaneDTO::SetNumberOfSamples(int samples) {
	numberOfSamples = samples;
}
SelectField FieldAtPlaneDTO::GetField() {
	return field;
}
void FieldAtPlaneDTO::SetField(SelectField f) {
	field = f;
}
Priority FieldAtPlaneDTO::GetPriority() {
	Priority p;
	p.SetValue(MAXIMUM+1);
	return p;
}
