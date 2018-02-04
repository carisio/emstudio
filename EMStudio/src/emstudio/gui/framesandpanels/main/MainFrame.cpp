/*
 * MainFrame.cpp
 *
 *  Created on: 27/06/2012
 *      Author: Leandro
 */

#include <emstudio/core/results/FieldAtPathResult.h>
#include <emstudio/core/results/FieldAtPlaneResult.h>
#include <emstudio/core/results/RadiationPatternResult.h>
#include <emstudio/gui/elements/ElementGUI.h>
#include <emstudio/gui/framesandpanels/main/AboutDialog.h>
#include <emstudio/gui/framesandpanels/main/InformProjectHasChangedCommand.h>
#include <emstudio/gui/framesandpanels/main/MainFrame.h>
#include <emstudio/gui/framesandpanels/main/visualizationpanel/BasicOpenGLStateMachine.h>
#include <emstudio/moderator/ConfigApp.h>
#include <emstudio/util/muparser/MathParser.h>
#include <emstudio/util/resources/UtilResource.h>
#include <stddef.h>
#include <wx/chartype.h>
#include <wx/containr.h>
#include <wx/defs.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/menu.h>
#include <wx/msw/bitmap.h>
#include <wx/msw/icon.h>
#include <wx/msw/menu.h>
#include <wx/msw/toolbar.h>
#include <wx/string.h>
#include <wx/tbarbase.h>
#include <wx/toolbar.h>
#include <wx/window.h>
#include <iostream>
#include <new>

int MainFrame::ID_UNITS = wxID_HIGHEST + 1;
int MainFrame::ID_MATERIALLIBRARY = wxID_HIGHEST + 2;
int MainFrame::ID_SYMBOLS = wxID_HIGHEST + 3;
int MainFrame::ID_START = wxID_HIGHEST + 4;
int MainFrame::ID_CLONE = wxID_HIGHEST + 5;
int MainFrame::ID_RESULTS = wxID_HIGHEST + 6;
int MainFrame::ID_CAM_AUTO = wxID_HIGHEST + 7;
int MainFrame::ID_CAM_XY = wxID_HIGHEST + 8;
int MainFrame::ID_CAM_YZ = wxID_HIGHEST + 9;
int MainFrame::ID_CAM_XZ = wxID_HIGHEST + 10;
int MainFrame::ID_CAM_MOVE = wxID_HIGHEST + 11;
int MainFrame::ID_CAM_ROTATE = wxID_HIGHEST + 12;
int MainFrame::ID_CAM_ZOOM = wxID_HIGHEST + 13;
int MainFrame::ID_ABOUT = wxID_HIGHEST + 14;

MainFrame::MainFrame(const wxString& title, Moderator* m)
	: wxFrame(NULL, wxID_ANY, title), moderator(m) {
}
MainFrame::~MainFrame() {

}
void MainFrame::Initialize() {
	LoadMaterialLibrary();
	BuildDefaultSymbolsMap();

	resultManager = BuildResultManager();
	availableElements = BuildElementManager();
	RegisterAvailableElements();
	elementsInProject = BuildElementManager();
	ElementGUI::SetElementsInProject(elementsInProject);

	renderersAndEditorsManager = BuildRenderersAndEditorsManager();
	howToShowResultsManager = BuildHowToShowResultsManager(); // Tem que ser criado após elementsInProject
	units = UnitsSmartPointer(new Units());
	resultTree = ResultTree();

	//	Cria o projeto com os elementos padrões
	RegisterDefaultElementsInProject();

	SetIcon(wxIcon("appicon", wxBITMAP_TYPE_ICO_RESOURCE));
	std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand(new InformProjectHasChangedCommand(this));

	containerPanel = new ContainerPanel(this, GetAvailableElements(), GetElementsInProject(), GetRenderersAndEditorsManager(), prjHasChangedCommand);

	SetFileStatus(NEW);

	ConnectEvents();

	InitializeMenuBar();
	InitializeToolBar();
	InitializeStatusBar();
	InitializeCameraMode();
}
void MainFrame::BuildDefaultSymbolsMap() {
	symbolsMap = SymbolsMapSmartPointer(new SymbolsMap);
	MathParser::SetSymbolsMap(symbolsMap);
}
void MainFrame::LoadMaterialLibrary() {
	materialLibrary = MaterialLibrarySmartPointer(new MaterialLibrary());
	FileManager::OpenMaterialLibrary(FileManager::GetMaterialLibraryFileName(), materialLibrary);
}
ResultManager MainFrame::BuildResultManager() {
	ResultManager rm;
	rm.AddResult(ResultSmartPointer(new SimpleTextResult));
	rm.AddResult(ResultSmartPointer(new TableResult));
	rm.AddResult(ResultSmartPointer(new RadiationPatternResult));
	rm.AddResult(ResultSmartPointer(new FieldAtPathResult));
	rm.AddResult(ResultSmartPointer(new FieldAtPlaneResult));
	rm.AddResult(ResultSmartPointer(new mom::SegmentInformationResult));

	return rm;
}
ElementManagerSmartPointer MainFrame::BuildElementManager() {
	ElementManagerSmartPointer em = ElementManagerSmartPointer(new ElementManager());
	return em;
}
void MainFrame::RegisterAvailableElements() {

}
void MainFrame::RegisterDefaultElementsInProject() {

}
RenderersAndEditorsManagerSmartPointer MainFrame::BuildRenderersAndEditorsManager() {
	Material::SetMaterialLibrary(GetMaterialLibrary());
	RenderersAndEditorsManagerSmartPointer rem = RenderersAndEditorsManagerSmartPointer(new RenderersAndEditorsManager());
	return rem;
}

