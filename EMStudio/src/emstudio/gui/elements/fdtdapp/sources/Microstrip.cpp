/*
 * GeneralSource.cpp
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#include "Microstrip.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

Microstrip::Microstrip()
		: ElementsWithFacets(ElementTypeSmartPointer(new SourceType())) {


	lowerBoundary.SetXExpression("0");
	lowerBoundary.SetYExpression("0");
	lowerBoundary.SetZExpression("0");
	upperBoundary.SetXExpression("50");
	upperBoundary.SetYExpression("50");
	upperBoundary.SetZExpression("5");

	linePosition.SetExpression("25");
	lineLength.SetExpression("10");
	lineWidth.SetExpression("5");
//	substrateColor.SetValue(wxColour(0,0,255));
//	pecColor.SetValue(wxColour(255,0,0));
	showSolid.SetValue(true);
	pecUnderSubstrate.SetValue(true);
	visible.SetValue(true);

	linePoints.SetValue(100); sourcePoint.SetValue(90);
	lineImpedance.SetExpression("50");
	initialFrequency.SetExpression("25");
	frequencyStep.SetExpression("5");
	nFrequency.SetExpression("10");

	BaseTypeValidatorSmartPointer validadorInteiroMaiorQueZero(new IntGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorQueZero(new DoubleGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorDoubleMaiorOuIgualAZero(new DoubleGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidExcitation(new InvalidExcitationMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidMicrostripPorts(new InvalidMicrostripXYPortsValidator);

	AddPriorityProperty(HIGH);
	AddProperty(Property("Lower boundary", &lowerBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Upper boundary", &upperBoundary, validadorInvalidPoint3D));
	AddMaterialProperty("Substrate");
	AddProperty(Property("Line position(X)", &linePosition));
	AddProperty(Property("Line length", &lineLength, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Line width", &lineWidth, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("PEC under substrate?", &pecUnderSubstrate));
	AddProperty(Property("Match with PML", &matchWithPML));

	AddProperty(Property("Excitation", &excitation, validadorInvalidExcitation));
//	AddProperty(Property("Line points", &linePoints));
//	AddProperty(Property("Source point", &sourcePoint));
	AddProperty(Property("Ports", &ports, validadorInvalidMicrostripPorts));
	AddProperty(Property("Line impedance", &lineImpedance, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Initial frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &frequencyStep, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorMathExpressionMaiorQueZero));


//	AddProperty(Property("PEC color", &pecColor));
//	AddProperty(Property("Substrate color", &substrateColor));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));

}

Microstrip::~Microstrip() {

}


ElementGUISmartPointer Microstrip::NewElementGUI() {
	return ElementGUISmartPointer(new Microstrip());
}

wxString Microstrip::GetRegisteredName() {
	return "Microstrip";
}

wxIcon Microstrip::GetIcon() {
	return UtilResource::GetIcon("microstrip");
}

ElementDTOSmartPointer Microstrip::NewElementDTO() {
	MicrostripDTO* result = new MicrostripDTO;

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	result->SetX1(lowerBoundary.GetX());
	result->SetY1(lowerBoundary.GetY());
	result->SetZ1(lowerBoundary.GetZ());
	result->SetX2(upperBoundary.GetX());
	result->SetY2(upperBoundary.GetY());
	result->SetZ2(upperBoundary.GetZ());
	result->SetExcitation(excitation.ConvertToExcitation());
	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(frequencyStep.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());
	result->SetLinePositionX(linePosition.ForceEval());
	result->SetLineLength(lineLength.ForceEval());
	result->SetLineWidth(lineWidth.ForceEval());
	result->SetPecUnderSubstrate(pecUnderSubstrate.IsValue());
	result->SetLinePoints(linePoints.GetValue());
	result->SetSourcePoint(sourcePoint.GetValue());
	result->SetLineImpedance(lineImpedance.ForceEval());
	result->SetMatchWithPML(matchWithPML);
	result->SetPorts(ports.ConvertToMicrostripXYPorts());

	return ElementDTOSmartPointer(result);
}

bool Microstrip::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();

	xmin = lowerBoundary.GetX();
	xmax = upperBoundary.GetX();
	ymin = lowerBoundary.GetY();
	ymax = upperBoundary.GetY();
	zmin = lowerBoundary.GetZ();
	zmax = upperBoundary.GetZ();

	return true;
}

void Microstrip::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();

	double xmin = lowerBoundary.GetX();
	double ymin = lowerBoundary.GetY();
	double zmin = lowerBoundary.GetZ();
	double xmax = upperBoundary.GetX();
	double ymax = upperBoundary.GetY();
	double zmax = upperBoundary.GetZ();
	bool fill =  showSolid.IsValue();

	double linePosition_dbl = linePosition.ForceEval();
	double lineWidth_dbl = lineWidth.ForceEval();
	double lineLength_dbl = lineLength.ForceEval();

	SetColor(GetPECColor());
	DrawPlaneZ(linePosition_dbl-lineWidth_dbl/2, ymin, linePosition_dbl+lineWidth_dbl/2, ymin+lineLength_dbl, zmax*1.005, fill);
	DrawPlaneY(linePosition_dbl-lineWidth_dbl/2, zmin, linePosition_dbl+lineWidth_dbl/2, zmax, ymin*0.995, fill);

	if (pecUnderSubstrate.IsValue()) {
		DrawPlaneZ(xmin, ymin, xmax, ymax, zmin, fill);
	}

//	SetColor(substrateColor.GetValue());
	SetColor(GetMaterialColor());
	DrawPlaneX(ymin, zmin, ymax, zmax, xmin, fill);
	DrawPlaneX(ymin, zmin, ymax, zmax, xmax, fill);
	DrawPlaneY(xmin, zmin, xmax, zmax, ymin, fill);
	DrawPlaneY(xmin, zmin, xmax, zmax, ymax, fill);
	DrawPlaneZ(xmin, ymin, xmax, ymax, zmin, fill);
	DrawPlaneZ(xmin, ymin, xmax, ymax, zmax, fill);

	SetColor(GetPECColor());
	vector<pair<double, double> > portsCoordinates = ports.ConvertToMicrostripXYPorts().GetCoordinates();
	for (size_t i = 0; i < portsCoordinates.size(); i++) {
		double x = portsCoordinates[i].first;
		double y = portsCoordinates[i].second;
		DrawLine(x, y, zmin, x, y, zmax, 3);
	}
}

bool Microstrip::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	double linePosition_dbl = linePosition.ForceEval();
	double lineWidth_dbl = lineWidth.ForceEval();
	double lineLength_dbl = lineLength.ForceEval();

	valid = CheckBoundaries(lowerBoundary, upperBoundary, errorMessage, "Lower Boundary", "Upper Boundary");

	if (linePosition_dbl < lowerBoundary.GetX() || linePosition_dbl > upperBoundary.GetX()) {
		errorMessage.Append("Line Position exceeds x boundary.\n");
		valid = false;
	}
	if (lineLength_dbl > (upperBoundary.GetY()-lowerBoundary.GetY())) {
		errorMessage.Append("Line Length exceeds y boundary.\n");
		valid = false;
	}
	if (linePosition_dbl + lineWidth_dbl/2 > upperBoundary.GetX() ||
			linePosition_dbl - lineWidth_dbl/2 < lowerBoundary.GetX()) {
		errorMessage.Append("Line Width exceeds x boundary.\n");
		valid = false;
	}

	/* Se o usuário pediu para casar com a PML, verifica se está na direção correta. Nessa versão a microfita está sempre orientada no plano z */
	if (matchWithPML.IsMatchedWithPML(zNeg) || matchWithPML.IsMatchedWithPML(zPos)) {
		errorMessage.Append("Microstrip is Z-oriented. It can only match the grid at x or y directions.\n");
		valid = false;
	}

	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

