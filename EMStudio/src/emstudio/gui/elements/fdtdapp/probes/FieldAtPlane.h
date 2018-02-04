/*
 * FieldAtPlane.h
 *
 *  Created on: 13/03/2013
 *      Author: leandrocarisio
 */

#ifndef FIELDATPLANE_H_
#define FIELDATPLANE_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/ProbeType.h"
#include "emstudio/dto/fdtdapp/FieldAtPlaneDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

#include "emstudio/util/resources/UtilResource.h"

class FieldAtPlane : public ElementsWithFacets {
private:
	SelectField selectedField;
	ColourWrapper colour;
	BoolWrapper visible;
	SheetME dimensions;
	IntMathExpressionParser snapshootNumber;

	void SortMinMax(double& min, double& max);
public:
	FieldAtPlane();
	virtual ~FieldAtPlane();

	virtual ElementGUISmartPointer NewElementGUI();
	virtual wxString GetRegisteredName();
	virtual wxIcon GetIcon();
	virtual ElementDTOSmartPointer NewElementDTO();
	virtual void Draw(OpenGLStateMachine* opengl);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);
};

#endif /* FIELDATPLANE_H_ */