HowToShowResultsManagerSmartPointer MainFrame::BuildHowToShowResultsManager() {
	HowToShowResultsManagerSmartPointer htsr = HowToShowResultsManagerSmartPointer(new HowToShowResultsManager(GetElementsInProject()));
	return htsr;
}

ElementManagerSmartPointer MainFrame::GetAvailableElements() {
    return availableElements;
}

MaterialLibrarySmartPointer MainFrame::GetMaterialLibrary() {
    return materialLibrary;
}
SymbolsMapSmartPointer MainFrame::GetSymbolsMap() {
	return symbolsMap;
}

wxString MainFrame::GetProjectCode() {
	// O código do projeto é formado apenas pelas informações que o caracterizam
	return FileManager::GetProjectCode(units, symbolsMap, elementsInProject);
}

ResultTree& MainFrame::GetResultTree() {
	return resultTree;
}

RenderersAndEditorsManagerSmartPointer MainFrame::GetRenderersAndEditorsManager() {
    return renderersAndEditorsManager;
}

HowToShowResultsManagerSmartPointer MainFrame::GetHowToShowResultsManager() {
	return howToShowResultsManager;
}

ElementManagerSmartPointer MainFrame::GetElementsInProject() {
    return elementsInProject;
}

UnitsSmartPointer MainFrame::GetUnits() {
	return units;
}
void MainFrame::ConnectEvents() {
	Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::NewProject));
	Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::Save));
	Connect(wxID_SAVEAS, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SaveAs));
	Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::Open));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::Quit));
	Connect(ID_UNITS, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::OpenUnitsFrame));
	Connect(ID_MATERIALLIBRARY, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::OpenMaterialLibraryFrame));
	Connect(ID_SYMBOLS, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::OpenSymbolsList));
	Connect(ID_START, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::StartSimulation));
	Connect(wxID_DELETE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::DeleteElement));
	Connect(ID_CLONE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::CloneElement));
	Connect(ID_RESULTS, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::ShowResults));
	Connect(ID_CAM_AUTO, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SetCameraMode));
	Connect(ID_CAM_XY, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SetCameraMode));
	Connect(ID_CAM_XZ, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SetCameraMode));
	Connect(ID_CAM_YZ, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SetCameraMode));
	Connect(ID_CAM_MOVE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SetCameraMode));
	Connect(ID_CAM_ROTATE, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SetCameraMode));
	Connect(ID_CAM_ZOOM, wxEVT_COMMAND_MENU_SELECTED,  wxCommandEventHandler(MainFrame::SetCameraMode));
	Connect(ID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OpenAboutBox));
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::OnClose));
	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(MainFrame::Resize));
}
void MainFrame::RebuildProjectTree() {
	containerPanel->RebuildProjectTree();
	ShowUnitsInStatusBar();
}
void MainFrame::InitializeStatusBar() {
	CreateStatusBar(2);
	ShowUnitsInStatusBar();
}
void MainFrame::ShowUnitsInStatusBar() {
	wxString space = GetUnits()->GetUserDefinedSpaceUnit().first;
	wxString time = GetUnits()->GetUserDefinedTimeUnit().first;
	wxString frequency = GetUnits()->GetUserDefinedFrequencyUnit().first;
	wxString text = wxT("Units: ");
	text.append(space).append(", ").append(time).append(", ").append(frequency);
	SetStatusText(text,1);
}
void MainFrame::InitializeMenuBar() {
	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW, wxT("&New\tCtrl-N"), wxT("New Project"));
	fileMenu->Append(wxID_OPEN, wxT("&Open\tCtrl-O"), wxT("Open Project"));
	fileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl-S"), wxT("Save Project"));
	fileMenu->Append(wxID_SAVEAS, wxT("Save &As\tF12"), wxT("Save Project As..."));
	fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit EM Studio"));

	wxMenu *configureMenu = new wxMenu;
	configureMenu->Append(ID_UNITS, wxT("&Units"), wxT("Configure default units"));
	configureMenu->Append(ID_MATERIALLIBRARY, wxT("&Material Library"), wxT("Configure material library"));
	configureMenu->Append(ID_SYMBOLS, wxT("&Symbols"), wxT("Configure symbols list"));

	wxMenu *simulateMenu = new wxMenu;
	simulateMenu->Append(ID_START, wxT("&Start"), wxT("Start simulation"));
	simulateMenu->Append(ID_RESULTS, wxT("&Results"), wxT("Show results"));

	wxMenu *aboutMenu = new wxMenu;
	aboutMenu->Append(ID_ABOUT, wxT("&About"), wxT("About"));

	menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("&File"));
	menuBar->Append(configureMenu, wxT("&Configure"));
	menuBar->Append(simulateMenu, wxT("&Simulate"));
	menuBar->Append(aboutMenu, wxT("&About"));

	SetMenuBar(menuBar);
}
void MainFrame::InitializeToolBar() {
	CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL | wxTB_TEXT);
