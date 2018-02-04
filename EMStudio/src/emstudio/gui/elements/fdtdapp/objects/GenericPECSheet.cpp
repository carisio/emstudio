/*
 * GenericPECSheet.cpp
 *
 *  Created on: 16/04/2013
 *      Author: Leandro
 */

#include "GenericPECSheet.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"
#include <vector>

GenericPECSheet::GenericPECSheet() : ElementsWithFacets(ElementTypeSmartPointer(new Object2DType())), sheet() {

//	colour.SetValue(wxColour(0,0,255));
	showSolid.SetValue(false);
	visible.SetValue(true);
	sheet.SetCutAtZ("25");
	std::vector<std::pair<wxString, wxString> > coordinates;
	coordinates.push_back(std::pair<wxString, wxString>("10", "10"));
	coordinates.push_back(std::pair<wxString, wxString>("25", "40"));
	coordinates.push_back(std::pair<wxString, wxString>("40", "40"));
	sheet.SetCoordinates(coordinates);

	BaseTypeValidatorSmartPointer validatorInvalidGenericSheetME(new InvalidGenericSheetMEValidator);
	BaseTypeValidatorSmartPointer validatorMoreThan3Vertex(new MinNumberOfVertexGenericSheetMEValidator(3, validatorInvalidGenericSheetME));

	AddProperty(Property("Sheet", &sheet, validatorMoreThan3Vertex));
//	AddProperty(Property("Match with PML", &matchWithPML));
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));

}

GenericPECSheet::~GenericPECSheet() {
}

ElementGUISmartPointer GenericPECSheet::NewElementGUI() {
	return ElementGUISmartPointer(new GenericPECSheet());
}

wxString GenericPECSheet::GetRegisteredName() {
	return "Generic PEC Sheet";
}

wxIcon GenericPECSheet::GetIcon() {
	return UtilResource::GetIcon("genericpecsheet");
}

ElementDTOSmartPointer GenericPECSheet::NewElementDTO() {
	GenericPECSheetDTO* result = new GenericPECSheetDTO;

	result->SetGenericSheet(sheet.ConvertToGenericSheet(true));
//	result->SetMatchWithPML(matchWithPML);

	return ElementDTOSmartPointer(result);
}


bool GenericPECSheet::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	std::vector<std::pair<double, double> > coordinates = sheet.ConvertToGenericSheet(IsChanged()).GetCoordinates();
	SetChanged(false);
	double coord1Min, coord1Max, coord2Min, coord2Max;
	coord1Min = 1e30; coord1Max = -1e30; coord2Min = 1e30; coord2Max = -1e30;

	for (size_t i = 0; i < coordinates.size(); i++) {
		pair<double, double> p = coordinates[i];
		if (p.first < coord1Min) {
			coord1Min = p.first;
		}
		if (p.first > coord1Max) {
			coord1Max = p.first;
		}
		if (p.second < coord2Min) {
			coord2Min = p.second;
		}
		if (p.second > coord2Max) {
			coord2Max = p.second;
		}
	}

	if (sheet.IsCutAtZ()) {
		zmin = sheet.GetCutAt();
		zmax = sheet.GetCutAt();
		xmin = coord1Min;
		xmax = coord1Max;
		ymin = coord2Min;
		ymax = coord2Max;
	} else if (sheet.IsCutAtX()) {
		xmin = sheet.GetCutAt();
		xmax = sheet.GetCutAt();
		ymin = coord1Min;
		ymax = coord1Max;
		zmin = coord2Min;
		zmax = coord2Max;
	} else if (sheet.IsCutAtY()) {
		ymin = sheet.GetCutAt();
		ymax = sheet.GetCutAt();
		xmin = coord1Min;
		xmax = coord1Max;
		zmin = coord2Min;
		zmax = coord2Max;
	}

	return true;
}

void GenericPECSheet::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
//	SetColor(colour.GetValue());
	SetColor(GetPECColor());

	DrawPolygon2D(sheet.ConvertToGenericSheet(IsChanged()), showSolid.IsValue());
	SetChanged(false);
//	EnableLight();
}

bool GenericPECSheet::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;

	/* Se a PEC foi casada com a PML, verifica se a orientação da PEC está condizente com as direções selecionadas para casamento */
//	if (sheet.IsCutAtX()) {
//		if (matchWithPML.IsMatchedWithPML(xNeg) || matchWithPML.IsMatchedWithPML(xPos)) {
//			errorMessage.Append("Sheet is X-oriented. It can only match the grid at y or z directions.\n");
//			valid = false;
//		}
//	}
//	if (sheet.IsCutAtY()) {
//		if (matchWithPML.IsMatchedWithPML(yNeg) || matchWithPML.IsMatchedWithPML(yPos)) {
//			errorMessage.Append("Sheet is Y-oriented. It can only match the grid at x or z directions.\n");
//			valid = false;
//		}
//	}
//	if (sheet.IsCutAtZ()) {
//		if (matchWithPML.IsMatchedWithPML(zNeg) || matchWithPML.IsMatchedWithPML(zPos)) {
//			errorMessage.Append("Sheet is Z-oriented. It can only match the grid at x or y directions.\n");
//			valid = false;
//		}
//	}
//	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}
void GenericPECSheet::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();

	std::vector<std::pair<wxString, wxString> > coordinates = sheet.GetCoordinates();
	std::vector<std::pair<wxString, wxString> > newCoordinates;

	wxString coord1, coord2;
	if (sheet.IsCutAtX()) {
		coord1 = py;
		coord2 = pz;
		wxString cutAt = "(" + sheet.GetCutAtExpression() + ") + " + px;
		sheet.SetCutAtX(cutAt);
	} else if (sheet.IsCutAtY()) {
		coord1 = px;
		coord2 = pz;
		wxString cutAt = "(" + sheet.GetCutAtExpression() + ") + " + py;
		sheet.SetCutAtY(cutAt);
	} else if (sheet.IsCutAtZ()) {
		coord1 = px;
		coord2 = py;
		wxString cutAt = "(" + sheet.GetCutAtExpression() + ") + " + pz;
		sheet.SetCutAtZ(cutAt);
	}
	for (size_t i = 0; i < coordinates.size(); i++) {
		wxString newCoord1 = "(" + coordinates[i].first  + ") + " + coord1;
		wxString newCoord2 = "(" + coordinates[i].second + ") + " + coord2;
		newCoordinates.push_back(std::pair<wxString, wxString>(newCoord1, newCoord2));
	}
	sheet.SetCoordinates(newCoordinates);
}
