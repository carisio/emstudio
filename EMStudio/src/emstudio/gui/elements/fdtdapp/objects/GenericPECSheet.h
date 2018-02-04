/*
 * GenericPECSheet.h
 *
 *  Created on: 16/04/2013
 *      Author: Leandro
 */

#ifndef GENERICPECSHEET_H_
#define GENERICPECSHEET_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object2DType.h"
#include "emstudio/dto/fdtdapp/GenericPECSheetDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class GenericPECSheet : public ElementsWithFacets {
private:
//	ColourWrapper colour;
	BoolWrapper showSolid;
	BoolWrapper visible;
	GenericSheetME sheet;
//	MatchWithPML matchWithPML;

public:
	GenericPECSheet();
	virtual ~GenericPECSheet();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsAllPropertiesTogetherValid();
	virtual void DoMove(Point3DME p);
};

#endif /* GENERICPECSHEET_H_ */
