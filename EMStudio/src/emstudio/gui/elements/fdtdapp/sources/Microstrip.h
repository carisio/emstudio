/*
 * GeneralSource.h
 *
 *  Created on: 05/10/2011
 *      Author: Leandro
 */

#ifndef MICROSTRIP_H_
#define MICROSTRIP_H_

#include "emstudio/gui/elements/fdtdapp/ElementsWithFacets.h"
#include "emstudio/gui/elements/Property.h"
#include "emstudio/gui/elements/types/SourceType.h"
#include "emstudio/dto/fdtdapp/MicrostripDTO.h"

#include "emstudio/includes/basetypes.h"
#include "emstudio/includes/basetypevalidators.h"

class Microstrip : public ElementsWithFacets {
private:
	Point3DME lowerBoundary, upperBoundary;
//	ColourWrapper substrateColor;
//	ColourWrapper pecColor;
	MathExpressionParser linePosition, lineWidth, lineLength;
	BoolWrapper showSolid;
	BoolWrapper pecUnderSubstrate;
	BoolWrapper visible;

	ExcitationME excitation;
	IntWrapper linePoints;
	IntWrapper sourcePoint;
	MathExpressionParser lineImpedance;
	BoolWrapper hardSource;
	MathExpressionParser initialFrequency;
	MathExpressionParser frequencyStep;
	IntMathExpressionParser nFrequency;

	MicrostripXYPortsME ports;

	MatchWithPML matchWithPML;
public:
	Microstrip();

    virtual ElementGUISmartPointer NewElementGUI();
    virtual wxString GetRegisteredName();
    virtual wxIcon GetIcon();
    virtual ElementDTOSmartPointer NewElementDTO();

    virtual void Draw(OpenGLStateMachine* opengl);
    virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
    virtual void DoMove(Point3DME p);

    virtual vector<Facet> BuildFacets();

    virtual bool IsAllPropertiesTogetherValid();

	virtual ~Microstrip();
};

#endif /* MICROSTRIP_H_ */
