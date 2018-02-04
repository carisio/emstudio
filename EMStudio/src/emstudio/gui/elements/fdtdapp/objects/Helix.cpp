/*
 * Helix.cpp
 *
 *  Created on: 29/09/2011
 *      Author: Leandro
 */

#include "Helix.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

namespace fdtd {

Helix::Helix() : ElementsWithFacets(ElementTypeSmartPointer(new Object3DType())),
		startLength(),
		turns(), turnSeparation(), helixRadius(), wireRadius(),
		orientation(), showSolid(), visible() {

	startAngle.SetExpression("0");
	center.SetXExpression("25"); center.SetYExpression("25"); center.SetZExpression("25");
	startLength.SetExpression("0");
	turns.SetExpression("5"); turnSeparation.SetExpression("3"); helixRadius.SetExpression("10"); wireRadius.SetExpression("1");
//	color.SetValue(wxColour(0,0,255));
	showSolid.SetValue(false);
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	AddPriorityProperty(MINIMUM);
	AddProperty(Property("Orientation", &orientation));
	AddProperty(Property("Center", &center, validadorInvalidPoint3D));
	AddProperty(Property("Start length", &startLength, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("Turns", &turns, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Turn separation", &turnSeparation, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Start angle", &startAngle));
	AddProperty(Property("Helix radius", &helixRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Wire radius", &wireRadius, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Rotate", &rotateAxis, validadorInvalidPoint3D));
	AddProperty(Property("Translate", &translateTo, validadorInvalidPoint3D));
	AddMaterialProperty("Material", "PEC");
//	AddProperty(Property("Color", &color));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));

}

Helix::~Helix() {
}

ElementGUISmartPointer Helix::NewElementGUI() {
	return ElementGUISmartPointer(new Helix());
}

wxString Helix::GetRegisteredName() {
	return "Helix";
}

wxIcon Helix::GetIcon() {
	return UtilResource::GetIcon("helix");
}

ElementDTOSmartPointer Helix::NewElementDTO() {
	HelixDTO* result = new HelixDTO;
	//	Não precisa disso, pois agora o que interessa são as faces
//	center.EvalExpressions();
//	result->SetX(center.GetX());
//	result->SetY(center.GetY());
//	result->SetZ(center.GetZ());
//	result->SetLength(startLength.ForceEval());
//    result->SetHelixRadius(helixRadius.ForceEval());
//    result->SetStartAngle(startAngle.ForceEval());
//    result->SetTurnSeparation(turnSeparation.ForceEval());
//    result->SetTurns(turns.ForceEval());
//    result->SetWireRadius(wireRadius.ForceEval());
//	result->SetOrientation(orientation);

	return ElementDTOSmartPointer(result);
}

bool Helix::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	FillApproximateDimensionsWithFacets(xmin, ymin, zmin, xmax, ymax, zmax);
	return true;
}

void Helix::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

//	SetColor(color.GetValue());
	SetColor(GetMaterialColor());

	DrawPolygons(GetFacets(), showSolid.IsValue());
}

bool Helix::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;;

//	if (bottomRadius.GetValue() == 0 && topRadius.GetValue() == 0) {
//		errorMessage.Append("Bottom Radius or Top Radius should be greater than 0.\n");
//		valid = false;
//	}
//
//	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}


