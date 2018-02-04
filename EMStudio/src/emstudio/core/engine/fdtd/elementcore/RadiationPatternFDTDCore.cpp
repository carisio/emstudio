/*
 * RadiationPatternFDTDCore.cpp
 *
 *  Created on: 06/03/2012
 *      Author: leandrocarisio
 */

#include "RadiationPatternFDTDCore.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/RadiationPatternResult.h"

RadiationPatternFDTDCore::RadiationPatternFDTDCore() {

}

RadiationPatternFDTDCore::~RadiationPatternFDTDCore() {
}


ElementCoreSmartPointer RadiationPatternFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new RadiationPatternFDTDCore);
}

void RadiationPatternFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	RadiationPatternDTO* radiationPatternDTO = static_cast<RadiationPatternDTO*>(elementDTOSmartPtr.get());
	dto = *radiationPatternDTO;

	cout << "DoConfigure\n";
	cout << dto.GetXmin() << endl;
	cout << dto.GetYmin() << endl;
	cout << dto.GetZmin() << endl;
	cout << dto.GetXmax() << endl;
	cout << dto.GetYmax() << endl;
	cout << dto.GetZmax() << endl;
}

void RadiationPatternFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid& grid = engine->GetGrid();

//	int Nx = engine->GetGrid().GetNxTOTAL();
//	int Ny = engine->GetGrid().GetNyTOTAL();
//	int Nz = engine->GetGrid().GetNzTOTAL();

//	Ri1 = grid.GetXCell(grid.GetXMin()) + 5;
//	Rj1 = grid.GetYCell(grid.GetYMin()) + 5;
//	Rk1 = grid.GetZCell(grid.GetZMin()) + 5;
//	Ri2 = grid.GetXCell(grid.GetXMax()) - 5;
//	Rj2 = grid.GetYCell(grid.GetYMax()) - 5;
//	Rk2 = grid.GetZCell(grid.GetZMax()) - 5;
	Ri1 = grid.GetXCell(dto.GetXmin());
	Rj1 = grid.GetYCell(dto.GetYmin());
	Rk1 = grid.GetZCell(dto.GetZmin());
	Ri2 = grid.GetXCell(dto.GetXmax());
	Rj2 = grid.GetYCell(dto.GetYmax());
	Rk2 = grid.GetZCell(dto.GetZmax());

	NFreq = dto.GetNFrequency();

	PLANOXY = Array2D<double>(360,NFreq,0.0);
	PLANOZX = Array2D<double>(360,NFreq,0.0);
	PLANOYZ = Array2D<double>(360,NFreq,0.0);

	Numi = Ri2-Ri1;
	Numj = Rj2-Rj1;
	Numk = Rk2-Rk1;

	ExIJt1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	ExIJt2 = Array3D<double>(Numi,Numj,NFreq,0.0);
	EyIJt1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	EyIJt2 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HxIJt1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HxIJt2 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HyIJt1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HyIJt2 = Array3D<double>(Numi,Numj,NFreq,0.0);
	ExIJb1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	ExIJb2 = Array3D<double>(Numi,Numj,NFreq,0.0);
	EyIJb1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	EyIJb2 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HxIJb1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HxIJb2 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HyIJb1 = Array3D<double>(Numi,Numj,NFreq,0.0);
	HyIJb2 = Array3D<double>(Numi,Numj,NFreq,0.0);

	ExIKt1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	ExIKt2 = Array3D<double>(Numi,Numk,NFreq,0.0);
	EzIKt1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	EzIKt2 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HxIKt1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HxIKt2 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HzIKt1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HzIKt2 = Array3D<double>(Numi,Numk,NFreq,0.0);
	ExIKb1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	ExIKb2 = Array3D<double>(Numi,Numk,NFreq,0.0);
	EzIKb1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	EzIKb2 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HxIKb1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HxIKb2 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HzIKb1 = Array3D<double>(Numi,Numk,NFreq,0.0);
	HzIKb2 = Array3D<double>(Numi,Numk,NFreq,0.0);

	EyJKt1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	EyJKt2 = Array3D<double>(Numj,Numk,NFreq,0.0);
	EzJKt1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	EzJKt2 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HyJKt1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HyJKt2 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HzJKt1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HzJKt2 = Array3D<double>(Numj,Numk,NFreq,0.0);
	EyJKb1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	EyJKb2 = Array3D<double>(Numj,Numk,NFreq,0.0);
	EzJKb1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	EzJKb2 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HyJKb1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HyJKb2 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HzJKb1 = Array3D<double>(Numj,Numk,NFreq,0.0);
	HzJKb2 = Array3D<double>(Numj,Numk,NFreq,0.0);

	RD1 = Array1D<double>(NFreq,0.0);
	RD2 = Array1D<double>(NFreq,0.0);

	omega = Array1D<double>(NFreq,0.0);
	frequency = Array1D<double>(NFreq,0.0);
	kapa = Array1D<double>(NFreq,0.0);

	Cosine = Array1D<double>(361,0.0);
	Sine = Array1D<double>(361,0.0);

	for (int i = 0; i <= 360; i++) {
		Cosine[i] = cos(i*PI/180.0);
		Sine[i] = sin(i*PI/180.0);
	}


	double FInit = dto.GetInitialFrequency();
	double FStep = dto.GetFrequencyStep();

	for (int f = 0; f < NFreq; f++) {
		frequency[f] = FInit + f*FStep;
		omega[f] = 2.0*PI*(FInit + f*FStep);
		kapa[f] = omega[f]/SPEED_OF_LIGHT_VACUUM;
	}
}
void RadiationPatternFDTDCore::ElectricFieldsChanged(double t) {
//	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	for (int f = 0; f < NFreq; f++) {
		RD1[f] = cos(-omega[f]*t);
		RD2[f] = sin(-omega[f]*t);
	}

	#pragma omp parallel sections
		{
	#pragma omp section
			EFldIJ();
	#pragma omp section
			EFldIK();
	#pragma omp section
			EFldJK();
		}
}

