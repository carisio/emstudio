/*
 * CircularPECSheet.cpp
 *
 *  Created on: 20/11/2013
 *      Author: leandrocarisio
 */

#include "CircularPECSheet.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/util/constants/Constants.h"
#include <iostream>

CircularPECSheet::CircularPECSheet()
	: ElementsWithFacets(ElementTypeSmartPointer(new Object2DType())) {

	plane.SetValue(XY);
	center.SetXExpression("25");
	center.SetYExpression("25");
	center.SetZExpression("0");
	initialAngle.SetExpression("0");
	finalAngle.SetExpression("360");
	outerRadius.SetExpression("10");
	innerRadius.SetExpression("0");
	showSolid.SetValue(false);
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer invalidPoint3DMEvalidator(new InvalidPoint3DMEValidator);
	BaseTypeValidatorSmartPointer between0and360validator(new MathExpressionInTheIntervalValidator(0,360));
	BaseTypeValidatorSmartPointer greaterThan0validator(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer equalOrGreaterThan0validator(new MathExpressionGreaterThanOrEqualValidator(0));

	AddProperty(Property("Plane", &plane));
	AddProperty(Property("Center", &center, invalidPoint3DMEvalidator));
	AddProperty(Property("Initial angle", &initialAngle, between0and360validator));
	AddProperty(Property("Final angle", &finalAngle, between0and360validator));
	AddProperty(Property("Outer radius", &outerRadius, greaterThan0validator));
	AddProperty(Property("Inner radius", &innerRadius, equalOrGreaterThan0validator));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));
}

CircularPECSheet::~CircularPECSheet() {

}


ElementGUISmartPointer CircularPECSheet::NewElementGUI() {
	return ElementGUISmartPointer(new CircularPECSheet());
}

wxString CircularPECSheet::GetRegisteredName() {
	return "Circular PEC Sheet";
}

wxIcon CircularPECSheet::GetIcon() {
	return UtilResource::GetIcon("circularpecsheet");
}

ElementDTOSmartPointer CircularPECSheet::NewElementDTO() {
	GenericPECSheetsDTO* result = new GenericPECSheetsDTO;
	result->SetGenericSheets(GetGenericSheets());

	return ElementDTOSmartPointer(result);
}


bool CircularPECSheet::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	center.EvalExpressions();
	xmin = center.GetX();
	ymin = center.GetY();
	zmin = center.GetZ();
	xmax = center.GetX();
	ymax = center.GetY();
	zmax = center.GetZ();

	std::vector<GenericSheet> sheets = GetGenericSheets();

	for (size_t i = 0; i < sheets.size(); i++) {
		std::vector<std::pair<double, double> > coord = sheets[i].GetCoordinates();

		for (size_t i = 0; i < coord.size(); i++) {
			if (plane.GetValue() == XY) {
				xmin = coord[i].first < xmin ? coord[i].first : xmin;
				xmax = coord[i].first > xmax ? coord[i].first : xmax;
				ymin = coord[i].second < ymin ? coord[i].second : ymin;
				ymax = coord[i].second > ymax ? coord[i].second : ymax;
			} else if (plane.GetValue() == YZ) {
				ymin = coord[i].first < ymin ? coord[i].first : ymin;
				ymax = coord[i].first > ymax ? coord[i].first : ymax;
				zmin = coord[i].second < zmin ? coord[i].second : zmin;
				zmax = coord[i].second > zmax ? coord[i].second : zmax;
			} else if (plane.GetValue() == XZ) {
				xmin = coord[i].first < xmin ? coord[i].first : xmin;
				xmax = coord[i].first > xmax ? coord[i].first : xmax;
				zmin = coord[i].second < zmin ? coord[i].second : zmin;
				zmax = coord[i].second > zmax ? coord[i].second : zmax;
			}
		}
	}

	return true;
}

void CircularPECSheet::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	DisableLight();
//	SetColor(colour.GetValue());
	SetColor(GetPECColor());

	std::vector<GenericSheet> sheets = GetGenericSheets();

	for (size_t i = 0; i < sheets.size(); i++) {
		DrawPolygon2D(sheets[i], showSolid.IsValue());
	}
//	EnableLight();
}

bool CircularPECSheet::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

	double outerRadius_dbl = outerRadius.ForceEval();
	double innerRadius_dbl = innerRadius.ForceEval();
	double initialAngle_dbl = initialAngle.ForceEval();
	double finalAngle_dbl = finalAngle.ForceEval();

	if (outerRadius_dbl <= innerRadius_dbl) {
		errorMessage.Append("Outer Radius should be greater than Inner Radius.\n");
		valid = false;
	}
	if (finalAngle_dbl <= initialAngle_dbl) {
		errorMessage.Append("Final angle should be greater than Initial angle.\n");
		valid = false;
	}
	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}