//	CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
	wxToolBar* toolBar = GetToolBar();

	toolBar->AddTool(wxID_NEW, "New", UtilResource::GetBitmapFromIcon("new") , "New file");
	toolBar->AddTool(wxID_OPEN, "Open", UtilResource::GetIcon("open"), "Open file");
	toolBar->AddTool(wxID_SAVE, "Save", UtilResource::GetIcon("save"), "Save file");
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_DELETE, "Delete", UtilResource::GetIcon("delete"), "Delete element");
	toolBar->AddTool(ID_CLONE, "Clone", UtilResource::GetIcon("clone"), "Clone element");
	toolBar->AddSeparator();
	toolBar->AddTool(ID_UNITS, "Units", UtilResource::GetIcon("units"), "Configure units");
	toolBar->AddTool(ID_MATERIALLIBRARY, "Library", UtilResource::GetIcon("library"), "Open material library");
	toolBar->AddTool(ID_SYMBOLS, "Symbols", UtilResource::GetIcon("symbol"), "Open symbols list");
	toolBar->AddSeparator();
	toolBar->AddTool(ID_START, "Simulate", UtilResource::GetIcon("simulate"), "Start simulation");
	toolBar->AddTool(ID_RESULTS, "Results", UtilResource::GetIcon("results"), "Show results");
    toolBar->AddSeparator();
    toolBar->AddTool(ID_CAM_AUTO, "Auto", UtilResource::GetIcon("camauto"), "Camera - auto", wxITEM_CHECK);
    toolBar->AddTool(ID_CAM_XY, "XY", UtilResource::GetIcon("camxy"), "Camera - XY Plane", wxITEM_CHECK);
    toolBar->AddTool(ID_CAM_YZ, "YZ", UtilResource::GetIcon("camyz"), "Camera - YZ Plane", wxITEM_CHECK);
    toolBar->AddTool(ID_CAM_XZ, "XZ", UtilResource::GetIcon("camxz"), "Camera - XZ Plane", wxITEM_CHECK);
    toolBar->AddTool(ID_CAM_MOVE, "Move", UtilResource::GetIcon("move"), "Move Camera", wxITEM_CHECK);
    toolBar->AddTool(ID_CAM_ROTATE, "Rotate", UtilResource::GetIcon("rotate"), "Rotate Camera", wxITEM_CHECK);
    toolBar->AddTool(ID_CAM_ZOOM, "Zoom", UtilResource::GetIcon("zoom"), "Zoom", wxITEM_CHECK);


	toolBar->SetToolBitmapSize(wxSize(30, 30));
	toolBar->Realize();
}
void MainFrame::Resize(wxSizeEvent& event) {
	wxSize newSize = this->GetClientSize();
	containerPanel->SetSize(newSize);
}
void MainFrame::AddMessage(wxString message) {
	containerPanel->AddMessage(message);
}
void MainFrame::Quit(wxCommandEvent& event) {
	Close();
}

