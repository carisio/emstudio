///*
// * Cylinder.cpp
// *
// *  Created on: 29/09/2011
// *      Author: leandrocarisio
// */
//
//#include "Cylinder.h"
//#include "emstudio/util/resources/UtilResource.h"
//#include "gui/panels/visualizationpanel/OpenGLStateMachine.h"
//#include "gui/basetypes/basetypevalidator/BaseTypeValidator.h"
//#include "gui/basetypes/basetypevalidator/mathexpressionvalidators/MathExpressionGreaterThanValidator.h"
//#include "gui/basetypes/basetypevalidator/mathexpressionvalidators/MathExpressionGreaterThanOrEqualValidator.h"
//#include "util/Constants.h"
//#include "gui/basetypes/basetypevalidator/point3dmevalidators/InvalidPoint3DMEValidator.h"
//
//Cylinder::Cylinder() : EMStudioGUI(ElementTypeSmartPointer(new Object3DType())) {
//
//	bottomCenter.SetXExpression("25"); bottomCenter.SetYExpression("25"); bottomCenter.SetZExpression("5");
//	topCenter.SetXExpression("25"); topCenter.SetYExpression("25"); topCenter.SetZExpression("45");
//	bottomRadius.SetExpression("10"); topRadius.SetExpression("5");
//	thickness.SetExpression("2");
//
//	showSolid.SetValue(true);
//	visible.SetValue(true);
//
//	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorOuIgualAZero(new MathExpressionGreaterThanOrEqualValidator(0));
//	BaseTypeValidatorSmartPointer validadorMathExpressionMaiorQueZero(new MathExpressionGreaterThanValidator(0));
//	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);
//
//	AddPriorityProperty(MINIMUM);
//	AddProperty(Property("Bottom (center)", &bottomCenter, validadorInvalidPoint3D));
//	AddProperty(Property("Bottom (radius)", &bottomRadius, validadorMathExpressionMaiorOuIgualAZero));
//	AddProperty(Property("Top (center)", &topCenter, validadorInvalidPoint3D));
//	AddProperty(Property("Top (radius)", &topRadius, validadorMathExpressionMaiorOuIgualAZero));
//	AddProperty(Property("Thickness", &thickness, validadorMathExpressionMaiorQueZero));
//	AddMaterialProperty("Material", "PEC");
////	AddProperty(Property("Color", &colour));
//	AddProperty(Property("Solid?", &showSolid));
//	AddProperty(Property("Visible?", &visible));
//}
//
//Cylinder::~Cylinder() {
//
//}
//
//
//ElementGUISmartPointer Cylinder::NewElementGUI() {
//	return ElementGUISmartPointer(new Cylinder());
//}
//
//wxString Cylinder::GetRegisteredName() {
//	return "Cylinder";
//}
//
//wxIcon Cylinder::GetIcon() {
//	return UtilResource::GetIcon("cylinder");
//}
//
//ElementDTOSmartPointer Cylinder::NewElementDTO() {
//	CylinderDTO* result = new CylinderDTO;
//
//	return ElementDTOSmartPointer(result);
//}
//bool Cylinder::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
//	if (!visible.IsValue())
//		return false;
//
//	FillApproximateDimensionsWithFacets(xmin, ymin, zmin, xmax, ymax, zmax);
//	return true;
//}
//void Cylinder::Draw(OpenGLStateMachine* opengl) {
//	if (!visible.IsValue())
//	  return;
//
//	SetColor(GetMaterialColor());
//	DrawPolygons(GetFacets(), showSolid.IsValue());
//}
//
//bool Cylinder::IsAllPropertiesTogetherValid() {
//	wxString errorMessage;
//	bool valid = true;;
//
//	double topRadius_dbl = topRadius.ForceEval();
//	double bottomRadius_dbl = bottomRadius.ForceEval();
//
//	topCenter.EvalExpressions();
//	bottomCenter.EvalExpressions();
//
//	if (bottomRadius_dbl == 0 && topRadius_dbl == 0) {
//		errorMessage.Append("Bottom Radius or Top Radius should be greater than 0.\n");
//		valid = false;
//	}
//	if (bottomCenter.GetX() == topCenter.GetX() && bottomCenter.GetY() == topCenter.GetY() && bottomCenter.GetZ() == topCenter.GetZ()) {
//		errorMessage.Append("Bottom center and top center should be different.\n");
//		valid = false;
//	}
//	SetAllPropertiesTogetherErrorMessage(errorMessage);
//	return valid;
//}
//
///**
// * O cilindro é definido no espaço com 2 pontos, top (p1) e bottom (p0), que representam o centro das duas bases:
// *
// *           /\
// *          /  \
// *         /   x\ (p1)
// *        /   /  \
// *       /   /   /
// *      /   /   /
// *     /   /   /
// *     \  /   /
// *      \x   /
// *  (p0) \  /
// *        \/
// *
// *  (corte ao longo do eixo do cilindro)
// *
// *
// * Para desenhar o cilindro, é necessário definir os pontos que formam o círculo da base e do topo e ligá-los
// * Isso é feito como se segue:
// *
// * A partir dos pontos p1 e p0, é possível calcular o vetor normal ao plano que contém a base, n:
// *
// * n = p1 - p0   =>   n = (x1 - x0, y1 - y0, z1 - z0) = (nx, ny, nz)
// *
// * Com o vetor normal, é possível encontrar o plano em que se encontra a base do cilindro (ponto p0):
// *
// * Para qualquer ponto P com coordenadas x, y, z, o vetor Pp0 é perpendicular a n (o produto escalar entre ambos é zero):
// *
// * (x - x0, y - y0, z - z0) (nx, ny, nz) = 0
// * x * nx + y * ny + z * nz = nx * x0 + ny * y0 + nz * z0
// *
// * Equação do plano:
// * x * nx + y * ny + z * nz = d, em que d = nx * x0 + ny * y0 + nz * z0
// *
// * Agora é preciso escolher dois vetores perpendiculares entre si (v1 e v2) e entre a normal, n.
// * Para isso, basta escolher aleatoriamente um vetor e calcular o outro. A escolha de v1 é feita inicialmente calculando um ponto no plano,
// * como se segue (escolher uma das 3 opções abaixo):
// *
// * 1) Se nx for diferente de 0, escolhe pp.y = y0 + 1 e pp.z = z0 + 1. pp.x é dado por:
// *
// *    pp.x = (d - ny * pp.y - nz * pp.z) / (nx)
// *
// * 2) Se ny for diferende de 0, escolhe pp.x = x0 + 1 e pp.z = z0 + 1. pp.y é dado por:
// *
// *    pp.y = (d - nx * pp.x - nz * pp.z) / (ny)
// *
// * 2) Se nz for diferende de 0, escolhe pp.x = x0 + 1 e pp.y = y0 + 1. pp.z é dado por:
// *
// *    pp.z = (d - nx * pp.x - ny * pp.y) / (nz)
// *
// * Com um ponto no plano, o vetor v1 pode ser formado pelos pontos pp e p0:
// *
// * v1 = (pp.x - p0.x, pp.y - p0.y, pp.z - v0.z) = (v1.x, v1.y, v1.z)
// *
// * Calculado o vetor v1 = (v1.x, v1.y, v1.z), o vetor v2 é apenas o produto vetorial entre v1 e n:
// *
// * v2 = v1 x n
// *      | x    y    z   |
// * v2 = |v1.x v1.y v1.z | = (nz * v1.y - ny * v1.z, nx * v1.z - nz * v1.x, ny * v1.x - nx * v1.y) = (v2.x, v2.y, v2.z)
// *      | nx   ny   nz  |
// *
// * A partir disso, é necessário normalizar os vetors v1 e v2:
// *
// * u1 = v1/|v1|
// * u2 = v2/|v2|
// *
// * Os pontos que formam a base do cilindro de raio r são dados por:
// *
// * origem + [u1 * cos(teta) + u2 * sen(teta)] * r
// *
// * Desmembrando em coordenadas, temos que:
// * x = x0 + [cos(teta) * u1.x + sen(teta) * u2.x] * r
// * y = y0 + [cos(teta) * u1.y + sen(teta) * u2.y] * r    , teta variando entre 0 e 360 graus
// * z = z0 + [cos(teta) * u1.z + sen(teta) * u2.z] * r
// *
// * Essa é a equação do círculo de raio r que forma a base do cilindro.
// * No caso de um tubo circular, é necessário dois circulos na base e dois círculos no topo (interno e externo).
// */
//std::vector<Facet> Cylinder::GetFacets() {
//	std::vector<Facet> facets;
//
//	bottomCenter.EvalExpressions();
//	topCenter.EvalExpressions();
//	bottomRadius.ForceEval();
//	topRadius.ForceEval();
//	thickness.ForceEval();
//
//	/* Calcula pontos p1 e p2 */
//	Rvector3 p1(topCenter.GetX(), topCenter.GetY(), topCenter.GetZ());
//	Rvector3 p0(bottomCenter.GetX(), bottomCenter.GetY(), bottomCenter.GetZ());
//	/* Calcula n */
//	Rvector3 n(p1.X - p0.X, p1.Y - p0.Y, p1.Z - p0.Z);
//	/* Constante d da equação do plano da base */
//	double d = n.X * p0.X + n.Y * p0.Y + n.Z * p0.Z;
//	/* Calcula pp */
//	Rvector3 pp;
//	if (n.X != 0 ) {
//		pp.Y = p0.Y+1;
//		pp.Z = p0.Z+1;
//		pp.X = (d - n.Y * pp.Y - n.Z * pp.Z) / n.X;
//	} else if (n.Y != 0) {
//		pp.X = p0.X+1;
//		pp.Z = p0.Z+1;
//		pp.Y = (d - n.X * pp.X - n.Z * pp.Z) / n.Y;
//	} else if (n.Z != 0) {
//		pp.X = p0.X+1;
//		pp.Y = p0.Y+1;
//		pp.Z = (d - n.X * pp.X - n.Y * pp.Y) / n.Z;
//
//	}
//	/* Calcula os vetores v1 e v2 */
//	Rvector3 v1(pp.X - p0.X, pp.Y - p0.Y, pp.Z - p0.Z);
//	Rvector3 v2(n.Z * v1.Y - n.Y * v1.Z, n.X * v1.Z - n.Z * v1.X, n.Y * v1.X - n.X * v1.Y);
//	/* Normaliza os vetores v1 e v2 */
//	Rvector3 u1 = v1; u1.Normalize();
//	Rvector3 u2 = v2; u2.Normalize();
//
//	/* raios interno e externo da base */
//	double int_radius_base = bottomRadius.Eval();
//	double ext_radius_base = int_radius_base + thickness.Eval();
//	/* raios interno e externo do topo */
//	double int_radius_top = topRadius.Eval();
//	double ext_radius_top = int_radius_top + thickness.Eval();
//
//	/*
//	 * Desenha as faces do tubo.
//	 * Imagine que a base (um anel) será dividida em inúmeros segmentos.
//	 * Veja um exemplo de um dos segmentos (se o número de segmentos for muito grande, eles são próximos de retangulos.
//	 *
//	 * ^
//	 * |
//	 * |
//	 * |  p3         p4
//	 * |    ---------
//	 * |   |         |
//	 * |   |         |
//	 * |    ---------
//	 * |  p2         p1
//	 * |
//	 * |---------------------->
//	 *
//	 * No topo existe um segmento equivalente, com coordenadas p5, p6, p7 e p8, com outro raio.
//	 *
//	 * Para desenha o tubo, é necessário então desenhar 4 faces para cada segmento. As faces da base e topo, e as faces
//	 * laterais (interna e externa) ligando a base ao topo.
//	 *
//	 * Base: pontos p1, p2, p3, p4
//	 * Topo: pontos p5, p6, p7, p8
//	 * Lateral interna: pontos p2, p3, p7, p6
//	 * Lateral externa: pontos p1, p4, p8, p5
//	 */
//	double segments = 32;
//	for (int i = 0; i < segments; i++) {
//		double thetaI = 2*PI*i/segments;
//		double thetaIplus1 = 2*PI*(i+1)/segments;
//
//		double cos_theta = cos(thetaI);
//		double sin_theta = sin(thetaI);
//		double cos_theta_plus1 = cos(thetaIplus1);
//		double sin_theta_plus1 = sin(thetaIplus1);
//
//		/* Desenha a base, que está no plano que contém o ponto p0 */
//		double x1 = p0.X + (cos_theta * u1.X + sin_theta * u2.X) * ext_radius_base;
//		double y1 = p0.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * ext_radius_base;
//		double z1 = p0.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * ext_radius_base;
//
//		double x2 = p0.X + (cos_theta * u1.X + sin_theta * u2.X) * int_radius_base;
//		double y2 = p0.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * int_radius_base;
//		double z2 = p0.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * int_radius_base;
//
//		double x3 = p0.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * int_radius_base;
//		double y3 = p0.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * int_radius_base;
//		double z3 = p0.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * int_radius_base;
//
//		double x4 = p0.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * ext_radius_base;
//		double y4 = p0.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * ext_radius_base;
//		double z4 = p0.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * ext_radius_base;
//
//		/* Desenha a base, que está no plano que contém o ponto p1 */
//		double x5 = p1.X + (cos_theta * u1.X + sin_theta * u2.X) * ext_radius_top;
//		double y5 = p1.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * ext_radius_top;
//		double z5 = p1.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * ext_radius_top;
//
//		double x6 = p1.X + (cos_theta * u1.X + sin_theta * u2.X) * int_radius_top;
//		double y6 = p1.Y + (cos_theta * u1.Y + sin_theta * u2.Y) * int_radius_top;
//		double z6 = p1.Z + (cos_theta * u1.Z + sin_theta * u2.Z) * int_radius_top;
//
//		double x7 = p1.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * int_radius_top;
//		double y7 = p1.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * int_radius_top;
//		double z7 = p1.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * int_radius_top;
//
//		double x8 = p1.X + (cos_theta_plus1 * u1.X + sin_theta_plus1 * u2.X) * ext_radius_top;
//		double y8 = p1.Y + (cos_theta_plus1 * u1.Y + sin_theta_plus1 * u2.Y) * ext_radius_top;
//		double z8 = p1.Z + (cos_theta_plus1 * u1.Z + sin_theta_plus1 * u2.Z) * ext_radius_top;
//
//		Facet face = Facet();
//		face.Add(Rvector3(x1,y1,z1));
//		face.Add(Rvector3(x2,y2,z2));
//		face.Add(Rvector3(x3,y3,z3));
//		face.Add(Rvector3(x4,y4,z4));
//		facets.push_back(face);
//
//		face = Facet();
//		face.Add(Rvector3(x1,y1,z1));
//		face.Add(Rvector3(x4,y4,z4));
//		face.Add(Rvector3(x8,y8,z8));
//		face.Add(Rvector3(x5,y5,z5));
//		facets.push_back(face);
//
//		face = Facet();
//		face.Add(Rvector3(x5,y5,z5));
//		face.Add(Rvector3(x6,y6,z6));
//		face.Add(Rvector3(x7,y7,z7));
//		face.Add(Rvector3(x8,y8,z8));
//		facets.push_back(face);
//
//		face = Facet();
//		face.Add(Rvector3(x2,y2,z2));
//		face.Add(Rvector3(x3,y3,z3));
//		face.Add(Rvector3(x7,y7,z7));
//		face.Add(Rvector3(x6,y6,z6));
//		facets.push_back(face);
//	}
//
//	return facets;
//}
