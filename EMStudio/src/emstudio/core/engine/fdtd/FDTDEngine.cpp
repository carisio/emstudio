/*
 * FDTDEngine.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "FDTDEngine.h"
#include "emstudio/dto/fdtdapp/ElementsWithFacetsDTO.h"

#include "emstudio/core/engine/fdtd/elementcore/FDTDElementCore.h"
#include "emstudio/dto/fdtdapp/ThinWireDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/ThinWireFDTDCore.h"
#include "emstudio/dto/fdtdapp/DeltaGapDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/DeltaGapFDTDCore.h"
#include "emstudio/dto/fdtdapp/DipoleDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/DipoleFDTDCore.h"
#include "emstudio/dto/fdtdapp/MonopoleDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/MonopoleFDTDCore.h"
#include "emstudio/dto/fdtdapp/PlaneWaveDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/PlaneWaveFDTDCore.h"
#include "emstudio/dto/fdtdapp/RectangularPECSheetDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/RectangularPECSheetFDTDCore.h"
#include "emstudio/dto/fdtdapp/BoxDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/BoxFDTDCore.h"
#include "emstudio/dto/fdtdapp/MicrostripDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/MicrostripFDTDCore.h"
#include "emstudio/dto/fdtdapp/FieldAtPointDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/FieldAtPointFDTDCore.h"
#include "emstudio/dto/fdtdapp/CylinderDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/CylinderFDTDCore.h"
#include "emstudio/dto/fdtdapp/CircularTubeDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/CircularTubeFDTDCore.h"
#include "emstudio/dto/fdtdapp/SphereDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/SphereFDTDCore.h"
#include "emstudio/dto/fdtdapp/RadiationPatternDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/RadiationPatternFDTDCore.h"
#include "emstudio/dto/fdtdapp/FieldAtPathDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/FieldAtPathFDTDCore.h"
#include "emstudio/dto/fdtdapp/FieldAtPlaneDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/FieldAtPlaneFDTDCore.h"
#include "emstudio/dto/fdtdapp/HelixDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/HelixFDTDCore.h"
#include "emstudio/dto/fdtdapp/RectangularTubeDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/RectangularTubeFDTDCore.h"
#include "emstudio/dto/fdtdapp/ToroidDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/ToroidFDTDCore.h"
#include "emstudio/dto/fdtdapp/GenericPECSheetDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/GenericPECSheetFDTDCore.h"
#include "emstudio/dto/fdtdapp/GenericPECSheetsDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/GenericPECSheetsFDTDCore.h"
#include "emstudio/dto/fdtdapp/DXFObjectDTO.h"
#include "emstudio/core/engine/fdtd/elementcore/DXFObjectFDTDCore.h"
#include "wx/wx.h"

#include <iostream>
using std::cout;
using std::endl;

/* Função usada para ordenar a lista de projeto de acordo com a prioridade */
bool compareElementCoreSmartPointer(ElementCoreSmartPointer first, ElementCoreSmartPointer second) {
	int firstPriority = (static_cast<ElementsWithFacetsDTO*>(first->GetDTO().get()))->GetPriority().GetValue();
	int secondPriority = (static_cast<ElementsWithFacetsDTO*>(second->GetDTO().get()))->GetPriority().GetValue();
	return firstPriority < secondPriority;
}


