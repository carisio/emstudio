/*
 * ElementsWithSegments.h
 *
 *  Created on: 28/05/2014
 *      Author: leandrocarisio
 */

#ifndef ELEMENTSWITHSEGMENTS_H_
#define ELEMENTSWITHSEGMENTS_H_

#include "../ElementGUI.h"
#include "../ElementType.h"
#include "emstudio/util/nec/Segment.h"
#include "emstudio/gui/basetypes/BoolWrapper.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"
#include "wx/wx.h"

namespace mom {

class ElementsWithSegments : public ElementGUI {
private:
	BoolWrapper visible;
	BoolWrapper solid;
	Segments segments;
public:
	ElementsWithSegments(ElementTypeSmartPointer type);
	virtual ~ElementsWithSegments();

	Segments& GetSegments();
	virtual Segments BuildSegments();
	void SetSegments(Segments s);
	bool HasSegments();
	Segment FindClosestSegment(double x, double y, double z, double& d2center);
	bool FindClosestSegmentInAllElements(double x, double y, double z, Segment& s, double& d);

	void AddVisibleProperty(wxString propertyName = "Visible?", bool visible = true);
	void AddSolidProperty(wxString propertyName = "Solid?", bool solid = true);
	bool IsVisible();
	bool IsSolid();

	wxColour GetPECColor();
	virtual wxColour GetSegmentsColor();
	virtual void Draw(OpenGLStateMachine* opengl);

	virtual void DoPopulateDTO(ElementDTOSmartPointer p);

	bool GetProjectBoundary(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	void FillApproximateDimensionsWithSegments(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
};

}

#endif /* ELEMENTSWITHSEGMENTS_H_ */
