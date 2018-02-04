/*
 * MoM.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "MoM.h"
#include "emstudio/dto/momapp/MoMDTO.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"

namespace mom {

MoM::MoM() : ElementsWithSegments(ElementTypeSmartPointer(new MethodType())) {
	initialFrequency.SetExpression("300");
	frequencyStep.SetExpression("0");
	nFrequency.SetExpression("1");

	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
	BaseTypeValidatorSmartPointer validadorGroundParameters(new InvalidGroundParametersValidators);

	AddProperty(Property("Use extended thin-wire kernel?", &extendedThinWire));
	AddProperty(Property("Initial frequency", &initialFrequency, validadorMathExpressionMaiorQueZero));
	AddProperty(Property("Frequency step", &frequencyStep, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("N frequencies", &nFrequency, validadorMathExpressionMaiorOuIgualAZero));
	AddProperty(Property("Ground parameters", &groundParameters, validadorGroundParameters));
}


ElementGUISmartPointer MoM::NewElementGUI() {
	return ElementGUISmartPointer(new MoM);
}

wxString MoM::GetRegisteredName() {
	return "MoM";
}

wxIcon MoM::GetIcon() {
	return UtilResource::GetIcon("fdtd");
}

ElementDTOSmartPointer MoM::NewElementDTO() {
	MoMDTO* result = new MoMDTO;

	result->SetUseExtendedThinWireKernel(extendedThinWire.IsValue());
	result->SetInitialFrequency(initialFrequency.ForceEval());
	result->SetFrequencyStep(frequencyStep.ForceEval());
	result->SetNFrequency(nFrequency.ForceEval());

	groundParameters.IsGroundParametersValid();
	result->SetHasMedium1(!groundParameters.GetGround1().IsFreeSpace());
	result->SetMedium1(groundParameters.GetGround1());
	result->SetCurrentsGoToZero(groundParameters.IsCurrentsOnSegmentsTouchingGroundGoToZero());
	result->SetCurrentsInterpolated(groundParameters.IsCurrentsOnSegmentsTouchingGroundInterpolated());
	result->SetHasMedium2(groundParameters.IsGround2());
	result->SetMedium2(groundParameters.GetGround2());
	result->SetLinearCliff(groundParameters.IsLinearCliff());
	result->SetCircularCliff(groundParameters.IsCircularCliff());
	result->SetDistBelowGround(groundParameters.GetDistanceBelowGround());
	result->SetDistFromOrigin(groundParameters.GetDistanceFromOrigin());
	result->SetNumberOfRadials(groundParameters.GetNumberOfWires());
	result->SetWireLength(groundParameters.GetWireLength());
	result->SetWireRadius(groundParameters.GetWireRadius());

	return ElementDTOSmartPointer(result);
}
bool MoM::IsAllPropertiesTogetherValid() {
	bool valid = true;
	return valid;
}

void MoM::DoMove(Point3DME p) {
}
bool MoM::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	groundParameters.IsGroundParametersValid();
	if (groundParameters.GetNumberOfWires() <= 0 && !groundParameters.IsGround2())
		return false;

	if (groundParameters.GetNumberOfWires() > 0) {
		xmin = ymin = -groundParameters.GetWireLength();
		xmax = ymax = groundParameters.GetWireLength();
		zmin = -groundParameters.GetWireRadius();
		zmax = groundParameters.GetWireRadius();
	}

	if (groundParameters.IsGround2()) {
		xmin = ymin = -(groundParameters.GetDistanceFromOrigin()+groundParameters.GetWireLength());
		xmax = ymax = +(groundParameters.GetDistanceFromOrigin()+groundParameters.GetWireLength());
	}

	return true;
}
void MoM::Draw(OpenGLStateMachine* opengl) {
	double xmin, ymin, zmin, xmax, ymax, zmax;
	bool hasDimensions = GetProjectBoundary(xmin, ymin, zmin, xmax, ymax, zmax);
	double xdiff = xmax-xmin;
	double ydiff = ymax-ymin;
	double zdiff = zmax-zmin;
	if (xdiff > zdiff) {
		xmin -= xdiff;
		xmax += xdiff;
	} else {
		xmin -= zdiff;
		xmax += zdiff;
	}
	if (zdiff > zdiff) {
		ymin -= ydiff;
		ymax += ydiff;
	} else {
		ymin -= zdiff;
		ymax += zdiff;
	}

	if (!hasDimensions) {
		xmin = -2; ymin = -2; xmax = 2; ymax = 2;
	}

	groundParameters.IsGroundParametersValid();

	int nRad = groundParameters.GetNumberOfWires();
	if (nRad > 0) {
		double length = groundParameters.GetWireLength();
		double radius = groundParameters.GetWireRadius();

		Material m; m.SetType(PEC);
		SetColor(m.GetColor());
		for (int i = 0; i < nRad; i++) {
			double ang = 2*PI*i/nRad;
			double x = length*cos(ang);
			double y = length*sin(ang);
			DrawSegment(0,0,0,x,y,0,radius,true);
		}
	}

	if (!groundParameters.GetGround1().IsFreeSpace() && !groundParameters.IsGround2()) {
		SetColor(groundParameters.GetGround1().GetColor());
		DrawPlaneZ(xmin, ymin, xmax, ymax, 0, true);
	} else if (!groundParameters.GetGround1().IsFreeSpace() && groundParameters.IsLinearCliff()) {
		cout << "Eh linear cliff" << endl;
		SetColor(groundParameters.GetGround1().GetColor());
		DrawPlaneZ(xmin, ymin, groundParameters.GetDistanceFromOrigin(), ymax, 0, true);
		DrawPlaneX(ymin, -groundParameters.GetDistanceBelowGround(), ymax, 0, xmin, true);
		DrawPlaneX(ymin, -groundParameters.GetDistanceBelowGround(), ymax, 0, groundParameters.GetDistanceFromOrigin(), true);
		DrawPlaneY(xmin, -groundParameters.GetDistanceBelowGround(), groundParameters.GetDistanceFromOrigin(), 0, ymin, true);
		DrawPlaneY(xmin, -groundParameters.GetDistanceBelowGround(), groundParameters.GetDistanceFromOrigin(), 0, ymax, true);
		SetColor(groundParameters.GetGround2().GetColor());
		DrawPlaneZ(groundParameters.GetDistanceFromOrigin(), ymin, xmax+groundParameters.GetDistanceFromOrigin(), ymax, -groundParameters.GetDistanceBelowGround(), true);
	} else if (!groundParameters.GetGround1().IsFreeSpace() && groundParameters.IsCircularCliff()) {
		cout << "Eh circular cliff" << endl;
		// Se houve alguma mudança no projeto, é necessário recalcular as faces para ground1 e ground2
		if (IsChanged()) {
			double h = groundParameters.GetDistanceBelowGround();
			if (h == 0) h = 1;
			circularCliffGround1 = BuildCircularTube(0, groundParameters.GetDistanceFromOrigin(), -2*h, 0);
			circularCliffGround2 = BuildCircularTube(groundParameters.GetDistanceFromOrigin(), 2*groundParameters.GetDistanceFromOrigin(), -h, -2*h);
		}
		SetColor(groundParameters.GetGround1().GetColor());
		DrawPolygons(circularCliffGround1, true);
		SetColor(groundParameters.GetGround2().GetColor());
		DrawPolygons(circularCliffGround2, true);
	}
}

std::vector<Facet> MoM::BuildCircularTube(double innerRadius, double outerRadius, double zMin, double zMax) {
	std::vector<Facet> facets;

	/* Calcula pontos p1 e p2 */
	Rvector3 p1(0, 0, zMax);
	Rvector3 p0(0, 0, zMin);
	/* Calcula n */
	Rvector3 n(p1.X - p0.X, p1.Y - p0.Y, p1.Z - p0.Z);
	/* Constante d da equação do plano da base */
	double d = n.X * p0.X + n.Y * p0.Y + n.Z * p0.Z;
	/* Calcula pp */
	Rvector3 pp;
	if (n.X != 0 ) {
		pp.Y = p0.Y+1;
		pp.Z = p0.Z+1;
		pp.X = (d - n.Y * pp.Y - n.Z * pp.Z) / n.X;
	} else if (n.Y != 0) {
		pp.X = p0.X+1;
		pp.Z = p0.Z+1;
		pp.Y = (d - n.X * pp.X - n.Z * pp.Z) / n.Y;
	} else if (n.Z != 0) {
		pp.X = p0.X+1;
		pp.Y = p0.Y+1;
		pp.Z = (d - n.X * pp.X - n.Y * pp.Y) / n.Z;

	}
	/* Calcula os vetores v1 e v2 */
	Rvector3 v1(pp.X - p0.X, pp.Y - p0.Y, pp.Z - p0.Z);
	Rvector3 v2(n.Z * v1.Y - n.Y * v1.Z, n.X * v1.Z - n.Z * v1.X, n.Y * v1.X - n.X * v1.Y);
	/* Normaliza os vetores v1 e v2 */
	Rvector3 u1 = v1; u1.Normalize();
	Rvector3 u2 = v2; u2.Normalize();

	/* raios interno e externo da base */
	double int_radius_base = innerRadius;
	double ext_radius_base = outerRadius;
	/* raios interno e externo do topo */
	double int_radius_top = innerRadius;
	double ext_radius_top = outerRadius;

	/*
	 * Desenha as faces do tubo.
	 * Imagine que a base (um anel) será dividida em inúmeros segmentos.
	 * Veja um exemplo de um dos segmentos (se o número de segmentos for muito grande, eles são próximos de retangulos.
	 *
	 * ^
	 * |
	 * |
	 * |  p3         p4
	 * |    ---------
	 * |   |         |
	 * |   |         |
	 * |    ---------
	 * |  p2         p1
	 * |
	 * |---------------------->
	 *
	 * No topo existe um segmento equivalente, com coordenadas p5, p6, p7 e p8, com outro raio.
	 *
	 * Para desenha o tubo, é necessário então desenhar 4 faces para cada segmento. As faces da base e topo, e as faces
	 * laterais (interna e externa) ligando a base ao topo.
	 *
	 * Base: pontos p1, p2, p3, p4
	 * Topo: pontos p5, p6, p7, p8
	 * Lateral interna: pontos p2, p3, p7, p6
	 * Lateral externa: pontos p1, p4, p8, p5
	 */
	double segments = 32;
	for (int i = 0; i < segments; i++) {
		double thetaI = 2*PI*i/segments;
		double thetaIplus1 = 2*PI*(i+1)/segments;

		double cos_theta = cos(thetaI);
		double sin_theta = sin(thetaI);
		double cos_theta_plus1 = cos(thetaIplus1);
		double sin_theta_plus1 = sin(thetaIplus1);

		/* Desenha a base, que está no plano que contém o ponto p0 */
		double x1 = p0.X + (cos_theta * u1.X + sin_theta * u2.X) * ext_radius_base;
		double y1 = p0.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * ext_radius_base;
		double z1 = p0.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * ext_radius_base;

		double x2 = p0.X + (cos_theta * u1.X + sin_theta * u2.X) * int_radius_base;
		double y2 = p0.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * int_radius_base;
		double z2 = p0.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * int_radius_base;

		double x3 = p0.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * int_radius_base;
		double y3 = p0.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * int_radius_base;
		double z3 = p0.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * int_radius_base;

		double x4 = p0.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * ext_radius_base;
		double y4 = p0.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * ext_radius_base;
		double z4 = p0.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * ext_radius_base;

		/* Desenha a base, que está no plano que contém o ponto p1 */
		double x5 = p1.X + (cos_theta * u1.X + sin_theta * u2.X) * ext_radius_top;
		double y5 = p1.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * ext_radius_top;
		double z5 = p1.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * ext_radius_top;

		double x6 = p1.X + (cos_theta * u1.X + sin_theta * u2.X) * int_radius_top;
		double y6 = p1.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * int_radius_top;
		double z6 = p1.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * int_radius_top;

		double x7 = p1.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * int_radius_top;
		double y7 = p1.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * int_radius_top;
		double z7 = p1.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * int_radius_top;

		double x8 = p1.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * ext_radius_top;
		double y8 = p1.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * ext_radius_top;
		double z8 = p1.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * ext_radius_top;

		Facet face = Facet();
		face.Add(Rvector3(x1,y1,z1));
		face.Add(Rvector3(x2,y2,z2));
		face.Add(Rvector3(x3,y3,z3));
		face.Add(Rvector3(x4,y4,z4));
		facets.push_back(face);

		face = Facet();
		face.Add(Rvector3(x1,y1,z1));
		face.Add(Rvector3(x4,y4,z4));
		face.Add(Rvector3(x8,y8,z8));
		face.Add(Rvector3(x5,y5,z5));
		facets.push_back(face);

		face = Facet();
		face.Add(Rvector3(x5,y5,z5));
		face.Add(Rvector3(x6,y6,z6));
		face.Add(Rvector3(x7,y7,z7));
		face.Add(Rvector3(x8,y8,z8));
		facets.push_back(face);

		face = Facet();
		face.Add(Rvector3(x2,y2,z2));
		face.Add(Rvector3(x3,y3,z3));
		face.Add(Rvector3(x7,y7,z7));
		face.Add(Rvector3(x6,y6,z6));
		facets.push_back(face);
	}

	return facets;
}
MoM::~MoM() {
}


} /* namespace mom */
