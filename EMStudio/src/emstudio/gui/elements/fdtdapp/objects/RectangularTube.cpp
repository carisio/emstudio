/*
 * RectangularTube.cpp
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#include "RectangularTube.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "emstudio/util/resources/UtilResource.h"

RectangularTube::RectangularTube() : ElementsWithFacets(ElementTypeSmartPointer(new Object3DType())) ,
		showSolid(), visible(){

//	colour.SetValue(wxColour(0,0,255));
	showSolid.SetValue(false);
	visible.SetValue(true);

	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);
	BaseTypeValidatorSmartPointer validadorInvalidGeometry(new InvalidRectangularTubeGeometryMEValidator);

	AddPriorityProperty(MINIMUM);
	AddProperty(Property("Geometry", &geometry, validadorInvalidGeometry));
	AddProperty(Property("Rotate", &rotateAxis, validadorInvalidPoint3D));
	AddProperty(Property("Translate", &translateTo, validadorInvalidPoint3D));
	AddMaterialProperty("Material", "PEC");
//	AddProperty(Property("Color", &colour));
	AddProperty(Property("Solid?", &showSolid));
	AddProperty(Property("Visible?", &visible));
}

RectangularTube::~RectangularTube() {

}

ElementGUISmartPointer RectangularTube::NewElementGUI() {
	return ElementGUISmartPointer(new RectangularTube());
}

wxString RectangularTube::GetRegisteredName() {
	return "Rectangular Tube";
}

wxIcon RectangularTube::GetIcon() {
	return UtilResource::GetIcon("rectangulartube");
}

ElementDTOSmartPointer RectangularTube::NewElementDTO() {
	RectangularTubeDTO* result = new RectangularTubeDTO;

//	Não precisa disso, pois agora o que interessa são as faces
//    result->SetBaseInnerHeight(baseInnerHeight.ForceEval());
//    result->SetBaseInnerWidth(baseInnerWidth.ForceEval());
//    result->SetBaseOutterHeight(baseOutterHeight.ForceEval());
//    result->SetBaseOutterWidth(baseOutterWidth.ForceEval());
//    result->SetLength(length.ForceEval());
//    result->SetOrientation(orientation);
//    result->SetTopInnerHeight(topInnerHeight.ForceEval());
//    result->SetTopInnerWidth(topInnerWidth.ForceEval());
//    result->SetTopOutterHeight(topOutterHeight.ForceEval());
//    result->SetTopOutterWidth(topOutterWidth.ForceEval());
//    result->SetX(center.GetX());
//    result->SetY(center.GetY());
//    result->SetZ(center.GetZ());
//
    return ElementDTOSmartPointer(result);
}

bool RectangularTube::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	FillApproximateDimensionsWithFacets(xmin, ymin, zmin, xmax, ymax, zmax);
	return true;
}
void RectangularTube::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

	SetColor(GetMaterialColor());
	DrawPolygons(GetFacets(), showSolid.IsValue());

//	vector<Facet> facets;
//
//	Rvector3 p1(0, 50, 0);
//	Rvector3 p2(50, 50, 0);
//	Rvector3 p3(0, 0, 0);
//	Rvector3 p4(50, 0, 0);
//	Rvector3 p5(50, 50, 80);
//	Rvector3 p6(100, 50, 80);
//	Rvector3 p7(50, 0, 50);
//	Rvector3 p8(100, 0, 50);
//
//	Facet f;
//	f.Add(p1); f.Add(p5); f.Add(p2);
//	facets.push_back(f);
//	f = Facet();
//	f.Add(p5); f.Add(p6); f.Add(p2);
//	facets.push_back(f);
//	f = Facet();
//	f.Add(p8); f.Add(p2); f.Add(p6);
//	facets.push_back(f);
//	f = Facet();
//	f.Add(p8); f.Add(p4); f.Add(p2);
//	facets.push_back(f);
//	f = Facet();
//	f.Add(p4); f.Add(p3); f.Add(p8);
//	facets.push_back(f);
//	f = Facet();
//	f.Add(p3); f.Add(p7); f.Add(p8);
//	facets.push_back(f);
//	f = Facet();
//	f.Add(p3); f.Add(p1); f.Add(p7);
//	facets.push_back(f);
//	f = Facet();
//	f.Add(p5); f.Add(p1); f.Add(p7);
//	facets.push_back(f);
//
//	DrawPolygons(facets, showSolid.IsValue());
}

bool RectangularTube::IsAllPropertiesTogetherValid() {
	wxString errorMessage;
	bool valid = true;

	SetAllPropertiesTogetherErrorMessage(errorMessage);
	return valid;
}

/**
 *  ^ coord2
 *  |
 *  | P8                 P7
 *  |  x-----------------x
 *  |  |                 |
 *  |  |   P4       P3   |
 *  |  |   x---------x   |
 *  |  |   |         |   |
 *  |  |   |         |   |
 *  |  |   |         |   |
 *  |  |   x---------x   |
    |  |   P1        P2  |
 *  |  |                 |
 *  |  x-----------------x
 *  |  P5               P6
 *  |-------------------------> coord1
 *
 */