FDTDEngine::FDTDEngine(ElementDTOSmartPointer dtosmartptr, InformSimulationStatusSmartPointer status) :
		Engine(dtosmartptr, status),
		dto(*(static_cast<FDTDDTO*>(dtosmartptr.get()))), grid(*(static_cast<FDTDDTO*>(dtosmartptr.get()))), mesh(vector<ElementsWithFacetsDTO*>(), grid, (static_cast<FDTDDTO*>(dtosmartptr.get()))->GetDeltaT()) {

	/*
	 * REGISTRA TODOS OS PARES DE ELEMENTOS DTO E CORE
	 */
	Register(ElementsWithFacetsDTOSmartPointer(new ThinWireDTO), ElementCoreSmartPointer(new ThinWireFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new DeltaGapDTO), ElementCoreSmartPointer(new DeltaGapFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new DipoleDTO), ElementCoreSmartPointer(new DipoleFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new MonopoleDTO), ElementCoreSmartPointer(new MonopoleFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new PlaneWaveDTO), ElementCoreSmartPointer(new PlaneWaveFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new RectangularPECSheetDTO), ElementCoreSmartPointer(new RectangularPECSheetFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new BoxDTO), ElementCoreSmartPointer(new BoxFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new MicrostripDTO), ElementCoreSmartPointer(new MicrostripFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new FieldAtPointDTO), ElementCoreSmartPointer(new FieldAtPointFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new CylinderDTO), ElementCoreSmartPointer(new CylinderFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new CircularTubeDTO), ElementCoreSmartPointer(new CircularTubeFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new SphereDTO), ElementCoreSmartPointer(new SphereFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new RadiationPatternDTO), ElementCoreSmartPointer(new RadiationPatternFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new FieldAtPathDTO), ElementCoreSmartPointer(new FieldAtPathFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new FieldAtPlaneDTO), ElementCoreSmartPointer(new FieldAtPlaneFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new HelixDTO), ElementCoreSmartPointer(new HelixFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new RectangularTubeDTO), ElementCoreSmartPointer(new RectangularTubeFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new ToroidDTO), ElementCoreSmartPointer(new ToroidFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new GenericPECSheetDTO), ElementCoreSmartPointer(new GenericPECSheetFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new GenericPECSheetsDTO), ElementCoreSmartPointer(new GenericPECSheetsFDTDCore));
	Register(ElementsWithFacetsDTOSmartPointer(new DXFObjectDTO), ElementCoreSmartPointer(new DXFObjectFDTDCore));

	/*
	 * INICIALIZA ENGINE
	 */
	// O GRID é a primeira coisa a ser inicializada.
	// POR ENQUANTO SÓ ESTÁ SENDO CONSIDERADO GRID UNIFORME, que já é gerado automaticamente.
	grid = Grid(dto);
	Initialize();
}
double FDTDEngine::GetDeltaT() {
	return dto.GetDeltaT();
}
int FDTDEngine::GetTimeSteps() {
	return dto.GetTimesteps();
}
void FDTDEngine::SetDx(int x, int y, int z, double value) {
	data.Dx[x][y][z] = value;
}
void FDTDEngine::SetDy(int x, int y, int z, double value) {
	data.Dy[x][y][z] = value;
}
void FDTDEngine::SetDz(int x, int y, int z, double value) {
	data.Dz[x][y][z] = value;
}
void FDTDEngine::SetEx(int x, int y, int z, double value) {
	data.Ex[x][y][z] = value;
}
void FDTDEngine::SetEy(int x, int y, int z, double value) {
	data.Ey[x][y][z] = value;
}
void FDTDEngine::SetEz(int x, int y, int z, double value) {
	data.Ez[x][y][z] = value;
}
void FDTDEngine::SetHx(int x, int y, int z, double value) {
	data.Hx[x][y][z] = value;
}
void FDTDEngine::SetHy(int x, int y, int z, double value) {
	data.Hy[x][y][z] = value;
}
void FDTDEngine::SetHz(int x, int y, int z, double value) {
	data.Hz[x][y][z] = value;
}
double FDTDEngine::GetDx(int x, int y, int z) {
	return data.Dx[x][y][z];
}
double FDTDEngine::GetDy(int x, int y, int z) {
	return data.Dy[x][y][z];
}
double FDTDEngine::GetDz(int x, int y, int z) {
	return data.Dz[x][y][z];
}
double FDTDEngine::GetEx(int x, int y, int z) {
	return data.Ex[x][y][z];
}
double FDTDEngine::GetEy(int x, int y, int z) {
	return data.Ey[x][y][z];
}
double FDTDEngine::GetEz(int x, int y, int z) {
	return data.Ez[x][y][z];
}
double FDTDEngine::GetHx(int x, int y, int z) {
	return data.Hx[x][y][z];
}
double FDTDEngine::GetHy(int x, int y, int z) {
	return data.Hy[x][y][z];
}
double FDTDEngine::GetHz(int x, int y, int z) {
	return data.Hz[x][y][z];
}

void FDTDEngine::Initialize() {
	data.Initialize(grid, dto);
}