void RadiationPatternFDTDCore::EFldIJ() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double aux1,aux2,aux3,aux4;
	int ii,jj;

	for (int i = Ri1; i < Ri2; i++) {
		for (int j = Rj1; j < Rj2; j++) {
			aux1 = (engine->GetEx(i,j,Rk1) + engine->GetEx(i,j+1,Rk1))/2.0;
			aux2 = (engine->GetEx(i,j,Rk2) + engine->GetEx(i,j+1,Rk2))/2.0;
			aux3 = (engine->GetEy(i,j,Rk1) + engine->GetEy(i+1,j,Rk1))/2.0;
			aux4 = (engine->GetEy(i,j,Rk2) + engine->GetEy(i+1,j,Rk2))/2.0;

			ii = i-Ri1;
			jj = j-Rj1;
			for (int f = 0; f < NFreq; f++) {
				ExIJb1[ii][jj][f] = ExIJb1[ii][jj][f] + aux1 * RD1[f];
				ExIJb2[ii][jj][f] = ExIJb2[ii][jj][f] + aux1 * RD2[f];

				ExIJt1[ii][jj][f] = ExIJt1[ii][jj][f] + aux2 * RD1[f];
				ExIJt2[ii][jj][f] = ExIJt2[ii][jj][f] + aux2 * RD2[f];

				EyIJb1[ii][jj][f] = EyIJb1[ii][jj][f] + aux3 * RD1[f];
				EyIJb2[ii][jj][f] = EyIJb2[ii][jj][f] + aux3 * RD2[f];

				EyIJt1[ii][jj][f] = EyIJt1[ii][jj][f] + aux4 * RD1[f];
				EyIJt2[ii][jj][f] = EyIJt2[ii][jj][f] + aux4 * RD2[f];
			}
		}
	}
}

void RadiationPatternFDTDCore::EFldIK() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double aux1,aux2,aux3,aux4;
	int ii,kk;

	for (int i = Ri1; i < Ri2; i++) {
		for (int k = Rk1; k < Rk2; k++) {
			aux1 = (engine->GetEx(i,Rj1,k) + engine->GetEx(i,Rj1,k+1))/2.0;
			aux2 = (engine->GetEx(i,Rj2,k) + engine->GetEx(i,Rj2,k+1))/2.0;
			aux3 = (engine->GetEz(i,Rj1,k) + engine->GetEz(i+1,Rj1,k))/2.0;
			aux4 = (engine->GetEz(i,Rj2,k) + engine->GetEz(i+1,Rj2,k))/2.0;

			ii = i-Ri1;
			kk = k-Rk1;
			for (int f = 0; f < NFreq; f++) {
				ExIKb1[ii][kk][f] = ExIKb1[ii][kk][f] + aux1 * RD1[f];
				ExIKb2[ii][kk][f] = ExIKb2[ii][kk][f] + aux1 * RD2[f];

				ExIKt1[ii][kk][f] = ExIKt1[ii][kk][f] + aux2 * RD1[f];
				ExIKt2[ii][kk][f] = ExIKt2[ii][kk][f] + aux2 * RD2[f];

				EzIKb1[ii][kk][f] = EzIKb1[ii][kk][f] + aux3 * RD1[f];
				EzIKb2[ii][kk][f] = EzIKb2[ii][kk][f] + aux3 * RD2[f];

				EzIKt1[ii][kk][f] = EzIKt1[ii][kk][f] + aux4 * RD1[f];
				EzIKt2[ii][kk][f] = EzIKt2[ii][kk][f] + aux4 * RD2[f];
			}
		}
	}
}