vector<Facet> RectangularTube::BuildFacets() {
	geometry.IsGeometryValid();

	double bCutAt = geometry.GetBaseCutAt();
	double bCoord1Begin = geometry.GetBaseCoord1Begin();
	double bCoord1End = geometry.GetBaseCoord1End();
	double bCoord2Begin = geometry.GetBaseCoord2Begin();
	double bCoord2End = geometry.GetBaseCoord2End();
	double bCoord1Thickness = geometry.GetBaseCoord1Thickness();
	double bCoord2Thickness = geometry.GetBaseCoord2Thickness();
	double tCutAt = geometry.GetTopCutAt();
	double tCoord1Begin = geometry.GetTopCoord1Begin();
	double tCoord1End = geometry.GetTopCoord1End();
	double tCoord2Begin = geometry.GetTopCoord2Begin();
	double tCoord2End = geometry.GetTopCoord2End();
	double tCoord1Thickness = geometry.GetTopCoord1Thickness();
	double tCoord2Thickness = geometry.GetTopCoord2Thickness();

	rotateAxis.EvalExpressions();

	vector<Facet> facets;

	Rvector3 P1t,P2t,P3t,P4t,P5t,P6t,P7t,P8t;
	Rvector3 P1b,P2b,P3b,P4b,P5b,P6b,P7b,P8b;
	Facet face;

	if (geometry.IsXOriented()) {
		P1b.X=P2b.X=P3b.X=P4b.X=P5b.X=P6b.X=P7b.X=P8b.X=bCutAt;
		P1t.X=P2t.X=P3t.X=P4t.X=P5t.X=P6t.X=P7t.X=P8t.X=tCutAt;
		P1b.Y=bCoord1Begin; P1b.Z=bCoord2Begin;
		P2b.Y=bCoord1End; P2b.Z=bCoord2Begin;
		P3b.Y=bCoord1End; P3b.Z=bCoord2End;
		P4b.Y=bCoord1Begin; P4b.Z=bCoord2End;
		P5b.Y=bCoord1Begin-bCoord1Thickness; P5b.Z=bCoord2Begin-bCoord2Thickness;
		P6b.Y=bCoord1End+bCoord1Thickness; P6b.Z=bCoord2Begin-bCoord2Thickness;
		P7b.Y=bCoord1End+bCoord1Thickness; P7b.Z=bCoord2End+bCoord2Thickness;
		P8b.Y=bCoord1Begin-bCoord1Thickness; P8b.Z=bCoord2End+bCoord2Thickness;
		P1t.Y=tCoord1Begin; P1t.Z=tCoord2Begin;
		P2t.Y=tCoord1End; P2t.Z=tCoord2Begin;
		P3t.Y=tCoord1End; P3t.Z=tCoord2End;
		P4t.Y=tCoord1Begin; P4t.Z=tCoord2End;
		P5t.Y=tCoord1Begin-tCoord1Thickness; P5t.Z=tCoord2Begin-tCoord2Thickness;
		P6t.Y=tCoord1End+tCoord1Thickness; P6t.Z=tCoord2Begin-tCoord2Thickness;
		P7t.Y=tCoord1End+tCoord1Thickness; P7t.Z=tCoord2End+tCoord2Thickness;
		P8t.Y=tCoord1Begin-tCoord1Thickness; P8t.Z=tCoord2End+tCoord2Thickness;
	} else if (geometry.IsYOriented()) {
		P1b.Y=P2b.Y=P3b.Y=P4b.Y=P5b.Y=P6b.Y=P7b.Y=P8b.Y=bCutAt;
		P1t.Y=P2t.Y=P3t.Y=P4t.Y=P5t.Y=P6t.Y=P7t.Y=P8t.Y=tCutAt;
		P1b.X=bCoord1Begin; P1b.Z=bCoord2Begin;
		P2b.X=bCoord1End; P2b.Z=bCoord2Begin;
		P3b.X=bCoord1End; P3b.Z=bCoord2End;
		P4b.X=bCoord1Begin; P4b.Z=bCoord2End;
		P5b.X=bCoord1Begin-bCoord1Thickness; P5b.Z=bCoord2Begin-bCoord2Thickness;
		P6b.X=bCoord1End+bCoord1Thickness; P6b.Z=bCoord2Begin-bCoord2Thickness;
		P7b.X=bCoord1End+bCoord1Thickness; P7b.Z=bCoord2End+bCoord2Thickness;
		P8b.X=bCoord1Begin-bCoord1Thickness; P8b.Z=bCoord2End+bCoord2Thickness;
		P1t.X=tCoord1Begin; P1t.Z=tCoord2Begin;
		P2t.X=tCoord1End; P2t.Z=tCoord2Begin;
		P3t.X=tCoord1End; P3t.Z=tCoord2End;
		P4t.X=tCoord1Begin; P4t.Z=tCoord2End;
		P5t.X=tCoord1Begin-tCoord1Thickness; P5t.Z=tCoord2Begin-tCoord2Thickness;
		P6t.X=tCoord1End+tCoord1Thickness; P6t.Z=tCoord2Begin-tCoord2Thickness;
		P7t.X=tCoord1End+tCoord1Thickness; P7t.Z=tCoord2End+tCoord2Thickness;
		P8t.X=tCoord1Begin-tCoord1Thickness; P8t.Z=tCoord2End+tCoord2Thickness;
	} else if (geometry.IsZOriented()) {
		P1b.Z=P2b.Z=P3b.Z=P4b.Z=P5b.Z=P6b.Z=P7b.Z=P8b.Z=bCutAt;
		P1t.Z=P2t.Z=P3t.Z=P4t.Z=P5t.Z=P6t.Z=P7t.Z=P8t.Z=tCutAt;
		P1b.X=bCoord1Begin; P1b.Y=bCoord2Begin;
		P2b.X=bCoord1End; P2b.Y=bCoord2Begin;
		P3b.X=bCoord1End; P3b.Y=bCoord2End;
		P4b.X=bCoord1Begin; P4b.Y=bCoord2End;
		P5b.X=bCoord1Begin-bCoord1Thickness; P5b.Y=bCoord2Begin-bCoord2Thickness;
		P6b.X=bCoord1End+bCoord1Thickness; P6b.Y=bCoord2Begin-bCoord2Thickness;
		P7b.X=bCoord1End+bCoord1Thickness; P7b.Y=bCoord2End+bCoord2Thickness;
		P8b.X=bCoord1Begin-bCoord1Thickness; P8b.Y=bCoord2End+bCoord2Thickness;
		P1t.X=tCoord1Begin; P1t.Y=tCoord2Begin;
		P2t.X=tCoord1End; P2t.Y=tCoord2Begin;
		P3t.X=tCoord1End; P3t.Y=tCoord2End;
		P4t.X=tCoord1Begin; P4t.Y=tCoord2End;
		P5t.X=tCoord1Begin-tCoord1Thickness; P5t.Y=tCoord2Begin-tCoord2Thickness;
		P6t.X=tCoord1End+tCoord1Thickness; P6t.Y=tCoord2Begin-tCoord2Thickness;
		P7t.X=tCoord1End+tCoord1Thickness; P7t.Y=tCoord2End+tCoord2Thickness;
		P8t.X=tCoord1Begin-tCoord1Thickness; P8t.Y=tCoord2End+tCoord2Thickness;
	}
	//Tampo inferior
	face = Facet();
	face.Add(Rvector3(P1b.X,P1b.Y,P1b.Z));
	face.Add(Rvector3(P5b.X,P5b.Y,P5b.Z));
	face.Add(Rvector3(P6b.X,P6b.Y,P6b.Z));
	face.Add(Rvector3(P2b.X,P2b.Y,P2b.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P1b.X,P1b.Y,P1b.Z));
	face.Add(Rvector3(P5b.X,P5b.Y,P5b.Z));
	face.Add(Rvector3(P8b.X,P8b.Y,P8b.Z));
	face.Add(Rvector3(P4b.X,P4b.Y,P4b.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P4b.X,P4b.Y,P4b.Z));
	face.Add(Rvector3(P8b.X,P8b.Y,P8b.Z));
	face.Add(Rvector3(P7b.X,P7b.Y,P7b.Z));
	face.Add(Rvector3(P3b.X,P3b.Y,P3b.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P3b.X,P3b.Y,P3b.Z));
	face.Add(Rvector3(P7b.X,P7b.Y,P7b.Z));
	face.Add(Rvector3(P6b.X,P6b.Y,P6b.Z));
	face.Add(Rvector3(P2b.X,P2b.Y,P2b.Z));
	facets.push_back(face);

	//Tampo superior
	face = Facet();
	face.Add(Rvector3(P1t.X,P1t.Y,P1t.Z));
	face.Add(Rvector3(P5t.X,P5t.Y,P5t.Z));
	face.Add(Rvector3(P6t.X,P6t.Y,P6t.Z));
	face.Add(Rvector3(P2t.X,P2t.Y,P2t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P1t.X,P1t.Y,P1t.Z));
	face.Add(Rvector3(P5t.X,P5t.Y,P5t.Z));
	face.Add(Rvector3(P8t.X,P8t.Y,P8t.Z));
	face.Add(Rvector3(P4t.X,P4t.Y,P4t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P4t.X,P4t.Y,P4t.Z));
	face.Add(Rvector3(P8t.X,P8t.Y,P8t.Z));
	face.Add(Rvector3(P7t.X,P7t.Y,P7t.Z));
	face.Add(Rvector3(P3t.X,P3t.Y,P3t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P3t.X,P3t.Y,P3t.Z));
	face.Add(Rvector3(P7t.X,P7t.Y,P7t.Z));
	face.Add(Rvector3(P6t.X,P6t.Y,P6t.Z));
	face.Add(Rvector3(P2t.X,P2t.Y,P2t.Z));
	facets.push_back(face);
	//Faces internas
	face = Facet();
	face.Add(Rvector3(P1b.X,P1b.Y,P1b.Z));
	face.Add(Rvector3(P2b.X,P2b.Y,P2b.Z));
	face.Add(Rvector3(P2t.X,P2t.Y,P2t.Z));
	face.Add(Rvector3(P1t.X,P1t.Y,P1t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P1b.X,P1b.Y,P1b.Z));
	face.Add(Rvector3(P4b.X,P4b.Y,P4b.Z));
	face.Add(Rvector3(P4t.X,P4t.Y,P4t.Z));
	face.Add(Rvector3(P1t.X,P1t.Y,P1t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P3b.X,P3b.Y,P3b.Z));
	face.Add(Rvector3(P4b.X,P4b.Y,P4b.Z));
	face.Add(Rvector3(P4t.X,P4t.Y,P4t.Z));
	face.Add(Rvector3(P3t.X,P3t.Y,P3t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P3b.X,P3b.Y,P3b.Z));
	face.Add(Rvector3(P2b.X,P2b.Y,P2b.Z));
	face.Add(Rvector3(P2t.X,P2t.Y,P2t.Z));
	face.Add(Rvector3(P3t.X,P3t.Y,P3t.Z));
	facets.push_back(face);
	//Faces Externas
	face = Facet();
	face.Add(Rvector3(P5b.X,P5b.Y,P5b.Z));
	face.Add(Rvector3(P6b.X,P6b.Y,P6b.Z));
	face.Add(Rvector3(P6t.X,P6t.Y,P6t.Z));
	face.Add(Rvector3(P5t.X,P5t.Y,P5t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P5b.X,P5b.Y,P5b.Z));
	face.Add(Rvector3(P8b.X,P8b.Y,P8b.Z));
	face.Add(Rvector3(P8t.X,P8t.Y,P8t.Z));
	face.Add(Rvector3(P5t.X,P5t.Y,P5t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P7b.X,P7b.Y,P7b.Z));
	face.Add(Rvector3(P8b.X,P8b.Y,P8b.Z));
	face.Add(Rvector3(P8t.X,P8t.Y,P8t.Z));
	face.Add(Rvector3(P7t.X,P7t.Y,P7t.Z));
	facets.push_back(face);
	face = Facet();
	face.Add(Rvector3(P7b.X,P7b.Y,P7b.Z));
	face.Add(Rvector3(P6b.X,P6b.Y,P6b.Z));
	face.Add(Rvector3(P6t.X,P6t.Y,P6t.Z));
	face.Add(Rvector3(P7t.X,P7t.Y,P7t.Z));
	facets.push_back(face);

	rotateAxis.EvalExpressions();
	translateTo.EvalExpressions();

	RotateFacets(facets,rotateAxis.GetX(), rotateAxis.GetY(), rotateAxis.GetZ());
	TranslateFacets(facets,translateTo.GetX(), translateTo.GetY(), translateTo.GetZ());

	return facets;
}
void RectangularTube::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString coord1;
	wxString coord2;
	wxString cutAtBase;
	wxString cutAtTop;

	if (geometry.IsXOriented()) {
		coord1 = py;
		coord2 = pz;

		cutAtBase = "(" + geometry.GetBaseCutAtExpression() + ") + " + px;
		cutAtTop = "(" + geometry.GetTopCutAtExpression() + ") + " + px;
	} else if (geometry.IsYOriented()) {
		coord1 = px;
		coord2 = pz;

		cutAtBase = "(" + geometry.GetBaseCutAtExpression() + ") + " + py;
		cutAtTop = "(" + geometry.GetTopCutAtExpression() + ") + " + py;
	} else if (geometry.IsZOriented()) {
		coord1 = px;
		coord2 = py;

		cutAtBase = "(" + geometry.GetBaseCutAtExpression() + ") + " + pz;
		cutAtTop = "(" + geometry.GetTopCutAtExpression() + ") + " + pz;
	}

	geometry.SetBaseCoord1BeginExpression("(" + geometry.GetBaseCoord1BeginExpression() + ") + " + coord1);
	geometry.SetBaseCoord1EndExpression("(" + geometry.GetBaseCoord1EndExpression() + ") + " + coord1);
	geometry.SetBaseCoord2BeginExpression("(" + geometry.GetBaseCoord2BeginExpression() + ") + " + coord2);
	geometry.SetBaseCoord2EndExpression("(" + geometry.GetBaseCoord2EndExpression() + ") + " + coord2);
	geometry.SetTopCoord1BeginExpression("(" + geometry.GetTopCoord1BeginExpression() + ") + " + coord1);
	geometry.SetTopCoord1EndExpression("(" + geometry.GetTopCoord1EndExpression() + ") + " + coord1);
	geometry.SetTopCoord2BeginExpression("(" + geometry.GetTopCoord2BeginExpression() + ") + " + coord2);
	geometry.SetTopCoord2EndExpression("(" + geometry.GetTopCoord2EndExpression() + ") + " + coord2);

	geometry.SetBaseCutAtExpression(cutAtBase);
	geometry.SetTopCutAtExpression(cutAtTop);
}