void FDTDEngine::SimulationWillFinish() {
	ProjectList p = GetProjectList();
	ProjectList::iterator it = p.begin();
	ProjectList::iterator end = p.end();

	while (it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		ElementCore* elementCorePtr = elementCore.get();
		(static_cast<FDTDElementCore*>(elementCorePtr))->SimulationWillFinish();

		it++;
	}
}
void FDTDEngine::SimulationWillStart() {

	ProjectList p = GetProjectList();
	ProjectList::iterator it = p.begin();
	ProjectList::iterator end = p.end();

	while (it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		ElementCore* elementCorePtr = elementCore.get();
		(static_cast<FDTDElementCore*>(elementCorePtr))->SimulationWillStart();

		it++;
	}
}
void FDTDEngine::DFieldsChanged(double t) {
	ProjectList p = GetProjectList();
	ProjectList::iterator it = p.begin();
	ProjectList::iterator end = p.end();

	while (it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		ElementCore* elementCorePtr = elementCore.get();
		(static_cast<FDTDElementCore*>(elementCorePtr))->DFieldsChanged(t);

		it++;
	}
}
void FDTDEngine::ElectricFieldsChanged(double t) {
	ProjectList p = GetProjectList();
	ProjectList::iterator it = p.begin();
	ProjectList::iterator end = p.end();

	while (it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		ElementCore* elementCorePtr = elementCore.get();
		(static_cast<FDTDElementCore*>(elementCorePtr))->ElectricFieldsChanged(t);

		it++;
	}
}
void FDTDEngine::MagneticFieldsChanged(double t) {
	ProjectList p = GetProjectList();
	ProjectList::iterator it = p.begin();
	ProjectList::iterator end = p.end();

	while (it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		ElementCore* elementCorePtr = elementCore.get();
		(static_cast<FDTDElementCore*>(elementCorePtr))->MagneticFieldsChanged(t);

		it++;
	}
}
Grid& FDTDEngine::GetGrid() {
	return grid;
}
void FDTDEngine::DoStartSimulation() {
	int timeSteps = dto.GetTimesteps();
	double deltaT = dto.GetDeltaT();

	ConfigureMesh();
//	for (int i = 25; i < 35; i++)
//		mesh.SaveMeshXZToFile(i);

	SimulationWillStart();
	int progress = 0;
	int t = 0;
	for(t = 0; t < timeSteps && UpdateProgress(progress); t++) {
		currentInterationNumber = t;

		CalculateDFields();
		DFieldsChanged(deltaT*t);
      	// Calcula os campos E a partir de D

       	data.CalculateEFields(mesh);

       	ElectricFieldsChanged(deltaT*t);
       	CalculateHFields();
       	MagneticFieldsChanged(deltaT*(0.5+t));

       	progress = 100.0*t/(timeSteps-1);

    }

    if (!SimulationWasCanceled()) {
    	SimulationWillFinish();
    }

}

void FDTDEngine::CalculateDFields() {
	data.CalculateDFields();
}

void FDTDEngine::CalculateHFields() {
	data.CalculateHFields();
}

FDTDEngine::~FDTDEngine() {
//	if (data) {
//		delete data;
//		data = 0;
//	}
}

int FDTDEngine::GetCurrentInterationNumber() {
	return currentInterationNumber;
}
/**
 * Para o pré-processamento do projeto, é importante verificar se os elementos estão dentro do grid.
 */
