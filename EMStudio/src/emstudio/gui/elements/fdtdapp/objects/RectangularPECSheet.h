/*
 * RectangularSheet.h
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#ifndef PECSHEET_H_
#define PECSHEET_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/Object2DType.h"
#include "emstudio/dto/fdtdapp/RectangularPECSheetDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class RectangularPECSheet : public ElementsWithFacets {
private:
//	Material material;
//	ColourWrapper colour;
	BoolWrapper showSolid;
	BoolWrapper visible;
	SheetME sheet;
	MatchWithPML matchWithPML;

	void SortMinMax(double& min, double& max);
public:
	RectangularPECSheet();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool IsAllPropertiesTogetherValid();
	virtual void DoMove(Point3DME p);

	virtual ~RectangularPECSheet();
};

#endif /* PECSHEET_H_ */
