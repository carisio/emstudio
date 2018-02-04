/*
 * FDTD.cpp
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#include "FDTD.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/includes/basetypevalidators.h"

#include <climits>

FDTD::FDTD()
	: ElementsWithFacets(ElementTypeSmartPointer(new MethodType())),
	  xcells(), ycells(), zcells(),
	  timesteps(), /*deltaT(),*/ abc(), gridColour(), gridVisible() {

	lowerBoundary.SetXExpression("0");
	lowerBoundary.SetYExpression("0");
	lowerBoundary.SetZExpression("0");
	upperBoundary.SetXExpression("50");
	upperBoundary.SetYExpression("50");
	upperBoundary.SetZExpression("50");
	xcells.SetExpression("50"); ycells.SetExpression("50"); zcells.SetExpression("50");
	timesteps.SetExpression("100");
//	deltaT.SetValue(1000);
	gridColour.SetValue(wxColour(150, 150, 150));
	gridVisible.SetValue(true);
//	smoothMesh.SetValue(true);

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);


	AddProperty(Property("Lower Boundary", &lowerBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Upper Boundary", &upperBoundary, validadorInvalidPoint3D));
	AddProperty(Property("Number of Cells (X)", &xcells, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Number of Cells (Y)", &ycells, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Number of Cells (Z)", &zcells, validadorMathExpressionMaiorQueZero));
//	AddProperty(Property("Smooth Mesh?", &smoothMesh));
	AddProperty(Property("Time steps", &timesteps, validadorMathExpressionMaiorQueZero));
//	AddProperty(Property("Delta T", &deltaT));
	AddProperty(Property("ABC", &abc));
	AddProperty(Property("Grid colour", &gridColour));
	AddProperty(Property("Grid visible?", &gridVisible));
}

FDTD::~FDTD() {

}

ElementGUISmartPointer FDTD::NewElementGUI() {
	return ElementGUISmartPointer(new FDTD());
}

wxString FDTD::GetRegisteredName() {
	return "FDTD";
}

wxIcon FDTD::GetIcon() {
	return UtilResource::GetIcon("fdtd");
}

ElementDTOSmartPointer FDTD::NewElementDTO() {
	FDTDDTO* result = new FDTDDTO;
	result->SetName(GetUserDefinedName());

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	result->SetXmin(lowerBoundary.GetX());
	result->SetYmin(lowerBoundary.GetY());
	result->SetZmin(lowerBoundary.GetZ());
	result->SetXmax(upperBoundary.GetX());
	result->SetYmax(upperBoundary.GetY());
	result->SetZmax(upperBoundary.GetZ());
	result->SetXcells(xcells.ForceEval());
	result->SetYcells(ycells.ForceEval());
	result->SetZcells(zcells.ForceEval());
	result->SetTimesteps(timesteps.ForceEval());
	result->SetSmoothMesh(true);
//	result->SetSmoothMesh(smoothMesh.IsValue());
//	result->SetDeltaT(deltaT.GetValue());
	result->SetABC(abc);
	return ElementDTOSmartPointer(result);
}

bool FDTD::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (! gridVisible.IsValue()) {
		return false;
	}

	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	xmin = lowerBoundary.GetX();
	ymin = lowerBoundary.GetY();
	zmin = lowerBoundary.GetZ();
	xmax = upperBoundary.GetX();
	ymax = upperBoundary.GetY();
	zmax = upperBoundary.GetZ();

	return true;
}
void FDTD::Draw(OpenGLStateMachine* opengl) {
	if (!gridVisible.IsValue())
	  return;

//	DisableLight();
	// necessário desabiliar a iluminação para desenhar as linhas corretamente
	glDisable(GL_LIGHTING);
	SetColor(gridColour.GetValue());

	/* Necessário para chamar o eval. */
	lowerBoundary.EvalExpressions();
	upperBoundary.EvalExpressions();
	double xmin = lowerBoundary.GetX();
	double ymin = lowerBoundary.GetY();
	double zmin = lowerBoundary.GetZ();
	double xmax = upperBoundary.GetX();
	double ymax = upperBoundary.GetY();
	double zmax = upperBoundary.GetZ();

	int i_xcell = xcells.ForceEval();
	int i_ycell = ycells.ForceEval();
	int i_zcell = zcells.ForceEval();

	float lineWidth = 1.0f;
	for (int i = 0; i <= i_xcell; i++) {
		double x = (xmax-xmin)/i_xcell;
		/* Plano XY */
		DrawLine(xmin + i*x, ymin, zmin,
				xmin+ i*x, ymax, zmin, lineWidth);
		/* Plano XZ */
		DrawLine(xmin+ i*x, ymin, zmin,
				xmin+ i*x, ymin, zmax, lineWidth);
	}
	for (int j = 0; j <= i_ycell; j++) {
		double y = (ymax-ymin)/i_ycell;
		/* Plano XY */
		DrawLine(xmin, ymin+ j*y, zmin,
				xmax, ymin+ j*y, zmin, lineWidth);
		/* Plano YZ */
		DrawLine(xmin, ymin+ j*y, zmin,
				xmin, ymin+ j*y, zmax, lineWidth);
	}
	for (int k = 0; k <= i_zcell; k++) {
		double z = (zmax-zmin)/i_zcell;
		/* Plano YZ */
		DrawLine(xmin, ymin, zmin+ k*z,
				xmin, ymax, zmin+ k*z, lineWidth);
		/* Plano XZ */
		DrawLine(xmin, ymin, zmin+ k*z,
				xmax, ymin, zmin+ k*z, lineWidth);
	}
//  Não funciona. Tem que habilitar o blend, mas parece que tem que desenhar na ordem certa. Ainda não sei como faz isso.
//	Ver comentários no OpenGLStateMachine
//	SetColor(wxColour(gridColour.GetValue().Red()*2, gridColour.GetValue().Green()*2, gridColour.GetValue().Blue()*2));
//	if (abc.IsPEC(xNeg)) {
//		DrawPlaneX(ymin, zmin, ymax, zmax, xmin, true);
//	}
//	if (abc.IsPEC(yNeg)) {
//		DrawPlaneY(xmin, zmin, xmax, zmax, ymin, true);
//	}
//	if (abc.IsPEC(zNeg)) {
//		DrawPlaneZ(xmin, ymin, xmax, ymax, zmin, true);
//	}
//	if (abc.IsPEC(xPos)) {
//		DrawPlaneX(ymin, zmin, ymax, zmax, xmax, true);
//	}
//	if (abc.IsPEC(yPos)) {
//		DrawPlaneY(xmin, zmin, xmax, zmax, ymax, true);
//	}
//	if (abc.IsPEC(zPos)) {
//		DrawPlaneZ(xmin, ymin, xmax, ymax, zmax, true);
//	}
//	EnableLight();
	glEnable(GL_LIGHTING);
}

