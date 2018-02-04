/*
 * PlaneWavePBCFDTDCore.cpp
 *
 *  Created on: 27/03/2013
 *      Author: Leandro
 */

#include "PlaneWavePBCFDTDCore.h"

PlaneWavePBCFDTDCore::PlaneWavePBCFDTDCore() {

}

PlaneWavePBCFDTDCore::~PlaneWavePBCFDTDCore() {
}

void PlaneWavePBCFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	PlaneWaveDTO* planeWaveDTO = static_cast<PlaneWaveDTO*>(elementDTOSmartPtr.get());

	dto = *planeWaveDTO;
}

ElementCoreSmartPointer PlaneWavePBCFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new PlaneWavePBCFDTDCore);
}

bool PlaneWavePBCFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetXmin(); ymin = dto.GetYmin(); zmin = dto.GetZmin();
	xmax = dto.GetXmax(); ymax = dto.GetYmax(); zmax = dto.GetZmax();
	return true;
}

void PlaneWavePBCFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();

	pbcXaxis = engine->GetFDTDDTO().GetABC().IsPeriodic(xNeg);
	pbcZaxis = engine->GetFDTDDTO().GetABC().IsPeriodic(zNeg);

	Ez_low_m1=0;
	Ez_low_m2=0.;
	Ez_high_m1=0.;
	Ez_high_m2=0.;

	dt = engine->GetDeltaT();
	cdt = SPEED_OF_LIGHT_VACUUM * dt;

	Nx = grid.GetNxTOTAL();
	Ny = grid.GetNyTOTAL();
	Nz = grid.GetNzTOTAL();

	Ez_inc = Array1D<double>(Ny, 0.0);
	Hx_inc = Array1D<double>(Ny, 0.0);

	ia = 1;
	ja = grid.GetYCell(dto.GetYmin());
	ka = 1;
	ib = Nx - ia - 1;
	jb = Ny - 1;
	kb = Nz - ka - 1;

	dto.GetExcitation().Init();
}
void PlaneWavePBCFDTDCore::DFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	// Calculate the incident buffer
	for(int j = 1; j < Ny; j++)
		Ez_inc[j] = Ez_inc[j] + 0.5*(Hx_inc[j-1] - Hx_inc[j]);

	// source
	double S = dto.GetExcitation().GetExcitationValue(t);

	Ez_inc[3] = S;

	// Boundary conditions for the incident buffer
	Ez_inc[0] = Ez_low_m2;
	Ez_low_m2 = Ez_low_m1;
	Ez_low_m1 = Ez_inc[1];
	Ez_inc[Ny-1] = Ez_high_m2;
	Ez_high_m2 = Ez_high_m1;
	Ez_high_m1 = Ez_inc[Ny-2];

	// Incident Dz
	for(int i = 1; i < Nx; i++) {
		for(int k = ka-1; k <= kb+1; k++) {
			double value = engine->GetDz(i, ja, k) + 0.5*Hx_inc[ja-1];
			engine->SetDz(i, ja, k, value);
		}
	}
}
void PlaneWavePBCFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	// Para alterar o campo Ex, Ey, Ez, use uma das funções abaixo:
	//	engine->SetEx(i, j, k, value);
	//	engine->SetEy(i, j, k, value);
	//	engine->SetEz(i, j, k, value);

	// As variáveis ia, ja, ka, ib, jb e kb guardam os índices que representam os limites da onda plana
	// Veja código dentro do método PlaneWavePBCFDTDCore::MagneticFieldsChanged

	// Esse if é executado quando o usuário selecionou PBC no eixo X
	if (pbcXaxis) {
		for(int j = 0; j < Ny; j++)
		{
			for(int k = ka-1; k <= kb+1; k++)
			{
				double value = engine->GetEy(ib+1, j, k);
				engine->SetEy(0, j, k, value);

				value = engine->GetEz(Nx-1, j, k);
				engine->SetEz(0, j, k, value);

			}
		}
	}

	// Esse if é executado quando o usuário selecionou PBC no eixo Z
	if (pbcZaxis) {
		for(int i = ia-1; i <= ib+1; i++)
		{
			for(int j = 0; j < Ny; j++)
			{
				double value = engine->GetEx(i, j, kb+1);
				engine->SetEx(i, j, 0, value);

				value = engine->GetEy(i, j, kb+1);
				engine->SetEy(i, j, 0, value);
			}
		}
	}
}
void PlaneWavePBCFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	// Calculate the incident field
	for(int j = 0; j < Ny-1; j++)
		Hx_inc[j] = Hx_inc[j] + 0.5*(Ez_inc[j] - Ez_inc[j+1]);

	// Incident Hx
	for(int i = 0; i < Nx; i++) {
		for(int k = ka-1; k <= kb + 1; k++) {
			double value = engine->GetHx(i, ja-1, k) + 0.5*Ez_inc[ja];
			engine->SetHx(i, ja-1, k, value);
		}
	}

	// PBC Hy e Hz
	if (pbcXaxis) {
		for(int j = 0; j < Ny; j++){
			for(int k = ka-1; k <= kb+1; k++){
				double value = engine->GetHy(0,j,k);
				engine->SetHy(Nx-1,j,k, value);

				value = engine->GetHz(0,j,k);
				engine->SetHz(ib+1,j,k, value);
			}
		}
	}
	// PBC Hx e Hy
	if (pbcZaxis) {
		for(int i = 0; i < Nx; i++)	{
			for(int j = 0; j < Ny; j++){
				double value = engine->GetHx(i,j, 0);
				engine->SetHx(i,j, kb+1, value);

				value = engine->GetHy(i,j, 0);
				engine->SetHy(i,j, kb+1, value);
			}
		}
	}
}

void PlaneWavePBCFDTDCore::SimulationWillFinish() {

}

bool PlaneWavePBCFDTDCore::IsElementConsistent() {
	bool elementOK = true;

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	/****************************************************************************/
	/* Se o FDTD tiver sido configurado com PBC, verifica se a direção da onda  */
	/* plana está configurada corretamente e se ela ocupa tod_o o espaço do grid*/
	/****************************************************************************/
	double xGridMin = engine->GetFDTDDTO().GetXmin(); double yGridMin = engine->GetFDTDDTO().GetYmin(); double zGridMin = engine->GetFDTDDTO().GetZmin();
	double xGridMax = engine->GetFDTDDTO().GetXmax(); double yGridMax = engine->GetFDTDDTO().GetYmax(); double zGridMax = engine->GetFDTDDTO().GetZmax();

	double xMin = dto.GetXmin(); double yMin = dto.GetYmin(); double zMin = dto.GetZmin();
	double xMax = dto.GetXmax(); double yMax = dto.GetYmax(); double zMax = dto.GetZmax();

	if (xMin != xGridMin || /*yMin != yGridMin ||*/ zMin != zGridMin ||
			xMax != xGridMax || yMax != yGridMax || zMax != zGridMax) {
		wxString errorMessage = GetName() + " should occupied the whole grid for y > constant.";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}

	bool directionOK = (dto.GetTheta() == 90) && (/*(dto.GetPhi() == 90) || */(dto.GetPhi() == 270)) && (dto.GetPsi() == 90);
	if (!directionOK) {
		wxString errorMessage = GetName();
		errorMessage.Append(wxT(": (\u03B8, \u03D5, \u03A8) should be (90\u00B0, 270\u00B0, 90\u00B0)")); // Ordem: teta, phi, psi
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}

	return elementOK;
}