/**
 *  Cria várias placas nesse formato. Juntando cada placa, forma-se a estrutura.
 *
 *  ^
 *  |
 *  |          (2)   (p3,p4)                => To finalAngle
 *  | (p5,p6)   / \
 *  |           \  \  (1)
 *  |        (3) \  \
 *  |             \__\  (p1, p2)
 *  |    (p7,p8)   (4)              => From initialAngle
 * -|---------------->
 *  |
 *
 */
std::vector<GenericSheet> CircularPECSheet::GetGenericSheets() {
	center.EvalExpressions();
	double x = center.GetX();
	double y = center.GetY();
	double z = center.GetZ();
	double outerRadius_dbl = outerRadius.ForceEval();
	double innerRadius_dbl = innerRadius.ForceEval();
	double initialAngle_dbl = initialAngle.ForceEval();
	double finalAngle_dbl = finalAngle.ForceEval();

	std::vector<GenericSheet> sheets;
	int segments = 36;
	for (int i = 0; i < segments; i++) {
		GenericSheet gs;
		if (plane.GetValue() == XY) {
			gs.SetCutAtZ(z);
		} else if (plane.GetValue() == YZ) {
			gs.SetCutAtX(x);
		} else if (plane.GetValue() == XZ) {
			gs.SetCutAtY(y);
		}

		std::vector<std::pair<double, double> > coordinates;
		// Cria o trecho #1: pontos (p1, p2) e (p3, p4)
		// Angulo entre o centro e os pontos (p1, p2) e entre o centro e os pontos (p3, p4)
		double initialAngle = initialAngle_dbl + i*(finalAngle_dbl-initialAngle_dbl)/segments;
		double finalAngle   = initialAngle_dbl + (i+1)*(finalAngle_dbl-initialAngle_dbl)/segments;
		// Coordenadas p1, p2 e p3, p4
		double p1 = outerRadius_dbl*cos(initialAngle*PI/180);
		double p2 = outerRadius_dbl*sin(initialAngle*PI/180);
		double p3 = outerRadius_dbl*cos(finalAngle*PI/180);
		double p4 = outerRadius_dbl*sin(finalAngle*PI/180);
		if (plane.GetValue() == XY) {
			p1 += x;
			p2 += y;
			p3 += x;
			p4 += y;
		} else if (plane.GetValue() == YZ) {
			p1 += y;
			p2 += z;
			p3 += y;
			p4 += z;
		} else if (plane.GetValue() == XZ) {
			p1 += x;
			p2 += z;
			p3 += x;
			p4 += z;
		}
		coordinates.push_back(std::pair<double, double>(p1, p2));
		coordinates.push_back(std::pair<double, double>(p3, p4));

		// Cria o trecho #3: pontos (p5, p6) e (p7, p8). Não é necessário criar o trecho 2, pois ele é a ligação dos pontos (p3, p4) e (p5, p6).
		// Coordenadas p1, p2 e p3, p4
		double p5 = innerRadius_dbl*cos(finalAngle*PI/180);
		double p6 = innerRadius_dbl*sin(finalAngle*PI/180);
		double p7 = innerRadius_dbl*cos(initialAngle*PI/180);
		double p8 = innerRadius_dbl*sin(initialAngle*PI/180);
		if (plane.GetValue() == XY) {
			p5 += x;
			p6 += y;
			p7 += x;
			p8 += y;
		} else if (plane.GetValue() == YZ) {
			p5 += x;
			p6 += y;
			p7 += x;
			p8 += y;
		} else if (plane.GetValue() == XZ) {
			p5 += x;
			p6 += y;
			p7 += x;
			p8 += y;
		}
		coordinates.push_back(std::pair<double, double>(p5, p6));
		if (innerRadius_dbl > 0) // Se innerRadius == 0, os 2 pontos são coincidentes
			coordinates.push_back(std::pair<double, double>(p7, p8));

		gs.SetCoordinates(coordinates);

		sheets.push_back(gs);
	}

	cout << "CircularPECSheet::GetGenericSheets => size = " << sheets.size() << endl;
	return sheets;
}
void CircularPECSheet::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + center.GetXExpression() + ") + " + px;
	wxString y = "(" + center.GetYExpression() + ") + " + py;
	wxString z = "(" + center.GetZExpression() + ") + " + pz;
	center.SetXExpression(x);
	center.SetYExpression(y);
	center.SetZExpression(z);
}