bool FDTDEngine::DoIsProjectConsistentBegin() {
	bool prjOk = true;

	ProjectList p = GetProjectList();
	ProjectList::iterator it = p.begin();
	ProjectList::iterator end = p.end();

	/*************************************************/
	/* Verifica se os elementos estão dentro do grid */
	/*************************************************/
	// Dimensões do grid
	double xGridMin = dto.GetXmin(); double yGridMin = dto.GetYmin(); double zGridMin = dto.GetZmin();
	double xGridMax = dto.GetXmax(); double yGridMax = dto.GetYmax(); double zGridMax = dto.GetZmax();

	while (it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		ElementCore* elementCorePtr = elementCore.get();
		FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(elementCorePtr);

		double xmin, ymin, zmin, xmax, ymax, zmax;
		bool hasDimensions = fdtdElementCorePtr->FillDimensions(xmin, ymin, zmin, xmax, ymax, zmax);

		if (hasDimensions &&
				(xmin < xGridMin || ymin < yGridMin || zmin < zGridMin || xmax > xGridMax || ymax > yGridMax || zmax > zGridMax)) {
			wxString errorMessage = fdtdElementCorePtr->GetName() + " is outside the grid.";
			AppendErrorMessage(errorMessage);
			prjOk = false;
		}

		it++;
	}

	/*************************************************/
	/* Se o FDTD tiver sido configurado com PBC,     */
	/* verifica se existe apenas uma onda plana.     */
	/*************************************************/
	if (dto.GetABC().IsPeriodic(xNeg) || dto.GetABC().IsPeriodic(zNeg)) {
		it = p.begin();

		int numberOfPlaneWaves = 0;
		wxString planeWaveNameDTOClassName = PlaneWaveDTO().GetDTOClassName();

		while (it != end) {
			ElementCoreSmartPointer elementCore = (*it);
			ElementCore* elementCorePtr = elementCore.get();

			/* Verifica se o elemento é uma onda plana */
			if (elementCorePtr->GetDTO()->GetDTOClassName() == planeWaveNameDTOClassName) {
				numberOfPlaneWaves++;
			}

			it++;
		}
		if (numberOfPlaneWaves == 0) {
			wxString errorMessage = "It is necessary one plane wave to use with periodic boundary condition.";
			AppendErrorMessage(errorMessage);
			prjOk = false;
		} else if (numberOfPlaneWaves > 1) {
			wxString errorMessage = "Project should have only one plane wave to use with periodic boundary condition.";
			AppendErrorMessage(errorMessage);
			prjOk = false;
		}
	}

	/*************************************************/
	/* Se o FDTD tiver sido configurado com PBC,     */
	/* verifica se o grid é uniforme e os delta em   */
	/* cada células são iguais.                      */
	/*************************************************/
	if (dto.GetABC().IsPeriodic(xNeg) || dto.GetABC().IsPeriodic(zNeg)) {
		bool gridOk = true;

		double delta = grid.GetDx(0);
		double deltaMin = delta*0.9999;
		double deltaMax = delta*1.0001;

		int nCellsX = grid.GetNxTOTAL();
		int nCellsY = grid.GetNyTOTAL();
		int nCellsZ = grid.GetNzTOTAL();

		for (int i = 0; i < nCellsX && gridOk; i++) {
			if ((grid.GetDx(i) < deltaMin) || (grid.GetDx(i) > deltaMax))
				gridOk = false;
		}
//		for (int i = 0; i < nCellsY && gridOk; i++) {
//			if ((grid.GetDy(i) < deltaMin) || (grid.GetDy(i) > deltaMax))
//				gridOk = false;
//		}
		for (int i = 0; i < nCellsZ && gridOk; i++) {
			if ((grid.GetDz(i) < deltaMin) || (grid.GetDz(i) > deltaMax))
				gridOk = false;
		}

		if (!gridOk) {
			wxString errorMessage = "Grid spacing should be equal in x and z directions.";
			AppendErrorMessage(errorMessage);
			prjOk = false;
		}
	}
	return prjOk;
}
//bool FDTDEngine::IsProjectConsistent() {
//	bool prjOK = true;
//
////	ProjectList p = GetProjectList();
////	ProjectList::iterator it = p.begin();
////	ProjectList::iterator end = p.end();
////
////	while (it != end) {
////		ElementCoreSmartPointer elementCore = (*it);
////		ElementCore* elementCorePtr = elementCore.get();
////		FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(elementCorePtr);
////
////		it++;
////	}
//
//	return prjOK;
//}
bool FDTDEngine::DoIsProjectConsistentEnd() {
	bool prjOK = true;

//	ProjectList p = GetProjectList();
//	ProjectList::iterator it = p.begin();
//	ProjectList::iterator end = p.end();
//
//	while (it != end) {
//		ElementCoreSmartPointer elementCore = (*it);
//		ElementCore* elementCorePtr = elementCore.get();
//		FDTDElementCore* fdtdElementCorePtr = static_cast<FDTDElementCore*>(elementCorePtr);
//
//		it++;
//	}

	return prjOK;
}
void FDTDEngine::ConfigureMesh() {

	ProjectList p = GetProjectList();
	ProjectList::iterator it = p.begin();
	ProjectList::iterator end = p.end();

	vector<ElementsWithFacetsDTO*> objectsWithFacets;

	while (it != end) {
		ElementCoreSmartPointer elementCore = (*it);
		ElementDTOSmartPointer dtoSP = elementCore->GetDTO();

		ElementsWithFacetsDTO* emstudioDTO = (static_cast<ElementsWithFacetsDTO*>(dtoSP.get()));

		if (emstudioDTO->HasFaces()) {
			objectsWithFacets.push_back(emstudioDTO);
		}

		it++;
	}
	mesh = Mesh(objectsWithFacets, grid, dto.GetDeltaT());
	mesh.Generate(this, dto.IsSmoothMesh());
}

FDTDDTO& FDTDEngine::GetFDTDDTO() {
	return dto;
}

void FDTDEngine::DoCreateProject() {
	GetProjectList().sort(compareElementCoreSmartPointer);
}
