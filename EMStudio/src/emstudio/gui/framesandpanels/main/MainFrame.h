/*
 * MainFrame.h
 *
 *  Created on: 27/06/2012
 *      Author: Leandro
 */

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include <list>
#include <tr1/memory>
#include "wx/wx.h"
#include "wx/msgdlg.h"
#include "wx/grid.h"
#include "ContainerPanel.h"
#include "emstudio/util/file/FileManager.h"
#include "emstudio/util/dialogs/UtilDialog.h"
#include "emstudio/gui/framesandpanels/units/UnitFrame.h"
#include "emstudio/gui/basetypes/MaterialLibrary.h"
#include "emstudio/gui/elements/ElementManager.h"
#include "emstudio/units/Units.h"
#include "emstudio/gui/framesandpanels/materials/MaterialLibraryFrame.h"
#include "emstudio/gui/framesandpanels/symbols/SymbolsFrame.h"
#include "emstudio/gui/framesandpanels/materials/NewMaterialFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/RenderersAndEditorsManager.h"
#include "emstudio/gui/basetypes/Material.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "emstudio/gui/basetypes/AbsorvingBoundaryCondition.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "emstudio/gui/basetypes/Plane.h"
#include "emstudio/units/Units.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/MaterialRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/OrientationRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/PlaneRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/ABCRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/MaterialEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/OrientationEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/PlaneEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/ABCEditor.h"
#include "emstudio/core/EngineFactory.h"
#include "emstudio/gui/elements/types/MethodType.h"
#include "emstudio/dto/ElementDTO.h"
#include "emstudio/dto/fdtdapp/ElementsWithFacetsDTO.h"
#include "emstudio/gui/framesandpanels/results/ResultFrame.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/core/results/SimpleTextResult.h"
#include "emstudio/core/results/ResultManager.h"
#include "emstudio/core/results/TableResult.h"
#include "emstudio/core/results/SegmentInformationResult.h"
#include "emstudio/gui/framesandpanels/results/howtoshowresults/HowToShowResults.h"
#include "emstudio/gui/framesandpanels/results/howtoshowresults/HowToShowResultsManager.h"
#include "emstudio/gui/framesandpanels/results/howtoshowresults/HowToShowTableResult.h"
#include "emstudio/moderator/Moderator.h"

class Moderator;
class ContainerPanel;
class MainFrame : public wxFrame {
private:
	enum FileStatus {UPDATED, OUTDATED, NEW};
	int currentFileStatus;
	wxString currentFileName;

private:
	static int ID_UNITS;
	static int ID_MATERIALLIBRARY;
	static int ID_SYMBOLS;
	static int ID_START;
	static int ID_RESULTS;
	static int ID_CLONE;
    static int ID_CAM_AUTO;
    static int ID_CAM_XY;
    static int ID_CAM_YZ;
    static int ID_CAM_XZ;
    static int ID_CAM_MOVE;
    static int ID_CAM_ROTATE;
    static int ID_CAM_ZOOM;
    static int ID_ABOUT;

	Moderator* moderator;
	ContainerPanel* containerPanel;
	wxMenuBar* menuBar;

/////////////////////////////////////////////////////////////////////////
	// VEIO DO MODERATOR. ORGANIZAR DEPOIS
	ResultManager resultManager;
	ElementManagerSmartPointer availableElements;
	ElementManagerSmartPointer elementsInProject;
	RenderersAndEditorsManagerSmartPointer renderersAndEditorsManager;
	HowToShowResultsManagerSmartPointer howToShowResultsManager;

	UnitsSmartPointer units;
	MaterialLibrarySmartPointer materialLibrary;
	SymbolsMapSmartPointer symbolsMap;

	ResultTree resultTree;

	ResultManager BuildResultManager();
	ElementManagerSmartPointer BuildElementManager();
	virtual void RegisterAvailableElements();
	virtual void RegisterDefaultElementsInProject();
	RenderersAndEditorsManagerSmartPointer BuildRenderersAndEditorsManager();
	HowToShowResultsManagerSmartPointer BuildHowToShowResultsManager();
	void LoadMaterialLibrary();
	void BuildDefaultSymbolsMap();

    RenderersAndEditorsManagerSmartPointer GetRenderersAndEditorsManager();
    HowToShowResultsManagerSmartPointer GetHowToShowResultsManager();
    MaterialLibrarySmartPointer GetMaterialLibrary();
    SymbolsMapSmartPointer GetSymbolsMap();

/////////////////////////////////////////////////////////////////////////
	void InitializeMenuBar();
	void InitializeToolBar();
	void InitializeStatusBar();
	void ShowUnitsInStatusBar();

	void SetCameraMode(wxCommandEvent& event);
	void SetCameraMode(int id_cam_mode);
	void InitializeCameraMode();

	void SetFileStatus(int status, wxString fileName = "");

	void ConnectEvents();
	void NewProject(wxCommandEvent& event);
	void NewProject();
	void Save();
	void Save(wxString file, bool replaceExistingFile);
	void Save(wxCommandEvent& event);
	void SaveAs(wxCommandEvent& event);
	void Open(wxCommandEvent& event);
	void Quit(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void OpenUnitsFrame(wxCommandEvent& event);
	void OpenMaterialLibraryFrame(wxCommandEvent& event);
	void OpenSymbolsList(wxCommandEvent& event);
	void OpenAboutBox(wxCommandEvent& event);
	void StartSimulation(wxCommandEvent& event);
	void ShowResults(wxCommandEvent& event);
	void DeleteElement(wxCommandEvent& event);
	void CloneElement(wxCommandEvent& event);
	void Resize(wxSizeEvent& event);
	void AddMessage(wxString message);

	int AskToSave();
public:
	MainFrame(const wxString& title, Moderator* moderator);
	~MainFrame();

	virtual void Initialize();

	virtual wxString GetAppType() = 0;

    ElementManagerSmartPointer GetAvailableElements();
	ElementManagerSmartPointer GetElementsInProject();
    UnitsSmartPointer GetUnits();
    wxString GetProjectCode();
    ResultTree& GetResultTree();

	void Open(wxString fileName);
	void InformProjectHasChanged();

	void RebuildProjectTree();
};

#endif /* MAINFRAME_H_ */