void RadiationPatternFDTDCore::EFldJK() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double aux1,aux2,aux3,aux4;
	int jj,kk;

	for (int j = Rj1; j < Rj2; j++) {
		for (int k = Rk1; k < Rk2; k++) {
			aux1 = (engine->GetEy(Ri1,j,k) + engine->GetEy(Ri1,j,k+1))/2.0;
			aux2 = (engine->GetEy(Ri2,j,k) + engine->GetEy(Ri2,j,k+1))/2.0;
			aux3 = (engine->GetEz(Ri1,j,k) + engine->GetEz(Ri1,j+1,k))/2.0;
			aux4 = (engine->GetEz(Ri2,j,k) + engine->GetEz(Ri2,j+1,k))/2.0;

			jj = j-Rj1;
			kk = k-Rk1;
			for (int f = 0; f < NFreq; f++) {
				EyJKb1[jj][kk][f] = EyJKb1[jj][kk][f] + aux1 * RD1[f];
				EyJKb2[jj][kk][f] = EyJKb2[jj][kk][f] + aux1 * RD2[f];

				EyJKt1[jj][kk][f] = EyJKt1[jj][kk][f] + aux2 * RD1[f];
				EyJKt2[jj][kk][f] = EyJKt2[jj][kk][f] + aux2 * RD2[f];

				EzJKb1[jj][kk][f] = EzJKb1[jj][kk][f] + aux3 * RD1[f];
				EzJKb2[jj][kk][f] = EzJKb2[jj][kk][f] + aux3 * RD2[f];

				EzJKt1[jj][kk][f] = EzJKt1[jj][kk][f] + aux4 * RD1[f];
				EzJKt2[jj][kk][f] = EzJKt2[jj][kk][f] + aux4 * RD2[f];
			}
		}
	}
}
void RadiationPatternFDTDCore::MagneticFieldsChanged(double t) {
//	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	for (int f=0;f<NFreq;f++) {
		RD1[f]=cos(-omega[f]*t);
		RD2[f]=sin(-omega[f]*t);
	}
	#pragma omp parallel sections
		{
	#pragma omp section
			HFldIJ();
	#pragma omp section
			HFldIK();
	#pragma omp section
			HFldJK();
		}
}
void RadiationPatternFDTDCore::HFldIJ() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double aux1,aux2,aux3,aux4;
	int ii,jj;

	for (int i = Ri1; i < Ri2; i++) {
		for (int j = Rj1; j < Rj2; j++) {
			aux1 = (engine->GetHx(i,j,Rk1) + engine->GetHx(i,j,Rk1-1) +
					engine->GetHx(i+1,j,Rk1) + engine->GetHx(i+1,j,Rk1-1))/4.0;
			aux2 = (engine->GetHx(i,j,Rk2) + engine->GetHx(i,j,Rk2-1) +
					engine->GetHx(i+1,j,Rk2) + engine->GetHx(i+1,j,Rk2-1))/4.0;
			aux3 = (engine->GetHy(i,j,Rk1) + engine->GetHy(i,j,Rk1-1) +
					engine->GetHy(i,j+1,Rk1) + engine->GetHy(i,j+1,Rk1-1))/4.0;
			aux4 = (engine->GetHy(i,j,Rk2) + engine->GetHy(i,j,Rk2-1) +
					engine->GetHy(i,j+1,Rk2) + engine->GetHy(i,j+1,Rk2-1))/4.0;

			ii = i-Ri1;
			jj = j-Rj1;
			for (int f = 0; f < NFreq; f++) {
				HxIJb1[ii][jj][f] = HxIJb1[ii][jj][f] + aux1 * RD1[f];
				HxIJb2[ii][jj][f] = HxIJb2[ii][jj][f] + aux1 * RD2[f];

				HxIJt1[ii][jj][f] = HxIJt1[ii][jj][f] + aux2 * RD1[f];
				HxIJt2[ii][jj][f] = HxIJt2[ii][jj][f] + aux2 * RD2[f];

				HyIJb1[ii][jj][f] = HyIJb1[ii][jj][f] + aux3 * RD1[f];
				HyIJb2[ii][jj][f] = HyIJb2[ii][jj][f] + aux3 * RD2[f];

				HyIJt1[ii][jj][f] = HyIJt1[ii][jj][f] + aux4 * RD1[f];
				HyIJt2[ii][jj][f] = HyIJt2[ii][jj][f] + aux4 * RD2[f];
			}
		}
	}
}
void RadiationPatternFDTDCore::HFldIK() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double aux1,aux2,aux3,aux4;
	int ii,kk;

	for (int i = Ri1; i < Ri2; i++) {
		for (int k = Rk1; k < Rk2; k++) {
			aux1 = (engine->GetHx(i,Rj1,k) + engine->GetHx(i,Rj1-1,k) +
					engine->GetHx(i+1,Rj1,k) + engine->GetHx(i+1,Rj1-1,k))/4.0;
			aux2 = (engine->GetHx(i,Rj2,k) + engine->GetHx(i,Rj2-1,k) +
					engine->GetHx(i+1,Rj2,k) + engine->GetHx(i+1,Rj2-1,k))/4.0;
			aux3 = (engine->GetHz(i,Rj1,k) + engine->GetHz(i,Rj1-1,k) +
					engine->GetHz(i,Rj1,k+1) + engine->GetHz(i,Rj1-1,k+1))/4.0;
			aux4 = (engine->GetHz(i,Rj2,k) + engine->GetHz(i,Rj2-1,k) +
					engine->GetHz(i,Rj2,k+1) + engine->GetHz(i,Rj2-1,k+1))/4.0;

			ii = i-Ri1;
			kk = k-Rk1;
			for (int f = 0; f < NFreq; f++) {
				HxIKb1[ii][kk][f] = HxIKb1[ii][kk][f] + aux1 * RD1[f];
				HxIKb2[ii][kk][f] = HxIKb2[ii][kk][f] + aux1 * RD2[f];

				HxIKt1[ii][kk][f] = HxIKt1[ii][kk][f] + aux2 * RD1[f];
				HxIKt2[ii][kk][f] = HxIKt2[ii][kk][f] + aux2 * RD2[f];

				HzIKb1[ii][kk][f] = HzIKb1[ii][kk][f] + aux3 * RD1[f];
				HzIKb2[ii][kk][f] = HzIKb2[ii][kk][f] + aux3 * RD2[f];

				HzIKt1[ii][kk][f] = HzIKt1[ii][kk][f] + aux4 * RD1[f];
				HzIKt2[ii][kk][f] = HzIKt2[ii][kk][f] + aux4 * RD2[f];
			}
		}
	}
}
void RadiationPatternFDTDCore::HFldJK() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double aux1,aux2,aux3,aux4;
	int jj,kk;

	for (int j = Rj1; j < Rj2; j++) {
		for (int k = Rk1; k < Rk2; k++) {
			aux1 = (engine->GetHy(Ri1,j,k) + engine->GetHy(Ri1-1,j,k) +
					engine->GetHy(Ri1,j+1,k) + engine->GetHy(Ri1-1,j+1,k))/4.0;
			aux2 = (engine->GetHy(Ri2,j,k) + engine->GetHy(Ri2-1,j,k) +
					engine->GetHy(Ri2,j+1,k) + engine->GetHy(Ri2-1,j+1,k))/4.0;
			aux3 = (engine->GetHz(Ri1,j,k) + engine->GetHz(Ri1-1,j,k) +
					engine->GetHz(Ri1,j,k+1) + engine->GetHz(Ri1-1,j,k+1))/4.0;
			aux4 = (engine->GetHz(Ri2,j,k) + engine->GetHz(Ri2-1,j,k) +
					engine->GetHz(Ri2,j,k+1) + engine->GetHz(Ri2-1,j,k+1))/4.0;

			jj = j-Rj1;
			kk = k-Rk1;
			for (int f = 0; f < NFreq; f++) {
				HyJKb1[jj][kk][f] = HyJKb1[jj][kk][f] + aux1 * RD1[f];
				HyJKb2[jj][kk][f] = HyJKb2[jj][kk][f] + aux1 * RD2[f];

				HyJKt1[jj][kk][f] = HyJKt1[jj][kk][f] + aux2 * RD1[f];
				HyJKt2[jj][kk][f] = HyJKt2[jj][kk][f] + aux2 * RD2[f];

				HzJKb1[jj][kk][f] = HzJKb1[jj][kk][f] + aux3 * RD1[f];
				HzJKb2[jj][kk][f] = HzJKb2[jj][kk][f] + aux3 * RD2[f];

				HzJKt1[jj][kk][f] = HzJKt1[jj][kk][f] + aux4 * RD1[f];
				HzJKt2[jj][kk][f] = HzJKt2[jj][kk][f] + aux4 * RD2[f];
			}
		}
	}
}
void RadiationPatternFDTDCore::SimulationWillFinish() {
	int Phi,Theta;

	double Max;

	// Representa quantos % equivale cada iteração
	double stepPercentage = 100.0/NFreq;
	wxString status = "Computing radiation pattern (";

	for (int f = 0; f < NFreq; f++) {
		GetEngine()->InformStatus(status + Converter::DoubleToFormattedString((f+0.0/6.0)*stepPercentage, 0) + "%)");
		Theta = 90;
		Max = -1e30;
		for (Phi = 0; Phi < 360; Phi++) {
			PLANOXY[Phi][f] = CalculateNLphasors(f,Theta,Phi);
			if (PLANOXY[Phi][f] > Max)
				Max = PLANOXY[Phi][f];
		}
		GetEngine()->InformStatus(status + Converter::DoubleToFormattedString((f+1.0/6.0)*stepPercentage, 0) + "%)");
		for (Phi = 0; Phi < 360; Phi++) {
			PLANOXY[Phi][f]/=Max;
			if(PLANOXY[Phi][f] <= 1e-6 || Max == 0)
				PLANOXY[Phi][f] = 1e-6;
			PLANOXY[Phi][f] = 10*log10(PLANOXY[Phi][f]);
		}
		GetEngine()->InformStatus(status + Converter::DoubleToFormattedString((f+2.0/6.0)*stepPercentage, 0) + "%)");
		Max = -1e30;
		Phi = 0;
		for (Theta = 0; Theta < 360; Theta++) {
			PLANOZX[Theta][f] = CalculateNLphasors(f,Theta,Phi);
			if (PLANOZX[Theta][f] > Max)
				Max=PLANOZX[Theta][f];
		}
		GetEngine()->InformStatus(status + Converter::DoubleToFormattedString((f+3.0/6.0)*stepPercentage, 0) + "%)");
		for (Theta = 0; Theta < 360; Theta++) {
			PLANOZX[Theta][f]/=Max;
			if(PLANOZX[Theta][f] <= 1e-6 || Max == 0)
				PLANOZX[Theta][f] = 1e-6;
			PLANOZX[Theta][f] = 10*log10(PLANOZX[Theta][f]);
		}
		Max = -1e30;
		Phi = 90;
		GetEngine()->InformStatus(status + Converter::DoubleToFormattedString((f+4.0/6.0)*stepPercentage, 0) + "%)");
		for (Theta = 0; Theta < 360; Theta++) {
			PLANOYZ[Theta][f] = CalculateNLphasors(f,Theta,Phi);
			if (PLANOYZ[Theta][f] > Max)
				Max=PLANOYZ[Theta][f];
		}
		GetEngine()->InformStatus(status + Converter::DoubleToFormattedString((f+5.0/6.0)*stepPercentage, 0) + "%)");
		for (Theta = 0; Theta < 360; Theta++) {
			PLANOYZ[Theta][f]/=Max;
			if(PLANOYZ[Theta][f] <= 1e-6 || Max == 0)
				PLANOYZ[Theta][f] = 1e-6;
			PLANOYZ[Theta][f] = 10*log10(PLANOYZ[Theta][f]);
		}
		GetEngine()->InformStatus(status + Converter::DoubleToFormattedString((f+6.0/6.0)*stepPercentage, 0) + "%)");
	}
	GetEngine()->InformStatus("");
}