vector<Facet> Microstrip::BuildFacets() {
	vector<Facet> facets;

	double xmin = lowerBoundary.GetX();
	double ymin = lowerBoundary.GetY();
	double zmin = lowerBoundary.GetZ();
	double xmax = upperBoundary.GetX();
	double ymax = upperBoundary.GetY();
	double zmax = upperBoundary.GetZ();

	Facet f1;
	f1.Add(Rvector3(xmin, ymin, zmin));
	f1.Add(Rvector3(xmax,ymin,zmin));
	f1.Add(Rvector3(xmax,ymax,zmin));
	f1.Add(Rvector3(xmin,ymax,zmin));
	facets.push_back(f1);

	Facet f2;
	f2.Add(Rvector3(xmin, ymin, zmin));
	f2.Add(Rvector3(xmin,ymax,zmin));
	f2.Add(Rvector3(xmin,ymax,zmax));
	f2.Add(Rvector3(xmin,ymin,zmax));
	facets.push_back(f2);

	Facet f3;
	f3.Add(Rvector3(xmin, ymin, zmin));
	f3.Add(Rvector3(xmax,ymin,zmin));
	f3.Add(Rvector3(xmax,ymin,zmax));
	f3.Add(Rvector3(xmin,ymin,zmax));
	facets.push_back(f3);

	Facet f4;
	f4.Add(Rvector3(xmax, ymax, zmax));
	f4.Add(Rvector3(xmin,ymax,zmax));
	f4.Add(Rvector3(xmin,ymin,zmax));
	f4.Add(Rvector3(xmax,ymin,zmax));
	facets.push_back(f4);

	Facet f5;
	f5.Add(Rvector3(xmax, ymax, zmax));
	f5.Add(Rvector3(xmax,ymin,zmax));
	f5.Add(Rvector3(xmax,ymin,zmin));
	f5.Add(Rvector3(xmax,ymax,zmin));
	facets.push_back(f5);

	Facet f6;
	f6.Add(Rvector3(xmax, ymax, zmax));
	f6.Add(Rvector3(xmin,ymax,zmax));
	f6.Add(Rvector3(xmin,ymax,zmin));
	f6.Add(Rvector3(xmax,ymax,zmin));
	facets.push_back(f6);

	return facets;
}

void Microstrip::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString lp = "(" + linePosition.GetExpression() + ") + " + px;
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
	linePosition.SetExpression(lp);
}
