/*
 * PlaneWave.cpp
 *
 *  Created on: 25/08/2011
 *      Author: Leandro
 */

#include "PlaneWave.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

PlaneWave::PlaneWave()
	: ElementsWithFacets(ElementTypeSmartPointer(new SourceType())) ,
	  excitation(), /*hardSource(), */visible(), colour() {

	direction.SetThetaExpression("90");
	direction.SetPhiExpression("270");
	direction.SetPsiExpression("90");
	//	hardSource.SetValue(false);
	colour.SetValue(wxColour(255,0,0));
	visible.SetValue(true);
	lowerBoundary.SetXExpression("10"); lowerBoundary.SetYExpression("10"); lowerBoundary.SetZExpression("10");
	upperBoundary.SetXExpression("40"); upperBoundary.SetYExpression("40"); upperBoundary.SetZExpression("40");

	SetPriority(HIGH);

//	BaseTypeValidatorSmartPointer validadorDeIntervalo0a360(new DoubleInTheIntervalValidator(0, 360));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidExcitation(new InvalidExcitationMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidDirectionPlaneWave(new InvalidDirectionPlaneWaveMEValidator);

	AddProperty(Property("Lower Boundary", &lowerBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Upper Boundary", &upperBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Direction", &direction, validadorInvalidDirectionPlaneWave));
	AddProperty(Property("Excitation", &excitation, validadorInvalidExcitation));
//	AddProperty(Property("Hard source?", &hardSource));
	AddProperty(Property("Color", &colour));
	AddProperty(Property("Visible?", &visible));
}

PlaneWave::~PlaneWave() {

}

ElementGUISmartPointer PlaneWave::NewElementGUI() {
	return ElementGUISmartPointer(new PlaneWave());
}

wxString PlaneWave::GetRegisteredName() {
	return "Plane Wave";
}

wxIcon PlaneWave::GetIcon() {
	return UtilResource::GetIcon("planewave");
}

ElementDTOSmartPointer PlaneWave::NewElementDTO() {
	PlaneWaveDTO* result = new PlaneWaveDTO;

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	direction.EvalExpressions();
	result->SetXmin(lowerBoundary.GetX());
	result->SetXmax(upperBoundary.GetX());
	result->SetYmin(lowerBoundary.GetY());
	result->SetYmax(upperBoundary.GetY());
	result->SetZmin(lowerBoundary.GetZ());
	result->SetZmax(upperBoundary.GetZ());
	result->SetTheta(direction.GetTheta());
	result->SetPhi(direction.GetPhi());
	result->SetPsi(direction.GetPsi());
	result->SetExcitation(excitation.ConvertToExcitation());
//	result->SetHardSource(hardSource.IsValue());

	return ElementDTOSmartPointer(result);
}

bool PlaneWave::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;
	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	xmin = this->lowerBoundary.GetX();
	ymin = this->lowerBoundary.GetY();
	zmin = this->lowerBoundary.GetZ();
	xmax = this->upperBoundary.GetX();
	ymax = this->upperBoundary.GetY();
	zmax = this->upperBoundary.GetZ();

	return true;
}

void PlaneWave::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
	SetColor(colour.GetValue());

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();

	DrawPlaneX(lowerBoundary.GetY(), lowerBoundary.GetZ(), upperBoundary.GetY(), upperBoundary.GetZ(), lowerBoundary.GetX());
	DrawPlaneX(lowerBoundary.GetY(), lowerBoundary.GetZ(), upperBoundary.GetY(), upperBoundary.GetZ(), upperBoundary.GetX());

	DrawPlaneY(lowerBoundary.GetX(), lowerBoundary.GetZ(), upperBoundary.GetX(), upperBoundary.GetZ(), lowerBoundary.GetY());
	DrawPlaneY(lowerBoundary.GetX(), lowerBoundary.GetZ(), upperBoundary.GetX(), upperBoundary.GetZ(), upperBoundary.GetY());

	DrawPlaneZ(lowerBoundary.GetX(), lowerBoundary.GetY(), upperBoundary.GetX(), upperBoundary.GetY(), lowerBoundary.GetZ());
	DrawPlaneZ(lowerBoundary.GetX(), lowerBoundary.GetY(), upperBoundary.GetX(), upperBoundary.GetY(), upperBoundary.GetZ());
//	EnableLight();
}

bool PlaneWave::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;

	valid = CheckBoundaries(lowerBoundary, upperBoundary, errorMessage, "Lower Boundary", "Upper Boundary");

	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

void PlaneWave::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString xl = "(" + lowerBoundary.GetXExpression() + ") + " + px;
	wxString yl = "(" + lowerBoundary.GetYExpression() + ") + " + py;
	wxString zl = "(" + lowerBoundary.GetZExpression() + ") + " + pz;
	wxString xu = "(" + upperBoundary.GetXExpression() + ") + " + px;
	wxString yu = "(" + upperBoundary.GetYExpression() + ") + " + py;
	wxString zu = "(" + upperBoundary.GetZExpression() + ") + " + pz;
	lowerBoundary.SetXExpression(xl);
	lowerBoundary.SetYExpression(yl);
	lowerBoundary.SetZExpression(zl);
	upperBoundary.SetXExpression(xu);
	upperBoundary.SetYExpression(yu);
	upperBoundary.SetZExpression(zu);
}