double RadiationPatternFDTDCore::CalculateNLphasors(int f, int Theta, int Phi) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid& grid = engine->GetGrid();

	std::complex<double>Jx;
	std::complex<double>Jy;
	std::complex<double>Jz;
	std::complex<double>Mx;
	std::complex<double>My;
	std::complex<double>Mz;

	std::complex<double>ejkr;

	double r,dr1,dr2,dr3,dr4,dx,dy,dz;

	double cost,cosp,sint,sinp;

	int ii,jj,kk;
	cost = Cosine[Theta];
	cosp = Cosine[Phi];
	sint = Sine[Theta];
	sinp = Sine[Phi];

	NTheta = std::complex<double>(0.,0.);
	NPhi = std::complex<double>(0., 0.);
	LTheta = std::complex<double>(0., 0.);
	LPhi = std::complex<double>(0., 0.);

	//Faces X
	//   #pragma omp parallel for private(j,k,Jy,Jz,My,Mz,dy,dz,jj,kk,r,ejkr)
	dr1 = (grid.GetAccumulatedDx(Ri1))*sint*cosp;
	dr2 = (grid.GetAccumulatedDx(Ri2))*sint*cosp;
	for (int j = Rj1; j < Rj2; j++) {
		dy = grid.GetDy(j);
		dr3 = (grid.GetAccumulatedDy(j) + dy/2.)*sint*sinp;
		jj = j-Rj1;
		for (int k = Rk1; k < Rk2; k++) {
			dz = grid.GetDz(k);
			dr4 = (grid.GetAccumulatedDz(k)+dz/2.)*cost;
			kk = k-Rk1;
			Jy = std::complex<double>(HzJKb1[jj][kk][f],HzJKb2[jj][kk][f]);
			Jz = std::complex<double>(-HyJKb1[jj][kk][f],-HyJKb2[jj][kk][f]);
			My = std::complex<double>(-EzJKb1[jj][kk][f],-EzJKb2[jj][kk][f]);
			Mz = std::complex<double>(EyJKb1[jj][kk][f],EyJKb2[jj][kk][f]);
			r = dr1+dr3+dr4;
			ejkr = polar<double>(1,kapa[f]*r)*dy*dz;
			//       #pragma omp critical
			{
				NTheta += (Jy*cost*sinp - Jz*sint)*ejkr;
				NPhi += (Jy*cosp)*ejkr;
				LTheta += (My*cost*sinp - Mz*sint)*ejkr;
				LPhi += (My*cosp)*ejkr;
			}
			Jy = std::complex<double>(-HzJKt1[jj][kk][f],-HzJKt2[jj][kk][f]);
			Jz = std::complex<double>(HyJKt1[jj][kk][f],HyJKt2[jj][kk][f]);
			My = std::complex<double>(EzJKt1[jj][kk][f],EzJKt2[jj][kk][f]);
			Mz = std::complex<double>(-EyJKt1[jj][kk][f],-EyJKt2[jj][kk][f]);
			r = dr2+dr3+dr4;
			ejkr = polar<double>(1,kapa[f]*r)*dy*dz;
			//       #pragma omp critical
			{
				NTheta += (Jy*cost*sinp - Jz*sint)*ejkr;
				NPhi += (Jy*cosp)*ejkr;
				LTheta += (My*cost*sinp - Mz*sint)*ejkr;
				LPhi += (My*cosp)*ejkr;
			}
		}
	}

	//Faces Y