int MainFrame::AskToSave() {
	wxString message = "Save ";
	message.Append("'").Append(currentFileName).Append("'?");

	int question = UtilDialog::ShowYesNoCancelMessage("Please confirm", message);

	if (question == wxYES) {
		Save();
	}

	return question;
}
void MainFrame::OnClose(wxCloseEvent& event) {
	if ( event.CanVeto() && currentFileStatus != UPDATED) {

		int question = AskToSave();
		// Verifica se mandou salvar e deu erro
		if (question == wxYES && currentFileStatus != UPDATED) {
			event.Veto();
			return;
		} else if (question == wxCANCEL) {
			event.Veto();
			return;
		}

	}

	Destroy();  // you may also do:  event.Skip();
				// since the default event handler does call Destroy(), too
}

void MainFrame::Save(wxString fileName, bool replaceExistingFile) {
	try {
		// Check if user type a file
		if (fileName == FileManager::FILE_NOT_CHOOSEN) {
			return;
		}
		// Confirm if the file already exists. If not, exit
		while (!replaceExistingFile && FileManager::FileExists(fileName)) {
			int result = UtilDialog::ShowYesNoCancelMessage("File exists", "File already exists. Do you want to replace it?");
			cout << "result: " << result << "\t" << wxYES << "\t" << wxNO << "\t" << wxCANCEL << endl;
			if (result == wxCANCEL) {
				return;
				// If user cancel, exit
			} else if (result == wxYES) {
				// If user wants to replace, than force
				replaceExistingFile = true;
			} else if (result == wxNO) {
				// If user don't wants to replace, ask for a new fileName
				fileName = FileManager::ShowFileDialog(this, wxT("Save"), wxT("EM Studio files (*.emstudio)|*.emstudio"), wxFD_SAVE);
				if (fileName == FileManager::FILE_NOT_CHOOSEN) {
					return;
				}
			}
		}

		// User typed a file and wanted to save it anyway
		if (! FileManager::SaveProject(fileName, units, symbolsMap, elementsInProject, resultTree)) {
			wxString msg = "Unable to save file ";
			msg.Append(fileName);
			UtilDialog::ShowErrorMessage(msg);
		} else {
			SetFileStatus(UPDATED, fileName);
		}
	} catch (const std::exception& ex) {
		cout << ex.what() << endl;
	}
}
void MainFrame::Save() {
	wxString fileName = currentFileName;
	if (currentFileStatus == NEW) {
		fileName = FileManager::ShowFileDialog(this, wxT("Save"), wxT("EM Studio files (*.emstudio)|*.emstudio"), wxFD_SAVE);
		Refresh(true);
		Update();
	}

	Save(fileName, !(currentFileStatus == NEW));
}
void MainFrame::Save(wxCommandEvent& event) {
	Save();
}
void MainFrame::SaveAs(wxCommandEvent& event) {
	wxString fileName = FileManager::ShowFileDialog(this, wxT("Save"), wxT("EM Studio files (*.emstudio)|*.emstudio"), wxFD_SAVE);
	Refresh(true);
	Update();
	Save(fileName, false);
}
void MainFrame::Open(wxString fileName) {
	if (fileName != FileManager::FILE_NOT_CHOOSEN) {
		Refresh(true);
		Update();
		wxString errorMessage;

		if (FileManager::LoadProject(fileName, units, symbolsMap, availableElements, elementsInProject, resultTree, resultManager, errorMessage)) {

			RebuildProjectTree();
			Refresh();

			InitializeCameraMode();
			SetFileStatus(UPDATED, fileName);
		} else {
			wxString msg = "Unable to open file ";
			msg.Append(fileName);
			msg.Append(".\n");
			msg.Append(errorMessage);
			UtilDialog::ShowErrorMessage(msg);
			// Se deu pau abrindo um projeto, então cria um novo:
			SetFileStatus(UPDATED); // Seta como update apenas para não perguntar de novo...
			NewProject();
		}
	}
}
void MainFrame::Open(wxCommandEvent& event) {
	if (currentFileStatus != UPDATED) {

		int question = AskToSave();
		// Verifica se mandou salvar e deu erro
		if (question == wxYES && currentFileStatus != UPDATED) {
			return;
		} else if (question == wxCANCEL) {
			return;
		}

	}

	// Se chegou aqui, é porque o usuário não quis salvar antes de abrir novo projeto
	wxString fileName = FileManager::ShowFileDialog(this, wxT("Open"), wxT("EM Studio files (*.emstudio)|*.emstudio"), wxFD_OPEN);
	Open(fileName);
}
void MainFrame::NewProject(wxCommandEvent& event) {
	NewProject();
}
void MainFrame::NewProject() {
	if (currentFileStatus != UPDATED) {

		int question = AskToSave();
		// Verifica se mandou salvar e deu erro
		if (question == wxYES && currentFileStatus != UPDATED) {
			return;
		} else if (question == wxCANCEL) {
			return;
		}

	}

	// Se chegou aqui, é porque o usuário não quis salvar antes de abrir novo projeto
	resultTree.ClearResults();
	symbolsMap->ClearMap();
	units->SetDefaultUnits();
	elementsInProject->Clear();
	//	Cria o projeto com os elementos padrões
	RegisterDefaultElementsInProject();

	RebuildProjectTree();
	Refresh();
	InitializeCameraMode();
	SetFileStatus(NEW);
}
void MainFrame::StartSimulation(wxCommandEvent& event) {
	InformProjectHasChanged();
	try {
		resultTree = moderator->StartSimulation();
		cout << "OK, pegou resultados do moderator" << endl;
	} catch(std::bad_alloc& ba) {
		UtilDialog::ShowErrorMessage("Not enough memory to simulate the projet!", "Out of memory");
	} catch (const std::exception& ex) {
		cout << ex.what() << endl;
	} catch (...) {
		cout << "Deu algum tipo de pau aqui" << endl;
	}
}
void MainFrame::ShowResults(wxCommandEvent& event) {
	// Verifica se o projeto se refere ao resultados. Se não se referir, pergunta se quer exibir os resultados mesmo assim.
	wxString prjCodeResult = GetResultTree().GetProjectCode();
	cout << "Código do projeto salvo na árvore de rsultados " << prjCodeResult << endl;
	if (prjCodeResult != "" && prjCodeResult != GetProjectCode()) {
		int question = UtilDialog::ShowYesNoMessage("Results don't match the project", "Results don't match the project. Show anyway?");

		if (question == wxID_NO) {
			return;
		}
	}

	if (GetResultTree().GetEngineResults().empty()) {
		UtilDialog::ShowInfoMessage("There are no results!", "No results found");
		return;
	}
	ResultFrame* resultFrame = new ResultFrame(this, GetResultTree(), GetAvailableElements(), GetHowToShowResultsManager());

	resultFrame->ShowModal();

	if (resultFrame->GetReturnCode() == wxID_CANCEL || resultFrame->GetReturnCode() == wxID_OK) {
		resultFrame->Destroy();
	}
}
void MainFrame::DeleteElement(wxCommandEvent& event) {
	containerPanel->DeleteSelectedElement();
}
void MainFrame::CloneElement(wxCommandEvent& event) {
	containerPanel->CloneSelectedElement();
}
void MainFrame::OpenUnitsFrame(wxCommandEvent& event) {
	UnitFrame* uf = new UnitFrame(this, GetUnits());
	uf->ShowModal();

	if (uf->GetReturnCode() == wxID_OK) {
		SetFileStatus(OUTDATED);
	}
	if (uf->GetReturnCode() == wxID_CANCEL || uf->GetReturnCode() == wxID_OK) {
		uf->Destroy();
		ShowUnitsInStatusBar();
	}
}
void MainFrame::OpenSymbolsList(wxCommandEvent& event) {
	SymbolsFrame* symFrame = new SymbolsFrame(this, GetSymbolsMap(), GetElementsInProject());
	if (symFrame->ShowModal() == wxID_CANCEL) {
		symFrame->Destroy();
	}
	symFrame->SetFocus();

	// Redesenha. Se o usuário tiver redefinido propriedades, o projeto pode ter mudado.
	GetElementsInProject()->InvalidateAllElements();
	containerPanel->Refresh(true);
	containerPanel->Update();
}
void MainFrame::OpenAboutBox(wxCommandEvent& event) {
	AboutDialog aboutDialog(wxID_ANY);
	aboutDialog.ShowModal();
}
void MainFrame::OpenMaterialLibraryFrame(wxCommandEvent& event) {
	MaterialLibraryFrame* mlf = new MaterialLibraryFrame(this, GetMaterialLibrary());
	if (mlf->ShowModal() == wxID_CANCEL) {
		mlf->Destroy();
	}
	mlf->SetFocus();

	// Redesenha. Pode ser que a cor do material tenha mudado na biblioteca.
	containerPanel->Refresh(true);
	containerPanel->Update();
}

