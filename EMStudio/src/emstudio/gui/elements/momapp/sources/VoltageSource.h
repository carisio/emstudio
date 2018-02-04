/*
 * VoltageSource.h
 *
 *  Created on: 02/06/2014
 *      Author: leandrocarisio
 */

#ifndef VOLTAGESOURCE_H_
#define VOLTAGESOURCE_H_

#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/SourceType.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

namespace mom {


class VoltageSource : public ElementsWithSegments {
private:
	ColourWrapper colour;
	MathExpressionParser realPart, imagPart;
	Point3DME position;

	Segment s;
	bool draw;
public:
	VoltageSource();
	virtual ~VoltageSource();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();
    virtual void DoMove(Point3DME p);
	virtual void Draw(OpenGLStateMachine* opengl);
	virtual void ProjectChanged();

	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual bool IsAllPropertiesTogetherValid();
};

} /* namespace mom */
#endif /* VOLTAGESOURCE_H_ */