//   #pragma omp parallel for private(i,k,Jx,Jz,Mx,Mz,dx,dz,ii,kk,r,ejkr)
	dr1 = (grid.GetAccumulatedDy(Rj1))*sint*sinp;
	dr2 = (grid.GetAccumulatedDy(Rj2))*sint*sinp;
	for (int i = Ri1; i < Ri2; i++) {
		dx = grid.GetDx(i);
		dr3 = (grid.GetAccumulatedDx(i)+dx/2.)*sint*cosp;
		ii = i-Ri1;
		for (int k = Rk1; k < Rk2; k++) {
			dz = grid.GetDz(k);
			dr4 = (grid.GetAccumulatedDz(k)+dz/2.)*cost;
			kk = k-Rk1;
			Jx = std::complex<double>(-HzIKb1[ii][kk][f],-HzIKb2[ii][kk][f]);
			Jz = std::complex<double>(HxIKb1[ii][kk][f],HxIKb2[ii][kk][f]);
			Mx = std::complex<double>(EzIKb1[ii][kk][f],EzIKb2[ii][kk][f]);
			Mz = std::complex<double>(-ExIKb1[ii][kk][f],-ExIKb2[ii][kk][f]);
			r = dr1+dr3+dr4;
			ejkr = polar<double>(1,kapa[f]*r)*dx*dz;
			//       #pragma omp critical
			{
				NTheta += (Jx*cost*cosp - Jz*sint)*ejkr;
				NPhi += (-Jx*sinp)*ejkr;
				LTheta += (Mx*cost*cosp - Mz*sint)*ejkr;
				LPhi += (-Mx*sinp)*ejkr;
			}
			Jx = std::complex<double>(HzIKt1[ii][kk][f],HzIKt2[ii][kk][f]);
			Jz = std::complex<double>(-HxIKt1[ii][kk][f],-HxIKt2[ii][kk][f]);
			Mx = std::complex<double>(-EzIKt1[ii][kk][f],-EzIKt2[ii][kk][f]);
			Mz = std::complex<double>(ExIKt1[ii][kk][f],ExIKt2[ii][kk][f]);
			r = dr2+dr3+dr4;
			ejkr = polar<double>(1,kapa[f]*r)*dx*dz;
			//       #pragma omp critical
			{
				NTheta += (Jx*cost*cosp - Jz*sint)*ejkr;
				NPhi += (-Jx*sinp)*ejkr;
				LTheta += (Mx*cost*cosp - Mz*sint)*ejkr;
				LPhi += (-Mx*sinp)*ejkr;
			}
		}
	}
	//Faces Z
	//   #pragma omp parallel for private(i,j,Jx,Jy,Mx,My,dx,dy,ii,jj,r,ejkr)
	dr1 = (grid.GetAccumulatedDz(Rk1))*cost;
	dr2 = (grid.GetAccumulatedDz(Rk2))*cost;
	for (int i = Ri1; i < Ri2; i++) {
		dx = grid.GetDx(i);
		dr3 = (grid.GetAccumulatedDx(i)+dx/2.)*sint*cosp;
		ii = i-Ri1;
		for (int j = Rj1; j < Rj2; j++) {
			dy = grid.GetDy(j);
			dr4 = (grid.GetAccumulatedDy(j)+dy/2.)*sint*sinp;
			jj = j-Rj1;
			Jx = std::complex<double>(HyIJb1[ii][jj][f],HyIJb2[ii][jj][f]);
			Jy = std::complex<double>(-HxIJb1[ii][jj][f],-HxIJb2[ii][jj][f]);
			Mx = std::complex<double>(-EyIJb1[ii][jj][f],-EyIJb2[ii][jj][f]);
			My = std::complex<double>(ExIJb1[ii][jj][f],ExIJb2[ii][jj][f]);
			r = dr1+dr3+dr4;
			ejkr = polar<double>(1,kapa[f]*r)*dx*dy;
			//       #pragma omp critical
			{
				NTheta += (Jx*cost*cosp + Jy*cost*sinp)*ejkr;
				NPhi += (-Jx*sinp+Jy*cosp)*ejkr;
				LTheta += (Mx*cost*cosp + My*cost*sinp)*ejkr;
				LPhi += (-Mx*sinp + My*cosp)*ejkr;
			}
			Jx = std::complex<double>(-HyIJt1[ii][jj][f],-HyIJt2[ii][jj][f]);
			Jy = std::complex<double>(HxIJt1[ii][jj][f],HxIJt2[ii][jj][f]);
			Mx = std::complex<double>(EyIJt1[ii][jj][f],EyIJt2[ii][jj][f]);
			My = std::complex<double>(-ExIJt1[ii][jj][f],-ExIJt2[ii][jj][f]);
			r = dr2+dr3+dr4;
			ejkr = polar<double>(1,kapa[f]*r)*dx*dy;
			//       #pragma omp critical
			{
				NTheta += (Jx*cost*cosp + Jy*cost*sinp)*ejkr;
				NPhi += (-Jx*sinp+Jy*cosp)*ejkr;
				LTheta += (Mx*cost*cosp + My*cost*sinp)*ejkr;
				LPhi += (-Mx*sinp + My*cosp)*ejkr;
			}
		}
	}
	return kapa[f]*kapa[f]*(abs(LPhi + NTheta)*abs(LPhi + NTheta)
				+ abs(LTheta - NPhi)*abs(LTheta - NPhi));
}

