/*
 * FDTDMainFrame.h
 *
 *  Created on: 02/05/2014
 *      Author: leandrocarisio
 */

#ifndef FDTDMAINFRAME_H_
#define FDTDMAINFRAME_H_

#include "MainFrame.h"

#include "emstudio/moderator/Moderator.h"

#include "emstudio/gui/elements/ElementManager.h"
#include "emstudio/gui/elements/fdtdapp/objects/Box.h"
#include "emstudio/gui/elements/fdtdapp/objects/Cylinder.h"
#include "emstudio/gui/elements/fdtdapp/objects/Sphere.h"
#include "emstudio/gui/elements/fdtdapp/objects/RectangularTube.h"
#include "emstudio/gui/elements/fdtdapp/objects/CircularTube.h"
#include "emstudio/gui/elements/fdtdapp/objects/Helix.h"
#include "emstudio/gui/elements/fdtdapp/objects/Toroid.h"
#include "emstudio/gui/elements/fdtdapp/objects/ThinWire.h"
#include "emstudio/gui/elements/fdtdapp/objects/RectangularPECSheet.h"
#include "emstudio/gui/elements/fdtdapp/sources/DeltaGap.h"
#include "emstudio/gui/elements/fdtdapp/sources/Microstrip.h"
#include "emstudio/gui/elements/fdtdapp/sources/Monopole.h"
#include "emstudio/gui/elements/fdtdapp/sources/Dipole.h"
#include "emstudio/gui/elements/fdtdapp/sources/PlaneWave.h"
#include "emstudio/gui/elements/fdtdapp/methods/FDTD.h"
#include "emstudio/gui/elements/fdtdapp/probes/FieldAtPath.h"
#include "emstudio/gui/elements/fdtdapp/probes/FieldAtPoint.h"
#include "emstudio/gui/elements/fdtdapp/probes/RadiationPattern.h"

#include "wx/wx.h"

class FDTDMainFrame : public MainFrame {
private:
	virtual void RegisterAvailableElements();
	virtual void RegisterDefaultElementsInProject();

public:
	virtual wxString GetAppType();
	FDTDMainFrame(const wxString& title, Moderator* moderator);
	virtual ~FDTDMainFrame();
};

#endif /* FDTDMAINFRAME_H_ */
