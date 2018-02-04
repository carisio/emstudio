/*
 * DXFObject.h
 *
 *  Created on: 09/05/2013
 *      Author: leandrocarisio
 */

#ifndef DXFOBJECT_H_
#define DXFOBJECT_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object3DType.h"
#include "emstudio/dto/fdtdapp/DXFObjectDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class DXFObject : public ElementsWithFacets {
private:
	DXFFile file;
	DXFParser parser;

	BoolWrapper normalize;
	MathExpressionParser scaleFactor;
	Point3DME translateTo;
	Point3DME rotateAxis;
	BoolWrapper solid;
	BoolWrapper visible;
//	DXFRenderer renderer;

	/* Dados para translação, rotação, normalização e escala */
	double oldTx, oldTy, oldTz;
	bool oldNormalize;
	double oldRx, oldRy, oldRz;
	double oldScale;
public:
	DXFObject();
	virtual ~DXFObject();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();

    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

    virtual vector<Facet> BuildFacets();

    virtual bool IsAllPropertiesTogetherValid();
};

#endif /* DXFOBJECT_H_ */