bool RadiationPatternFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetXmin();
	xmax = dto.GetXmax();
	ymin = dto.GetYmin();
	ymax = dto.GetYmax();
	zmin = dto.GetZmin();
	zmax = dto.GetZmax();

	return true;
}
bool RadiationPatternFDTDCore::HasResults() {
	return true;
}

ElementResults RadiationPatternFDTDCore::GetElementsResults() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int NFreq = dto.GetNFrequency();

	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;

	/* A primeira coluna tem o ângulo em graus em que é feito o cálculo do diagrama de radiação */
	GenericTable::ColumnDataRepresentation degreeColumn;
	for (int d = 0; d < 360; d++) {
		degreeColumn.push_back(d);
	}
	/* O nome da primeira coluna é o ângulo. Das outras, é a frequencia em que o diagrama de radiação foi calculado */
	vector<wxString> columnsName;
	columnsName.push_back("Angle (degree)");
	for (int f = 0; f < NFreq; f++) {
		wxString str = Converter::DoubleToFormattedString(frequency[f]/normalized_frequency_factor, 1);
		columnsName.push_back(str.Append(" ").Append(normalized_frequency_label));
	}

	/* Cria as tabelas. São 3, uma para cada plano. */
	GenericTable dataXYPlane;
	GenericTable dataYZPlane;
	GenericTable dataZXPlane;
	// Adiciona o rótulo das colunas
	dataXYPlane.SetColumnsLabel(columnsName);
	dataYZPlane.SetColumnsLabel(columnsName);
	dataZXPlane.SetColumnsLabel(columnsName);
	// Para cada tabela, adiciona a coluna contendo os ângulos
	dataXYPlane.AddColumn(degreeColumn);
	dataYZPlane.AddColumn(degreeColumn);
	dataZXPlane.AddColumn(degreeColumn);
	// Adiciona as colunas para os 3 planos
	for (int f = 0; f < NFreq; f++) {
		dataXYPlane.AddColumn(GenericTable::ColumnDataRepresentation());
		dataYZPlane.AddColumn(GenericTable::ColumnDataRepresentation());
		dataZXPlane.AddColumn(GenericTable::ColumnDataRepresentation());
	}
	/// Adiciona as linhas nas colunas
	for (int f = 0; f < NFreq; f++) {
		for (int d = 0; d < 360; d++) {
			// Usa f+1 porque a primeira coluna contém as informações sobre o ângulo em que o diagrama foi calculado.
			dataXYPlane.AppendInColumn(f+1, PLANOXY[d][f]);
			dataYZPlane.AppendInColumn(f+1, PLANOYZ[d][f]);
			dataZXPlane.AppendInColumn(f+1, PLANOZX[d][f]);
		}
	}

	/* Cada linha é mostrada para um*/
	list<ResultSmartPointer> result;

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(true);

	Plane xy, yz, zx; xy.SetValue(XY); yz.SetValue(YZ); zx.SetValue(XZ);
	result.push_back(ResultSmartPointer(new RadiationPatternResult("XY Plane", dataXYPlane, canBeInterpretedAsChart, xy)));
	result.push_back(ResultSmartPointer(new RadiationPatternResult("YZ Plane", dataYZPlane, canBeInterpretedAsChart, yz)));
	result.push_back(ResultSmartPointer(new RadiationPatternResult("ZX Plane", dataZXPlane, canBeInterpretedAsChart, zx)));

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}

