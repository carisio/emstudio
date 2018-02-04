/*
 * TransmissionLine.h
 *
 *  Created on: 05/06/2014
 *      Author: leandrocarisio
 */

#ifndef TRANSMISSIONLINE_H_
#define TRANSMISSIONLINE_H_


#include "emstudio/gui/elements/momapp/ElementsWithSegments.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/ConnectionType.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

namespace mom {

class TransmissionLine : public ElementsWithSegments {
private:
	Point3DME port1, port2;
	MathExpressionParser impedance, length;
	MathExpressionParser admittanceRealPort1, admittanceImagPort1;
	MathExpressionParser admittanceRealPort2, admittanceImagPort2;
	BoolWrapper crossedLine;
	ColourWrapper colour;

	Segment s1, s2;
	bool draw;
public:
	TransmissionLine();
	virtual ~TransmissionLine();

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
#endif /* TRANSMISSIONLINE_H_ */
