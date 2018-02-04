/*
 * FDTDEngine.h
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#ifndef FDTDENGINE_H_
#define FDTDENGINE_H_

#include "wx/wx.h"

#include "emstudio/util/tnt/tnt.h"
#include "emstudio/dto/fdtdapp/FDTDDTO.h"
#include "emstudio/core/Engine.h"

#include "Grid.h"
#include "Mesh.h"

#include "emstudio/util/file/FileManager.h"
#include "wx/wx.h"
#include "FDTDData.h"

class Mesh;

class FDTDEngine : public Engine {
private:
	FDTDData data;
	int currentInterationNumber;

	FDTDDTO dto;
	Grid grid;
	Mesh mesh;

private:
	void Initialize();
	void SetObjectMaterial();

	void SimulationWillFinish();
	void SimulationWillStart();
	void DFieldsChanged(double t);
	void ElectricFieldsChanged(double t);
	void MagneticFieldsChanged(double t);

	void CalculateHFields();
	void CalculateDFields();

	void ConfigureMesh();
public:
	FDTDEngine(ElementDTOSmartPointer dto, InformSimulationStatusSmartPointer status);
	virtual ~FDTDEngine();

	double GetDeltaT();
	int GetTimeSteps();

	void SetDx(int x, int y, int z, double value);
	void SetDy(int x, int y, int z, double value);
	void SetDz(int x, int y, int z, double value);

	void SetEx(int x, int y, int z, double value);
	void SetEy(int x, int y, int z, double value);
	void SetEz(int x, int y, int z, double value);

	void SetHx(int x, int y, int z, double value);
	void SetHy(int x, int y, int z, double value);
	void SetHz(int x, int y, int z, double value);

	double GetDx(int x, int y, int z);
	double GetDy(int x, int y, int z);
	double GetDz(int x, int y, int z);

	double GetEx(int x, int y, int z);
	double GetEy(int x, int y, int z);
	double GetEz(int x, int y, int z);

	double GetHx(int x, int y, int z);
	double GetHy(int x, int y, int z);
	double GetHz(int x, int y, int z);

	Grid& GetGrid();
	virtual void DoStartSimulation();

	int GetCurrentInterationNumber();

	virtual void DoCreateProject();

//	virtual bool IsProjectConsistent();
	virtual bool DoIsProjectConsistentBegin();
	virtual bool DoIsProjectConsistentEnd();

	FDTDDTO& GetFDTDDTO();
};

#endif /* FDTDENGINE_H_ */