bool RadiationPatternFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid& grid = engine->GetGrid();

	cout << "IsElementConsistent\n";
	cout << dto.GetXmin() << endl;
	cout << dto.GetYmin() << endl;
	cout << dto.GetZmin() << endl;
	cout << dto.GetXmax() << endl;
	cout << dto.GetYmax() << endl;
	cout << dto.GetZmax() << endl;

	if (grid.GetXCell(dto.GetXmin()) <= grid.GetXCell(grid.GetXMin()) + 1) {
		wxString errorMessage = "Lower boundary (X) of " + GetName() + " should be after the second cell";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}
	if (grid.GetYCell(dto.GetYmin()) <= grid.GetYCell(grid.GetYMin()) + 1) {
		wxString errorMessage = "Lower boundary (Y) of " + GetName() + " should be after the second cell";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}
	if (grid.GetZCell(dto.GetZmin()) <= grid.GetZCell(grid.GetZMin()) + 1) {
		wxString errorMessage = "Lower boundary (Z) of " + GetName() + " should be after the second cell";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}
	if (grid.GetXCell(dto.GetXmax()) >= grid.GetXCell(grid.GetXMax())-1) {
		wxString errorMessage = "Upper boundary (X) of " + GetName() + " should be before the second last cell";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}
	if (grid.GetYCell(dto.GetYmax()) >= grid.GetYCell(grid.GetYMax())-1) {
		wxString errorMessage = "Upper boundary (Y) of " + GetName() + " should be before the second last cell";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}
	if (grid.GetZCell(dto.GetZmax()) >= grid.GetZCell(grid.GetZMax())-1) {
		wxString errorMessage = "Upper boundary (Z) of " + GetName() + " should be before the second last cell";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}
	return elementOK;
}