vector<Facet> Helix::BuildFacets() {
	vector<Facet> facets;

	double x1,x2,x3,x4,x5,x6,x7,x8;
	double y1,y2,y3,y4,y5,y6,y7,y8;
	double z1,z2,z3,z4,z5,z6,z7,z8;
	double phi,theta, u,v;

	double Angle0;

	Facet Face;
	Facet Face1;
	Facet Face2;
	Facet Face3;

	// Conversão para double
	double wireRadius_dbl = wireRadius.ForceEval();
	double startLength_dbl = startLength.ForceEval();
	double turns_dbl = turns.ForceEval();
	double turnSeparation_dbl = turnSeparation.ForceEval();
	double startAngle_dbl = startAngle.ForceEval();
	double helixRadius_dbl = helixRadius.ForceEval();
	center.EvalExpressions();
	rotateAxis.EvalExpressions();

	//Haste e Tampo inferior
	double segments = 32;
	Face1 = Facet();
	if (startLength_dbl > 0) {
		for(phi = 0; phi < 360; phi += 360.0/segments) {
			v = (phi/180.0*PI);
			x1 = center.GetX() + wireRadius_dbl*cos(v);
			y1 = center.GetY() + wireRadius_dbl*sin(v);
			z1 = center.GetZ();

			v = ((phi+360.0/segments)/180.0*PI);
			x2 = center.GetX()+wireRadius_dbl*cos(v);
			y2 = center.GetY()+wireRadius_dbl*sin(v);
			z2 = center.GetZ()+startLength_dbl-wireRadius_dbl;

			//Laterais do comprimento inferior
			Face2 = Facet();
			Rvector3 v1(x1,y1,z1);
			Face2.Add(&v1);
			Face2.Add(Rvector3(x2,y2,z1));
			Face2.Add(Rvector3(x2,y2,z2));
			Face2.Add(Rvector3(x1,y1,z2));
			facets.push_back(Face2);
			Face1.Add(Rvector3(x1,y1,z1));
		}
		facets.push_back(Face1);
	}
	//Transicao Haste-Helice
	Angle0 = startAngle_dbl+360.0*1.5*wireRadius_dbl/(2*PI*helixRadius_dbl);
	theta = startAngle_dbl;
	if (startLength_dbl > 0) {
		for(phi = 0; phi < 360; phi += 360.0/segments) {
			v = (phi/180.0*PI);
			u = (theta/180.0*PI);
			x1 = center.GetX()+cos(u)*(helixRadius_dbl-wireRadius_dbl) + cos(v)*sin(u)*wireRadius_dbl;
			y1 = center.GetY()+sin(u)*(helixRadius_dbl-wireRadius_dbl) - cos(v)*cos(u)*wireRadius_dbl;
			z1 = center.GetZ()+startLength_dbl+sin(v)*wireRadius_dbl;

			x2 = center.GetX() + cos(u)*(wireRadius_dbl) + cos(v)*sin(u)*wireRadius_dbl;
			y2 = center.GetY() + sin(u)*(wireRadius_dbl) - cos(v)*cos(u)*wireRadius_dbl;
			z2 = center.GetZ() + startLength_dbl + sin(v)*wireRadius_dbl;

			x7 = center.GetX()-wireRadius_dbl*sin(v);
			y7 = center.GetY()-wireRadius_dbl*cos(v);
			z7 = center.GetZ()+startLength_dbl-wireRadius_dbl;

			u = (Angle0/180.0*PI);
			x5 = center.GetX()+cos(u)*helixRadius_dbl+cos(v)*cos(u)*wireRadius_dbl;
			y5 = center.GetY()+sin(u)*helixRadius_dbl+cos(v)*sin(u)*wireRadius_dbl;
			z5 = center.GetZ()+startLength_dbl+sin(v)*wireRadius_dbl;

			u = (theta/180.0*PI);
			v = ((phi+360.0/segments)/180.0*PI);
			x3 = center.GetX()+cos(u)*(wireRadius_dbl)+cos(v)*sin(u)*wireRadius_dbl;
			y3 = center.GetY()+sin(u)*(wireRadius_dbl)-cos(v)*cos(u)*wireRadius_dbl;
			z3 = center.GetZ()+startLength_dbl+sin(v)*wireRadius_dbl;

			x4 = center.GetX()+cos(u)*(helixRadius_dbl-wireRadius_dbl)+cos(v)*sin(u)*wireRadius_dbl;
			y4 = center.GetY()+sin(u)*(helixRadius_dbl-wireRadius_dbl)-cos(v)*cos(u)*wireRadius_dbl;
			z4 = center.GetZ()+startLength_dbl+sin(v)*wireRadius_dbl;

			x8 = center.GetX()-wireRadius_dbl*sin(v);
			y8 = center.GetY()-wireRadius_dbl*cos(v);
			z8 = center.GetZ()+startLength_dbl-wireRadius_dbl;

			u = (Angle0/180.0*PI);
			x6 = center.GetX()+cos(u)*helixRadius_dbl+cos(v)*cos(u)*wireRadius_dbl;
			y6 = center.GetY()+sin(u)*helixRadius_dbl+cos(v)*sin(u)*wireRadius_dbl;
			z6 = center.GetZ()+startLength_dbl+sin(v)*wireRadius_dbl;

			Face1 = Facet();
			Face1.Add(Rvector3(x1,y1,z1));
			Face1.Add(Rvector3(x2,y2,z2));
			Face1.Add(Rvector3(x3,y3,z3));
			Face1.Add(Rvector3(x4,y4,z4));
			facets.push_back(Face1);

			Face2 = Facet();
			Face2.Add(Rvector3(x1,y1,z1));
			Face2.Add(Rvector3(x5,y5,z5));
			Face2.Add(Rvector3(x6,y6,z6));
			Face2.Add(Rvector3(x4,y4,z4));
			facets.push_back(Face2);

			Face3 = Facet();
			Face3.Add(Rvector3(x2,y2,z2));
			Face3.Add(Rvector3(x7,y7,z7));
			Face3.Add(Rvector3(x8,y8,z8));
			Face3.Add(Rvector3(x3,y3,z3));
			facets.push_back(Face3);
		}
	} else { // Não desenha o segmento até o meio e fecha a hélice
		Face2 = Facet();
		for(phi = 0; phi < 360; phi += 360.0/segments) {
			v = ((phi+360.0/segments)/180.0*PI);
			u = (Angle0/180.0*PI);

			x5 = center.GetX()+cos(u)*helixRadius_dbl+cos(v)*cos(u)*wireRadius_dbl;
			y5 = center.GetY()+sin(u)*helixRadius_dbl+cos(v)*sin(u)*wireRadius_dbl;
			z5 = center.GetZ()+startLength_dbl+sin(v)*wireRadius_dbl;

			Face2.Add(Rvector3(x5,y5,z5));
		}
		facets.push_back(Face2);
//		cout << facets.size() << endl;
	}


	//Helice;
	for(phi = 0; phi < 360; phi += 360.0/segments) {
		for(theta=Angle0; theta<startAngle_dbl+360.0*turns_dbl; theta+=360.0/segments) {
			v = (phi/180.0*PI);
			u = (theta/180.0*PI);
			x1 = center.GetX()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y1 = center.GetY()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z1 = center.GetZ()+startLength_dbl+(theta-Angle0)*turnSeparation_dbl/360+ sin(v)*wireRadius_dbl;

			u = ((theta+360.0/segments)/180.0f*PI);
			x2 = center.GetX()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y2 = center.GetY()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z2 = center.GetZ()+startLength_dbl+(theta+360/segments-Angle0)*turnSeparation_dbl/360+ sin(v)*wireRadius_dbl;

			v = ((phi+360.0/segments)/180.0*PI);
			x3 = center.GetX()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y3 = center.GetY()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z3 = center.GetZ()+startLength_dbl+(theta+360/segments-Angle0)*turnSeparation_dbl/360+ sin(v)*wireRadius_dbl;

			u = (theta/180.0*PI);
			x4 = center.GetX()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
			y4 = center.GetY()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
			z4 = center.GetZ()+startLength_dbl+(theta-Angle0)*turnSeparation_dbl/360+ sin(v)*wireRadius_dbl;

			Face1 = Facet();
			Face1.Add(Rvector3(x1,y1,z1));
			Face1.Add(Rvector3(x2,y2,z2));
			Face1.Add(Rvector3(x3,y3,z3));
			Face1.Add(Rvector3(x4,y4,z4));
			facets.push_back(Face1);
		}
	}
	//Tampo superior
	Face1 = Facet();
	for(phi = 0; phi <= 360; phi += 360/segments) {
		v = (phi/180.0*PI);
		u = (theta/180.0*PI);
		x1 = center.GetX()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*cos(u);
		y1 = center.GetY()+(helixRadius_dbl+cos(v)*wireRadius_dbl)*sin(u);
		z1 = center.GetZ()+startLength_dbl+(theta-Angle0)*turnSeparation_dbl/360+ sin(v)*wireRadius_dbl;
		Face1.Add(Rvector3(x1,y1,z1));
	}
	facets.push_back(Face1);


	if (orientation.GetValue() == X) {
		RotateFacets(facets, Rvector3(center.GetX(), center.GetY(), center.GetZ()), 0, 90, 0);
	} else if (orientation.GetValue() == Y) {
		RotateFacets(facets, Rvector3(center.GetX(), center.GetY(), center.GetZ()), -90, 0, 0);
	}

	rotateAxis.EvalExpressions();
	translateTo.EvalExpressions();

	RotateFacets(facets,rotateAxis.GetX(), rotateAxis.GetY(), rotateAxis.GetZ());
	TranslateFacets(facets,translateTo.GetX(), translateTo.GetY(), translateTo.GetZ());
	return facets;
}

void Helix::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + center.GetXExpression() + ") + " + px;
	wxString y = "(" + center.GetYExpression() + ") + " + py;
	wxString z = "(" + center.GetZExpression() + ") + " + pz;
	center.SetXExpression(x);
	center.SetYExpression(y);
	center.SetZExpression(z);
}

}
