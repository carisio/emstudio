/*
 * FDTDMainFrame.cpp
 *
 *  Created on: 02/05/2014
 *      Author: leandrocarisio
 */

#include "FDTDMainFrame.h"

FDTDMainFrame::FDTDMainFrame(const wxString& title, Moderator* moderator)
	: MainFrame(title, moderator) {

}

FDTDMainFrame::~FDTDMainFrame() {
}

void FDTDMainFrame::RegisterAvailableElements() {
	ElementManagerSmartPointer em = GetAvailableElements();

	// 2D Objects
	em->RegisterElement(ElementGUISmartPointer(new CircularPECSheet()));
	em->RegisterElement(ElementGUISmartPointer(new GenericPECSheet()));
	em->RegisterElement(ElementGUISmartPointer(new RectangularPECSheet()));

	// 3D Objects
	em->RegisterElement(ElementGUISmartPointer(new Box()));
	em->RegisterElement(ElementGUISmartPointer(new CircularTube()));
	em->RegisterElement(ElementGUISmartPointer(new DXFObject()));
	em->RegisterElement(ElementGUISmartPointer(new fdtd::Helix()));
	em->RegisterElement(ElementGUISmartPointer(new Toroid()));
	em->RegisterElement(ElementGUISmartPointer(new RectangularTube()));
	em->RegisterElement(ElementGUISmartPointer(new Sphere()));
	em->RegisterElement(ElementGUISmartPointer(new ThinWire()));

	// Sources
	em->RegisterElement(ElementGUISmartPointer(new DeltaGap()));
	em->RegisterElement(ElementGUISmartPointer(new Dipole()));
	em->RegisterElement(ElementGUISmartPointer(new Microstrip()));
	em->RegisterElement(ElementGUISmartPointer(new Monopole()));
	em->RegisterElement(ElementGUISmartPointer(new PlaneWave()));

	// Methods
	em->RegisterElement(ElementGUISmartPointer(new FDTD()));

	// Probes
	em->RegisterElement(ElementGUISmartPointer(new FieldAtPath()));
	em->RegisterElement(ElementGUISmartPointer(new FieldAtPlane()));
	em->RegisterElement(ElementGUISmartPointer(new FieldAtPoint()));
	em->RegisterElement(ElementGUISmartPointer(new RadiationPattern()));
}

 void FDTDMainFrame::RegisterDefaultElementsInProject() {
	 GetElementsInProject()->RegisterElement(ElementGUISmartPointer(new FDTD()));
}

wxString FDTDMainFrame::GetAppType() {
	 return "FDTD";
 }
