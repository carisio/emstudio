/*
 * Moderator.h
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */
#ifndef MODERATOR_H_
#define MODERATOR_H_


#include "emstudio/gui/framesandpanels/main/ContainerPanel.h"
#include "emstudio/gui/framesandpanels/units/UnitFrame.h"
#include "emstudio/gui/framesandpanels/materials/MaterialLibraryFrame.h"
#include "emstudio/gui/framesandpanels/materials/NewMaterialFrame.h"
#include "emstudio/gui/framesandpanels/main/MainFrame.h"

#include "emstudio/gui/basetypes/MaterialLibrary.h"

#include "emstudio/gui/elements/types/MethodType.h"
#include "emstudio/gui/elements/ElementManager.h"
#include "emstudio/gui/elements/fdtdapp/objects/Box.h"
#include "emstudio/gui/elements/fdtdapp/objects/DXFObject.h"
#include "emstudio/gui/elements/fdtdapp/objects/Sphere.h"
#include "emstudio/gui/elements/fdtdapp/objects/RectangularTube.h"
#include "emstudio/gui/elements/fdtdapp/objects/CircularTube.h"
#include "emstudio/gui/elements/fdtdapp/objects/Helix.h"
#include "emstudio/gui/elements/fdtdapp/objects/Toroid.h"
#include "emstudio/gui/elements/fdtdapp/objects/ThinWire.h"
#include "emstudio/gui/elements/fdtdapp/objects/CircularPECSheet.h"
#include "emstudio/gui/elements/fdtdapp/objects/RectangularPECSheet.h"
#include "emstudio/gui/elements/fdtdapp/objects/GenericPECSheet.h"
#include "emstudio/gui/elements/fdtdapp/sources/DeltaGap.h"
#include "emstudio/gui/elements/fdtdapp/sources/Microstrip.h"
#include "emstudio/gui/elements/fdtdapp/sources/Monopole.h"
#include "emstudio/gui/elements/fdtdapp/sources/Dipole.h"
#include "emstudio/gui/elements/fdtdapp/sources/PlaneWave.h"
#include "emstudio/gui/elements/fdtdapp/methods/FDTD.h"
#include "emstudio/gui/elements/fdtdapp/probes/FieldAtPath.h"
#include "emstudio/gui/elements/fdtdapp/probes/FieldAtPoint.h"
#include "emstudio/gui/elements/fdtdapp/probes/FieldAtPlane.h"
#include "emstudio/gui/elements/fdtdapp/probes/RadiationPattern.h"

#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/RenderersAndEditorsManager.h"

#include "emstudio/gui/basetypes/Material.h"

#include "emstudio/util/file/FileManager.h"
#include "emstudio/util/dialogs/UtilDialog.h"
#include "emstudio/util/muparser/MathParser.h"

#include "emstudio/units/Units.h"

#include "emstudio/core/EngineFactory.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/core/results/ResultManager.h"
#include "emstudio/core/results/TableResult.h"

#include "emstudio/core/results/RadiationPatternResult.h"
#include "emstudio/core/results/FieldAtPlaneResult.h"
#include "emstudio/core/results/FieldAtPathResult.h"

#include "emstudio/dto/ElementDTO.h"
#include "emstudio/dto/fdtdapp/ElementsWithFacetsDTO.h"

#include "wx/wx.h"
#include "wx/msgdlg.h"
#include "wx/grid.h"
#include "wx/intl.h"
#include "wx/cmdline.h"

#include <list>
#include <tr1/memory>

using namespace::std;

class MainFrame;

class Moderator : public wxApp {
private:
	static const wxCmdLineEntryDesc cmdLineDesc[];
	typedef list<ElementDTOSmartPointer> EMStudioDTOList;

	wxLocale locale;

//	ResultManager resultManager;
//	ElementManagerSmartPointer availableElements;
//	ElementManagerSmartPointer elementsInProject;
//	RenderersAndEditorsManagerSmartPointer renderersAndEditorsManager;
//	HowToShowResultsManagerSmartPointer howToShowResultsManager;
//
//	UnitsSmartPointer units;
//	MaterialLibrarySmartPointer materialLibrary;
//	SymbolsMapSmartPointer symbolsMap;
//
//	ResultTree resultTree;

	MainFrame* frame;
//	ResultManager BuildResultManager();
//	ElementManagerSmartPointer BuildElementManager();
//	RenderersAndEditorsManagerSmartPointer BuildRenderersAndEditorsManager();
//	HowToShowResultsManagerSmartPointer BuildHowToShowResultsManager();
//	void LoadMaterialLibrary();
//	void BuildDefaultSymbolsMap();

	void UnnormalizeDTO(ElementDTOSmartPointer element);
	EMStudioDTOList GetUnnormalizedElementDTOList();
public:
	Moderator();

	~Moderator();
	virtual bool OnInit();

	/* Simulation */
	ResultTree StartSimulation();

//	void RepaintWindow();

//	ElementManagerSmartPointer GetAvailableElements();
//	ElementManagerSmartPointer GetElementsInProject();
//    UnitsSmartPointer GetUnits();
//
//    RenderersAndEditorsManagerSmartPointer GetRenderersAndEditorsManager();
//    HowToShowResultsManagerSmartPointer GetHowToShowResultsManager();
//    MaterialLibrarySmartPointer GetMaterialLibrary();
//    SymbolsMapSmartPointer GetSymbolsMap();
//
//    wxString GetProjectCode();
//
//    ResultTree& GetResultTree();
};

#endif /* MODERATOR_H_ */
