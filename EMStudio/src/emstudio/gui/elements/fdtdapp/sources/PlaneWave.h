/*
 * PlaneWave.h
 *
 *  Created on: 25/08/2011
 *      Author: Leandro
 */

#ifndef PLANEWAVE_H_
#define PLANEWAVE_H_

#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/types/SourceType.h"
#include "emstudio/dto/fdtdapp/PlaneWaveDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class PlaneWave : public ElementsWithFacets {
private:
	Point3DME lowerBoundary, upperBoundary;
	ExcitationME excitation;
//	BoolWrapper hardSource;
	BoolWrapper visible;
	ColourWrapper colour;
	DirectionPlaneWaveME direction;
public:
	PlaneWave();
	virtual ~PlaneWave();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

    virtual bool IsAllPropertiesTogetherValid();
};

#endif /* PLANEWAVE_H_ */
