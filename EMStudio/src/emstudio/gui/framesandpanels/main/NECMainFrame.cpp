/*
 * NECMainFrame.cpp
 *
 *  Created on: 02/05/2014
 *      Author: leandrocarisio
 */

#include "NECMainFrame.h"

#include "emstudio/gui/elements/momapp/methods/MoM.h"

#include "emstudio/gui/elements/momapp/wires/Wire.h"
#include "emstudio/gui/elements/momapp/wires/Helix.h"
#include "emstudio/gui/elements/momapp/wires/WireSphere.h"
#include "emstudio/gui/elements/momapp/connections/TransmissionLine.h"

#include "emstudio/gui/elements/momapp/sources/VoltageSource.h"

#include "emstudio/gui/elements/momapp/probes/Currents.h"
#include "emstudio/gui/elements/momapp/probes/ChargeDensities.h"
#include "emstudio/gui/elements/momapp/probes/RadiationPattern.h"

NECMainFrame::NECMainFrame(const wxString& title, Moderator* moderator)
	: MainFrame(title, moderator) {

}

NECMainFrame::~NECMainFrame() {
}

void NECMainFrame::RegisterAvailableElements() {
	ElementManagerSmartPointer em = GetAvailableElements();

	em->RegisterElement(ElementGUISmartPointer(new mom::MoM()));

	em->RegisterElement(ElementGUISmartPointer(new mom::Wire()));
	em->RegisterElement(ElementGUISmartPointer(new mom::WireSphere()));
//	em->RegisterElement(ElementGUISmartPointer(new mom::Helix()));
	em->RegisterElement(ElementGUISmartPointer(new mom::TransmissionLine()));

	em->RegisterElement(ElementGUISmartPointer(new mom::VoltageSource()));

	em->RegisterElement(ElementGUISmartPointer(new mom::Currents()));
	em->RegisterElement(ElementGUISmartPointer(new mom::ChargeDensities()));
	em->RegisterElement(ElementGUISmartPointer(new mom::RadiationPattern()));
}


void NECMainFrame::RegisterDefaultElementsInProject() {
	GetElementsInProject()->RegisterElement(ElementGUISmartPointer(new mom::MoM()));
}

wxString NECMainFrame::GetAppType() {
	 return "MoM";
 }