void MainFrame::InitializeCameraMode() {
	SetCameraMode(ID_CAM_AUTO);
}

void MainFrame::SetFileStatus(int status, wxString fileName) {
	wxString title = "EM Studio [" + AppType + "] - ";

	if (status == NEW) {
		currentFileStatus = status;
		currentFileName = "Untitled";

		title.Append(currentFileName).Append(" [*]");
	} else if (status == UPDATED) {
		currentFileStatus = status;
		currentFileName = fileName;

		title.Append(currentFileName);
	} else if (status == OUTDATED) {
		if (currentFileStatus != NEW)
			currentFileStatus = status;

		title.Append(currentFileName).Append(" [*]");
	}
	SetTitle(title);
}
void MainFrame::InformProjectHasChanged() {
	SetFileStatus(OUTDATED);
	elementsInProject->InformProjectChanged();
}
void MainFrame::SetCameraMode(int id_cam_mode) {
	wxToolBar* toolBar = GetToolBar();
	toolBar->ToggleTool(ID_CAM_AUTO, false);
	toolBar->ToggleTool(ID_CAM_XY, false);
	toolBar->ToggleTool(ID_CAM_YZ, false);
	toolBar->ToggleTool(ID_CAM_XZ, false);
	toolBar->ToggleTool(ID_CAM_MOVE, false);
	toolBar->ToggleTool(ID_CAM_ROTATE, false);
	toolBar->ToggleTool(ID_CAM_ZOOM, false);

	if (id_cam_mode == ID_CAM_AUTO) {
		toolBar->ToggleTool(ID_CAM_AUTO, true);
		containerPanel->SetCameraMode(CAM_AUTO);
	} else if (id_cam_mode == ID_CAM_XY) {
		toolBar->ToggleTool(ID_CAM_XY, true);
		containerPanel->SetCameraMode(CAM_XY);
	} else if (id_cam_mode == ID_CAM_YZ) {
		toolBar->ToggleTool(ID_CAM_YZ, true);
		containerPanel->SetCameraMode(CAM_YZ);
	} else if (id_cam_mode == ID_CAM_XZ) {
		toolBar->ToggleTool(ID_CAM_XZ, true);
		containerPanel->SetCameraMode(CAM_XZ);
	} else if (id_cam_mode == ID_CAM_MOVE) {
		toolBar->ToggleTool(ID_CAM_MOVE, true);
		containerPanel->EnableCameraMove();
	} else if (id_cam_mode == ID_CAM_ROTATE) {
		toolBar->ToggleTool(ID_CAM_ROTATE, true);
		containerPanel->EnableCameraRotate();
	} else if (id_cam_mode == ID_CAM_ZOOM) {
		toolBar->ToggleTool(ID_CAM_ZOOM, true);
		containerPanel->EnableCameraZoom();
	}
}
void MainFrame::SetCameraMode(wxCommandEvent& event) {
	SetCameraMode(event.GetId());
}