bool FDTD::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;

	valid = CheckBoundaries(lowerBoundary, upperBoundary, errorMessage, "Lower Boundary", "Upper Boundary");

	int npml = abc.GetNpml();
	if (npml <= 0) {
		errorMessage.Append("Npml should be greater than 0.\n");
		valid = false;
	}
	/* Verifica o tamanho do grid.
	 * A geração de matrizes no programa está sendo feita usando a biblioteca TNT.
	 * Um vetor nessa biblioteca é feito usando índices inteiros. Então o grid não pode ter mais
	 * células do que o máximo valor de um inteiro
	 */
	int i_xcell = xcells.ForceEval();
	int i_ycell = ycells.ForceEval();
	int i_zcell = zcells.ForceEval();

	int maxInt = (std::numeric_limits<int>::max());
	double xCellsComPML = i_xcell; xCellsComPML += (2*npml);
	double yCellsComPML = i_ycell; yCellsComPML += (2*npml);
	double zCellsComPML = i_zcell; zCellsComPML += (2*npml);
	double gridSize = xCellsComPML * yCellsComPML * zCellsComPML;
	if (gridSize > maxInt) {
		errorMessage.Append("Grid should be less than ").Append(Converter::IntToFormattedString(maxInt)).Append(".\n");
		valid = false;
	}

	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

void FDTD::DoMove(Point3DME p) {
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
