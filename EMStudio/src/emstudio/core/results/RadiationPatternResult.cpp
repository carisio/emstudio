/*
 * RadiationPatternResult.cpp
 *
 *  Created on: 18/04/2013
 *      Author: Leandro
 */

#include "RadiationPatternResult.h"
#include "emstudio/util/file/FileManager.h"

RadiationPatternResult::RadiationPatternResult(wxString title, GenericTable data, BoolWrapper canBeInterpretedAsChart, Plane p)
	: TableResult(title, data, canBeInterpretedAsChart) {
	plane.SetValue(p.GetValue());

	AddProperty(Property("Plane", &this->plane));
}

RadiationPatternResult::~RadiationPatternResult() {

}
void RadiationPatternResult::SetPlane(Plane p) {
	plane.Copy(&p);
}
Plane RadiationPatternResult::GetPlane() {
	return plane;
}
wxString RadiationPatternResult::GetResultClassName() {
	return "RadiationPatternResult";
}
ResultSmartPointer RadiationPatternResult::NewResult() {
	return ResultSmartPointer(new RadiationPatternResult);
}
bool RadiationPatternResult::ExportData(wxString fileName) {
	return TableResult::ExportData(fileName);
}
wxString RadiationPatternResult::GetInfoFileContents() {
	wxString moreDescription = TableResult::GetInfoFileContents();
	moreDescription.Append("\n\nPlane: ").Append(plane.GetUserFriendlyStringRepresentation()).Append("\n");

	return moreDescription;
}
