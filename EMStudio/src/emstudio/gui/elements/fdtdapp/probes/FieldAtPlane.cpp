/*
 * FieldAtPlane.cpp
 *
 *  Created on: 13/03/2013
 *      Author: leandrocarisio
 */

#include "FieldAtPlane.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

FieldAtPlane::FieldAtPlane() : ElementsWithFacets(ElementTypeSmartPointer(new ProbeType())) {

	colour.SetValue(wxColour(0,0,255));
	visible.SetValue(true);
	dimensions.SetCutAtZ("25");
	dimensions.SetX0Expression("10");
	dimensions.SetY0Expression("10");
	dimensions.SetX1Expression("40");
	dimensions.SetY1Expression("40");
	snapshootNumber.SetExpression("100");

	BaseTypeValidatorSmartPointer validadorInteiroNoIntervalo(new MathExpressionInTheIntervalValidator(2,100));
	BaseTypeValidatorSmartPointer validadorInvalidSheet(new InvalidSheetMEValidator);

	AddProperty(Property("Field", &selectedField));
	AddProperty(Property("Boundaries", &dimensions, validadorInvalidSheet));
	AddProperty(Property("Samples", &snapshootNumber, validadorInteiroNoIntervalo));
	AddProperty(Property("Color", &colour));
	AddProperty(Property("Visible?", &visible));
}

FieldAtPlane::~FieldAtPlane() {

}

ElementGUISmartPointer FieldAtPlane::NewElementGUI() {
	return ElementGUISmartPointer(new FieldAtPlane());
}

wxString FieldAtPlane::GetRegisteredName() {
	return "Field at Plane";
}

wxIcon FieldAtPlane::GetIcon() {
	// todo: criar um ícone para o field at plane. por enquanto está sendo usado o mesmo do field at path
	return UtilResource::GetIcon("fieldatplane");
}

ElementDTOSmartPointer FieldAtPlane::NewElementDTO() {
	FieldAtPlaneDTO* result = new FieldAtPlaneDTO;

	dimensions.EvalExpressions();

	double xmin = dimensions.GetX0();
	double ymin = dimensions.GetY0();
	double zmin = dimensions.GetZ0();
	double xmax = dimensions.GetX1();
	double ymax = dimensions.GetY1();
	double zmax = dimensions.GetZ1();

	if (dimensions.IsCutAtZ()) {
		zmin = dimensions.GetCutAt();
		zmax = dimensions.GetCutAt();
	} else if (dimensions.IsCutAtX()) {
		xmin = dimensions.GetCutAt();
		xmax = dimensions.GetCutAt();
	} else if (dimensions.IsCutAtY()) {
		ymin = dimensions.GetCutAt();
		ymax = dimensions.GetCutAt();
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
	result->SetCutAt(dimensions.GetCutAt());
	result->SetCutAtX(dimensions.IsCutAtX());
	result->SetCutAtY(dimensions.IsCutAtY());
	result->SetCutAtZ(dimensions.IsCutAtZ());

	result->SetNumberOfSamples(snapshootNumber.ForceEval());
	result->SetField(selectedField);

	return ElementDTOSmartPointer(result);
}

bool FieldAtPlane::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	xmin = dimensions.GetX0();
	ymin = dimensions.GetY0();
	zmin = dimensions.GetZ0();
	xmax = dimensions.GetX1();
	ymax = dimensions.GetY1();
	zmax = dimensions.GetZ1();
	if (dimensions.IsCutAtZ()) {
		zmin = dimensions.GetCutAt();
		zmax = dimensions.GetCutAt();
	} else if (dimensions.IsCutAtX()) {
		xmin = dimensions.GetCutAt();
		xmax = dimensions.GetCutAt();
	} else if (dimensions.IsCutAtY()) {
		ymin = dimensions.GetCutAt();
		ymax = dimensions.GetCutAt();
	}

	SortMinMax(xmin, xmax);
	SortMinMax(ymin, ymax);
	SortMinMax(zmin, zmax);
	return true;
}

void FieldAtPlane::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
	SetColor(colour.GetValue());
	dimensions.EvalExpressions();

	double xmin, ymin, zmin, xmax, ymax, zmax;
	xmin = dimensions.GetX0();
	ymin = dimensions.GetY0();
	zmin = dimensions.GetZ0();
	xmax = dimensions.GetX1();
	ymax = dimensions.GetY1();
	zmax = dimensions.GetZ1();
	if (dimensions.IsCutAtZ()) {
		DrawPlaneZ(xmin, ymin, xmax, ymax, dimensions.GetCutAt(), false);
	} else if (dimensions.IsCutAtX()) {
		DrawPlaneX(ymin, zmin, ymax, zmax, dimensions.GetCutAt(), false);
	} else if (dimensions.IsCutAtY()) {
		DrawPlaneY(xmin, zmin, xmax, zmax, dimensions.GetCutAt(), false);
	}
//	EnableLight();
}

void FieldAtPlane::SortMinMax(double& min, double& max) {
	if (min > max) {
		double aux = min;
		min = max;
		max = aux;
	}
}
void FieldAtPlane::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString xl = "(" + dimensions.GetX0Expression() + ") + " + px;
	wxString yl = "(" + dimensions.GetY0Expression() + ") + " + py;
	wxString zl = "(" + dimensions.GetZ0Expression() + ") + " + pz;
	wxString xu = "(" + dimensions.GetX1Expression() + ") + " + px;
	wxString yu = "(" + dimensions.GetY1Expression() + ") + " + py;
	wxString zu = "(" + dimensions.GetZ1Expression() + ") + " + pz;
	dimensions.SetX0Expression(xl);
	dimensions.SetY0Expression(yl);
	dimensions.SetZ0Expression(zl);
	dimensions.SetX1Expression(xu);
	dimensions.SetY1Expression(yu);
	dimensions.SetZ1Expression(zu);
}
