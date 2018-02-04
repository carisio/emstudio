///*
// * Cylinder.h
// *
// *  Created on: 29/09/2011
// *      Author: leandrocarisio
// */
//
//#ifndef CYLINDER_H_
//#define CYLINDER_H_
//
//#include "emstudio/gui/elements/EMStudioGUI.h"
//#include "gui/elements/Property.h"
//#include "emstudio/gui/elements/types/Object3DType.h"
//#include "gui/basetypes/BoolWrapper.h"
//#include "gui/basetypes/IntWrapper.h"
//#include "gui/basetypes/Point3DME.h"
//#include "emstudio/gui/basetypes/Material.h"
//#include "emstudio/dto/CylinderDTO.h"
//#include "gui/basetypes/MathExpressionParser.h"
//
//class Cylinder : public EMStudioGUI {
//private:
//	MathExpressionParser bottomRadius, topRadius, thickness;
//	Point3DME bottomCenter, topCenter;
//	BoolWrapper showSolid;
//	BoolWrapper visible;
//public:
//	Cylinder();
//
//    virtual ElementGUISmartPointer NewElementGUI();
//    virtual wxString GetRegisteredName();
//    virtual wxIcon GetIcon();
//    virtual ElementDTOSmartPointer NewElementDTO();
//    virtual void Draw(OpenGLStateMachine* opengl);
//    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
//
//    virtual vector<Facet> GetFacets();
//
//    virtual bool IsAllPropertiesTogetherValid();
//
//	virtual ~Cylinder();
//};
//
//#endif /* CYLINDER_H_ */
//
//
//
//
//
//
//
//
//
//
////#ifndef CYLINDER_H_
////#define CYLINDER_H_
////
////#include "emstudio/gui/elements/EMStudioGUI.h"
////#include "gui/elements/Property.h"
////#include "emstudio/gui/elements/types/Object3DType.h"
////#include "gui/basetypes/BoolWrapper.h"
////#include "gui/basetypes/IntWrapper.h"
////#include "gui/basetypes/Point3DME.h"
////#include "emstudio/gui/basetypes/Material.h"
////#include "emstudio/gui/basetypes/Orientation.h"
////#include "emstudio/dto/CylinderDTO.h"
////#include "gui/basetypes/MathExpressionParser.h"
////
////class Cylinder : public EMStudioGUI {
////private:
////	MathExpressionParser length, outerRadius, innerRadius;
////	Point3DME positionBottom;
////	Point3DME rotateAxis;
////	Point3DME translateTo;
////	Orientation orientation;
////	BoolWrapper showSolid;
////	BoolWrapper visible;
////
////	vector<Facet> GetFacets(double radius);
////	vector<Facet> GetInnerFacets();
////	vector<Facet> GetOuterFacets();
////public:
////	Cylinder();
////
////    virtual ElementGUISmartPointer NewElementGUI();
////    virtual wxString GetRegisteredName();
////    virtual wxIcon GetIcon();
////    virtual ElementDTOSmartPointer NewElementDTO();
////    virtual void Draw(OpenGLStateMachine* opengl);
////    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
////
////    virtual vector<Facet> GetFacets();
////
////    virtual bool IsAllPropertiesTogetherValid();
////
////	virtual ~Cylinder();
////};
////
////#endif /* CYLINDER_H_ */
