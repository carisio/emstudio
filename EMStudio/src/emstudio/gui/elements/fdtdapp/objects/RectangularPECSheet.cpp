/*
 * RectangularSheet.cpp
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#include "RectangularPECSheet.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

RectangularPECSheet::RectangularPECSheet()
	: ElementsWithFacets(ElementTypeSmartPointer(new Object2DType())), sheet() {

//	colour.SetValue(wxColour(0,0,255));
//	solidColour.SetValue(wxColour(0,255,0));
	showSolid.SetValue(true);
	visible.SetValue(true);
	sheet.SetCutAtZ("25");
	sheet.SetX0Expression("10");
	sheet.SetY0Expression("10");
	sheet.SetX1Expression("40");
	sheet.SetY1Expression("40");

	BaseTypeValidatorSmartPointer validadorInvalidSheet(new InvalidSheetMEValidator);

	AddProperty(Property("Dimensions", &sheet, validadorInvalidSheet));
	AddProperty(Property("Match with PML", &matchWithPML));
//	AddProperty(Property("Material", &material));
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));
}

RectangularPECSheet::~RectangularPECSheet() {

}


ElementGUISmartPointer RectangularPECSheet::NewElementGUI() {
	return ElementGUISmartPointer(new RectangularPECSheet());
}

wxString RectangularPECSheet::GetRegisteredName() {
	return "Rectangular PEC Sheet";
}

wxIcon RectangularPECSheet::GetIcon() {
	return UtilResource::GetIcon("rectangularpecsheet");
}

ElementDTOSmartPointer RectangularPECSheet::NewElementDTO() {
	RectangularPECSheetDTO* result = new RectangularPECSheetDTO;

	sheet.EvalExpressions();

	double xmin = sheet.GetX0();
	double ymin = sheet.GetY0();
	double zmin = sheet.GetZ0();
	double xmax = sheet.GetX1();
	double ymax = sheet.GetY1();
	double zmax = sheet.GetZ1();

	if (sheet.IsCutAtZ()) {
		zmin = sheet.GetCutAt();
		zmax = sheet.GetCutAt();
	} else if (sheet.IsCutAtX()) {
		xmin = sheet.GetCutAt();
		xmax = sheet.GetCutAt();
	} else if (sheet.IsCutAtY()) {
		ymin = sheet.GetCutAt();
		ymax = sheet.GetCutAt();
	}

	SortMinMax(xmin, xmax);
	SortMinMax(ymin, ymax);
	SortMinMax(zmin, zmax);

	result->SetX0(xmin);
	result->SetY0(ymin);
	result->SetZ0(zmin);
	result->SetX1(xmax);
	result->SetY1(ymax);
	result->SetZ1(zmax);
	result->SetCutAt(sheet.GetCutAt());
	result->SetCutAtX(sheet.IsCutAtX());
	result->SetCutAtY(sheet.IsCutAtY());
	result->SetCutAtZ(sheet.IsCutAtZ());

	result->SetMatchWithPML(matchWithPML);

	return ElementDTOSmartPointer(result);
}


bool RectangularPECSheet::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	xmin = sheet.GetX0();
	ymin = sheet.GetY0();
	zmin = sheet.GetZ0();
	xmax = sheet.GetX1();
	ymax = sheet.GetY1();
	zmax = sheet.GetZ1();
	if (sheet.IsCutAtZ()) {
		zmin = sheet.GetCutAt();
		zmax = sheet.GetCutAt();
	} else if (sheet.IsCutAtX()) {
		xmin = sheet.GetCutAt();
		xmax = sheet.GetCutAt();
	} else if (sheet.IsCutAtY()) {
		ymin = sheet.GetCutAt();
		ymax = sheet.GetCutAt();
	}

	SortMinMax(xmin, xmax);
	SortMinMax(ymin, ymax);
	SortMinMax(zmin, zmax);
	return true;
}

void RectangularPECSheet::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
//	SetColor(colour.GetValue());
	SetColor(GetPECColor());
	sheet.EvalExpressions();

	double xmin, ymin, zmin, xmax, ymax, zmax;
	xmin = sheet.GetX0();
	ymin = sheet.GetY0();
	zmin = sheet.GetZ0();
	xmax = sheet.GetX1();
	ymax = sheet.GetY1();
	zmax = sheet.GetZ1();
	if (sheet.IsCutAtZ()) {
		DrawPlaneZ(xmin, ymin, xmax, ymax, sheet.GetCutAt(), showSolid.IsValue());
	} else if (sheet.IsCutAtX()) {
		DrawPlaneX(ymin, zmin, ymax, zmax, sheet.GetCutAt(), showSolid.IsValue());
	} else if (sheet.IsCutAtY()) {
		DrawPlaneY(xmin, zmin, xmax, zmax, sheet.GetCutAt(), showSolid.IsValue());
	}
//	EnableLight();
}

void RectangularPECSheet::SortMinMax(double& min, double& max) {
	if (min > max) {
		double aux = min;
		min = max;
		max = aux;
	}
}

bool RectangularPECSheet::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	/* Se a PEC foi casada com a PML, verifica se a orientação da PEC está condizente com as direções selecionadas para casamento */
	if (sheet.IsCutAtX()) {
		if (matchWithPML.IsMatchedWithPML(xNeg) || matchWithPML.IsMatchedWithPML(xPos)) {
			errorMessage.Append("Sheet is X-oriented. It can only match the grid at y or z directions.\n");
			valid = false;
		}
	}
	if (sheet.IsCutAtY()) {
		if (matchWithPML.IsMatchedWithPML(yNeg) || matchWithPML.IsMatchedWithPML(yPos)) {
			errorMessage.Append("Sheet is Y-oriented. It can only match the grid at x or z directions.\n");
			valid = false;
		}
	}
	if (sheet.IsCutAtZ()) {
		if (matchWithPML.IsMatchedWithPML(zNeg) || matchWithPML.IsMatchedWithPML(zPos)) {
			errorMessage.Append("Sheet is Z-oriented. It can only match the grid at x or y directions.\n");
			valid = false;
		}
	}
	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

void RectangularPECSheet::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString xl = "(" + sheet.GetX0Expression() + ") + " + px;
	wxString yl = "(" + sheet.GetY0Expression() + ") + " + py;
	wxString zl = "(" + sheet.GetZ0Expression() + ") + " + pz;
	wxString xu = "(" + sheet.GetX1Expression() + ") + " + px;
	wxString yu = "(" + sheet.GetY1Expression() + ") + " + py;
	wxString zu = "(" + sheet.GetZ1Expression() + ") + " + pz;
	sheet.SetX0Expression(xl);
	sheet.SetY0Expression(yl);
	sheet.SetZ0Expression(zl);
	sheet.SetX1Expression(xu);
	sheet.SetY1Expression(yu);
	sheet.SetZ1Expression(zu);
}
