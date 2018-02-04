/*
 * DipoleFDTDCore.cpp
 *
 *  Created on: 10/12/2011
 *      Author: Leandro
 */

#include "DipoleFDTDCore.h"

#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"
#include "emstudio/moderator/Moderator.h"

DipoleFDTDCore::DipoleFDTDCore() : velocity_factor(1.0) {

}

DipoleFDTDCore::~DipoleFDTDCore() {
}


ElementCoreSmartPointer DipoleFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new DipoleFDTDCore);
}

void DipoleFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	DipoleDTO* dipoleDTO = static_cast<DipoleDTO*>(elementDTOSmartPtr.get());

	dto = *dipoleDTO;
}

void DipoleFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	iExcitation = i1 = i2 = engine->GetGrid().GetXCell(dto.GetX());
	jExcitation = j1 = j2 = engine->GetGrid().GetYCell(dto.GetY());
	kExcitation = k1 = k2 = engine->GetGrid().GetZCell(dto.GetZ());

	int orientation = dto.GetOrientation().GetValue();
	int length = 0;
	if (orientation == X) {
		deltaSExcitation = engine->GetGrid().GetDx(iExcitation);
		i1 = engine->GetGrid().GetXCell(dto.GetX() - dto.GetLength()/2 + deltaSExcitation/2);
		i2 = iExcitation + (iExcitation - i1) + 1;
		length = i2-i1;
	} else if (orientation == Y) {
		deltaSExcitation = engine->GetGrid().GetDy(jExcitation);
		j1 = engine->GetGrid().GetYCell(dto.GetY() - dto.GetLength()/2 + deltaSExcitation/2);
		j2 = jExcitation + (jExcitation - j1) + 1;
		length = j2-j1;
	} else if (orientation == Z) {
		deltaSExcitation = engine->GetGrid().GetDz(kExcitation);
		k1 = engine->GetGrid().GetZCell(dto.GetZ() - dto.GetLength()/2 + deltaSExcitation/2);
		k2 = kExcitation + (kExcitation - k1) + 1;
		length = k2-k1;
	}

	HLeft   = Array1D<double>(length+1,0.0); // Alterado para +1
	HRight  = Array1D<double>(length+1,0.0);
	HFront  = Array1D<double>(length+1,0.0);
	HBottom = Array1D<double>(length+1,0.0);

	V = Array1D<double>(dto.GetLinePoints(),0.0);
	I = Array1D<double>(dto.GetLinePoints(),0.0);

	c_times_dt = SPEED_OF_LIGHT_VACUUM * engine->GetDeltaT();

	excitationValue = Array1D<double>(engine->GetTimeSteps(),0.0);
	timeE = Array1D<double>(engine->GetTimeSteps(),0.0);
	timeH = Array1D<double>(engine->GetTimeSteps(),0.0);
	VOut = Array1D<double>(engine->GetTimeSteps(), 0.0);
	IOut = Array1D<double>(engine->GetTimeSteps(), 0.0);
//	VRef = Array1D<double>(engine->GetTimeSteps(), 0.0);

	int NFreq = dto.GetNFrequency();

	RD1 = Array1D<double>(NFreq,0.0);
	RD2 = Array1D<double>(NFreq,0.0);
	VF1 = Array1D<double>(NFreq,0.0);
	VF2 = Array1D<double>(NFreq,0.0);
//	VR1 = Array1D<double>(NFreq,0.0);
//	VR2 = Array1D<double>(NFreq,0.0);
//	VI1 = Array1D<double>(NFreq,0.0);
//	VI2 = Array1D<double>(NFreq,0.0);
	IF1 = Array1D<double>(NFreq,0.0);
	IF2 = Array1D<double>(NFreq,0.0);
	Zout1 = Array1D<double>(NFreq,0.0);
	Zout2 = Array1D<double>(NFreq,0.0);
	VSWR = Array1D<double>(NFreq,0.0);
	S11 = Array1D<double>(NFreq,0.0);
	PreviousV = Array2D<double>(3,2,0.0);

	omega = Array1D<double>(NFreq,0.0);
	frequency = Array1D<double>(NFreq,0.0);
	double FInit = dto.GetInitialFrequency();
	double FStep = dto.GetFrequencyStep();
	for (int f = 0; f < NFreq; f++) {
		omega[f] = 2.0*PI*(FInit + f*FStep);
		frequency[f] = FInit + f*FStep;
	}
	Sc_1D_lower = c_times_dt/deltaSExcitation;

	dto.GetExcitation().Init();
}

void DipoleFDTDCore::DFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int T = engine->GetCurrentInterationNumber();

	int linePoints = dto.GetLinePoints();
	int sourcePoints = dto.GetSourcePoints();
	double Z0 = dto.GetLineImpedance();
	int NFreq = dto.GetNFrequency();

	double V1;
	double S = dto.GetExcitation().GetExcitationValue(t);
	excitationValue[T] = S;
	timeE[T] = t;

	V1 = V[1];

	for (int l = 1; l < linePoints; l++) {
		V[l] = V[l] - c_times_dt*Z0*(I[l]-I[l-1])/deltaSExcitation;
	}
	//V[sourcePoints] += S;
	V[sourcePoints] = V[sourcePoints] - Z0*c_times_dt*(I[sourcePoints]-I[sourcePoints-1])/deltaSExcitation
			+ c_times_dt*S/deltaSExcitation;

	// ABC (Carga de terminacao com R = Z0)
	V[0] = (-1/(1/Sc_1D_lower+2+Sc_1D_lower))*(
		(1/Sc_1D_lower-2+Sc_1D_lower)*(V[2]+PreviousV[0][0])
		+ 2*(Sc_1D_lower-1/Sc_1D_lower)*(PreviousV[0][1]+PreviousV[2][1]-V[1]-PreviousV[1][0])
		- 4*(1/Sc_1D_lower+Sc_1D_lower)*PreviousV[1][1]) - PreviousV[2][0];
	//update the field history values
	PreviousV[0][0] = PreviousV[0][1];
	PreviousV[1][0] = PreviousV[1][1];
	PreviousV[2][0] = PreviousV[2][1];
	PreviousV[0][1] = V[0];
	PreviousV[1][1] = V[1];
	PreviousV[2][1] = V[2];

	VOut[T] = V[linePoints-1];

	for (int f = 0; f < NFreq; f++)	{
		RD1[f] = cos(-omega[f]*t);
		RD2[f] = sin(-omega[f]*t);
		VF1[f] += VOut[T]*RD1[f];
		VF2[f] += VOut[T]*RD2[f];
	}

}
void DipoleFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int orientation = dto.GetOrientation().GetValue();

	// Modelamento do Dipolo
	if (orientation == Z) {
		for (int k = k1; k < k2; k++) {
			engine->SetEz(iExcitation, jExcitation, k, 0.0);
		}
	}
	else if (orientation == X) {
		for (int i = i1; i < i2; i++) {
			engine->SetEx(i, jExcitation, kExcitation, 0.0);
		}
	}
	else if (orientation == Y) {
		for (int j = j1; j < j2; j++) {
			engine->SetEy(iExcitation, j, kExcitation, 0.0);
		}
	}
}

void DipoleFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int T = engine->GetCurrentInterationNumber();
//	double dt = engine->GetDeltaT();

	int orientation = dto.GetOrientation().GetValue();
	int linePoints = dto.GetLinePoints();
	int sourcePoints = dto.GetSourcePoints();
	double Z0 = dto.GetLineImpedance();
	int NFreq = dto.GetNFrequency();
	double radius = dto.GetWireRadius();

	double S = dto.GetExcitation().GetExcitationValue(t);

	class Grid grid = engine->GetGrid();
	double value;

	timeH[T] = t;
	Itmp = 0;

	for (int l = 0; l < linePoints-1; l++) {
		I[l] = I[l] - c_times_dt*(V[l+1] - V[l])/deltaSExcitation/Z0;
	}
	I[sourcePoints] = I[sourcePoints] - c_times_dt*(V[sourcePoints+1] - V[sourcePoints])/deltaSExcitation/Z0
			+ c_times_dt*S/Z0/deltaSExcitation;

	// Acoplamento 1D -> 3D
	if (orientation == Z) {
		value = HRight[kExcitation-k1] - c_times_dt/grid.GetDz(kExcitation)*
				(engine->GetEx(i1, j1, kExcitation+1) - engine->GetEx(i1, j1, kExcitation)
				 - 2*V[linePoints-1]/log(grid.GetDx(i1)/radius)/grid.GetDx(i1))
				 + c_times_dt/grid.GetDx(i1)*2/log(grid.GetDx(i1)/radius)*
				 engine->GetEz(i1+1, j1, kExcitation);
		engine->SetHy(i1, j1, kExcitation, value);

		value = HLeft[kExcitation-k1] - c_times_dt/grid.GetDz(kExcitation)*
				(engine->GetEx(i1-1, j1, kExcitation+1) - engine->GetEx(i1-1, j1, kExcitation)
				+ 2*V[linePoints-1]/log(grid.GetDx(i1-1)/radius)/grid.GetDx(i1-1))
				- c_times_dt/grid.GetDx(i1-1)*2/log(grid.GetDx(i1-1)/radius)*
				engine->GetEz(i1-1, j1, kExcitation);
		engine->SetHy(i1-1, j1, kExcitation, value);

		value = HBottom[kExcitation-k1] + c_times_dt/grid.GetDz(kExcitation)*
				(engine->GetEy(i1, j1, kExcitation+1) - engine->GetEy(i1, j1, kExcitation)
				- 2*V[linePoints-1]/log(grid.GetDy(j1)/radius)/grid.GetDy(j1))
				- c_times_dt/grid.GetDy(j1)*2/log(grid.GetDy(j1)/radius)*
				engine->GetEz(i1, j1+1, kExcitation);
		engine->SetHx(i1, j1, kExcitation, value);

		value = HFront[kExcitation-k1] + c_times_dt/grid.GetDz(kExcitation)*
				(engine->GetEy(i1, j1-1, kExcitation+1) - engine->GetEy(i1, j1-1, kExcitation)
				+ 2*V[linePoints-1]/log(grid.GetDy(j1-1)/radius)/grid.GetDy(j1-1))
				+ c_times_dt/grid.GetDy(j1-1)*2/log(grid.GetDy(j1-1)/radius)*
				engine->GetEz(i1, j1-1, kExcitation);
		engine->SetHx(i1, j1-1, kExcitation, value);

		HRight[kExcitation-k1]  = engine->GetHy(i1, j1, kExcitation);
		HLeft[kExcitation-k1]   = engine->GetHy(i1-1, j1, kExcitation);
		 HBottom[kExcitation-k1] = engine->GetHx(i1, j1, kExcitation);
		 HFront[kExcitation-k1] = engine->GetHx(i1, j1-1, kExcitation);
	} else if (orientation == X) {
		value = HRight[iExcitation-i1] + c_times_dt/grid.GetDx(iExcitation)*
				(engine->GetEz(iExcitation+1, j1, k1-1) - engine->GetEz(iExcitation, j1, k1-1)
				 + 2*V[linePoints-1]/log(grid.GetDz(k1-1)/radius)/grid.GetDz(k1-1))
				 + c_times_dt/grid.GetDz(k1-1)*2/log(grid.GetDz(k1-1)/radius)*
				 engine->GetEx(iExcitation, j1, k1-1);
		engine->SetHy(iExcitation, j1, k1-1, value);

		value = HLeft[iExcitation-i1] + c_times_dt/grid.GetDx(iExcitation)*
				(engine->GetEz(iExcitation+1, j1, k1) - engine->GetEz(iExcitation, j1, k1)
				- 2*V[linePoints-1]/log(grid.GetDz(k1)/radius)/grid.GetDz(k1))
				- c_times_dt/grid.GetDz(k1)*2/log(grid.GetDz(k1)/radius)*
				engine->GetEx(iExcitation, j1, k1+1);
		engine->SetHy(iExcitation, j1, k1, value);

		value = HFront[iExcitation-i1] + c_times_dt/grid.GetDx(iExcitation)*
				(engine->GetEy(iExcitation, j1-1, k1) - engine->GetEy(iExcitation+1, j1-1, k1)
				- 2*V[linePoints-1]/log(grid.GetDy(j1-1)/radius)/grid.GetDy(j1-1))
				- c_times_dt/grid.GetDy(j1-1)*2/log(grid.GetDy(j1-1)/radius)*
				engine->GetEx(iExcitation, j1-1, k1);
		engine->SetHz(iExcitation, j1-1, k1, value);

		value = HBottom[iExcitation-i1] + c_times_dt/grid.GetDx(iExcitation)*
				(engine->GetEy(iExcitation, j1, k1) - engine->GetEy(iExcitation+1, j1, k1)
				+ 2*V[linePoints-1]/log(grid.GetDy(j1)/radius)/grid.GetDy(j1))
				+ c_times_dt/grid.GetDy(j1)*2/log(grid.GetDy(j1)/radius)*
				engine->GetEx(iExcitation, j1+1, k1);
		engine->SetHz(iExcitation, j1, k1, value);

		HRight[iExcitation-i1]  = engine->GetHy(iExcitation, j1, k1-1);
		HLeft[iExcitation-i1]   = engine->GetHy(iExcitation, j1, k1);
		HFront[iExcitation-i1]  = engine->GetHz(iExcitation, j1-1, k1);
		HBottom[iExcitation-i1] = engine->GetHz(iExcitation, j1, k1);
	} else {
		value = HRight[jExcitation-j1] + c_times_dt/grid.GetDy(jExcitation)*
				(engine->GetEx(i1-1, jExcitation+1, k1) - engine->GetEx(i1-1, jExcitation, k1)
				 + 2*V[linePoints-1]/log(grid.GetDx(i1-1)/radius)/grid.GetDx(i1-1))
				 + c_times_dt/grid.GetDx(i1-1)*2/log(grid.GetDx(i1-1)/radius)*
				 engine->GetEy(i1-1, jExcitation, k1);
		engine->SetHz(i1-1, jExcitation, k1, value);

		value = HLeft[jExcitation-j1] + c_times_dt/grid.GetDy(jExcitation)*
				(engine->GetEx(i1, jExcitation+1, k1) - engine->GetEx(i1, jExcitation, k1)
				- 2*V[linePoints-1]/log(grid.GetDx(i1)/radius)/grid.GetDx(i1))
				- c_times_dt/grid.GetDx(i1)*2/log(grid.GetDx(i1)/radius)*
				engine->GetEy(i1+1, jExcitation, k1);
		engine->SetHz(i1, jExcitation, k1, value);

		value = HFront[jExcitation-j1] + c_times_dt/grid.GetDy(jExcitation)*
				(engine->GetEz(i1, jExcitation, k1-1) - engine->GetEz(i1, jExcitation+1, k1-1)
				- 2*V[linePoints-1]/log(grid.GetDz(k1-1)/radius)/grid.GetDz(k1-1))
				- c_times_dt/grid.GetDz(k1-1)*2/log(grid.GetDz(k1-1)/radius)*
				engine->GetEy(i1, jExcitation, k1-1);
		engine->SetHx(i1, jExcitation, k1-1, value);

		value = HBottom[jExcitation-j1] + c_times_dt/grid.GetDy(jExcitation)*
				(engine->GetEz(i1, jExcitation, k1) - engine->GetEz(i1, jExcitation+1, k1)
				+ 2*V[linePoints-1]/log(grid.GetDz(k1)/radius)/grid.GetDz(k1))
				+ c_times_dt/grid.GetDz(k1)*2/log(grid.GetDz(k1)/radius)*
				engine->GetEy(i1, jExcitation, k1+1);
		engine->SetHx(i1, jExcitation, k1, value);

		HRight[jExcitation-j1]  = engine->GetHz(i1-1, jExcitation, k1);
		HLeft[jExcitation-j1]   = engine->GetHz(i1, jExcitation, k1);
		HFront[jExcitation-j1]  = engine->GetHx(i1, jExcitation, k1-1);
		HBottom[jExcitation-j1] = engine->GetHx(i1, jExcitation, k1);
	}

	//Acoplamento 3D -> 1D
	if (orientation == Z)
	{
		I[linePoints-1] = grid.GetDx(i1)*
				(engine->GetHx(i1, j1-1, kExcitation) -
				engine->GetHx(i1, j1, kExcitation))
				+ grid.GetDy(j1)*
				(engine->GetHy(i1, j1, kExcitation) -
				engine->GetHy(i1-1, j1, kExcitation));

		Itmp = HBottom[kExcitation-k1]*grid.GetDx(i1-1)
				- HFront[kExcitation-k1]*grid.GetDx(i1)
				+ HRight[kExcitation-k1]*grid.GetDy(j1)
				- HLeft[kExcitation-k1]*grid.GetDy(j1-1);

	} else if (orientation == X) {
		I[linePoints-1] = grid.GetDz(k1)*
				(engine->GetHz(iExcitation, j1, k1) -
				engine->GetHz(iExcitation, j1-1, k1))
				+ grid.GetDy(j1)*
				(engine->GetHy(iExcitation, j1, k1-1) -
				engine->GetHy(iExcitation, j1, k1));
	} else {
		I[linePoints-1] = grid.GetDx(i1)*
				(engine->GetHx(i1, jExcitation, k1) -
				engine->GetHx(i1, jExcitation, k1-1))
				+ grid.GetDz(k1)*
				(engine->GetHz(i1-1, jExcitation, k1) -
				engine->GetHz(i1, jExcitation, k1));
	}

	I[linePoints-1] = I[linePoints-1]/ETA0;
	   IOut[T] = Itmp/ETA0;
	//I[linePoints-1] = V[linePoints-1]/Z0;

    // Média da corrente, para considerar o mesmo ponto de mediação da tensão.
	IOut[T] = I[linePoints-1];//(I[linePoints-1] + I[linePoints-2])/2;//

	// Modelamento do dipolo
	if (orientation == Z) {
		for (int l = k1; l < k2; l++) {
			if (l == kExcitation) continue;

			value = HRight[l-k1] - c_times_dt/grid.GetDz(l)*
					(engine->GetEx(i1, j1, l+1) - engine->GetEx(i1, j1, l))
					 + c_times_dt/grid.GetDx(i1)*2/log(grid.GetDx(i1)/radius)*
					 engine->GetEz(i1+1, j1, l);
			engine->SetHy(i1, j1, l, value);

			value = HLeft[l-k1] - c_times_dt/grid.GetDz(l)*
					(engine->GetEx(i1-1, j1, l+1) - engine->GetEx(i1-1, j1, l))
					- c_times_dt/grid.GetDx(i1-1)*2/log(grid.GetDx(i1-1)/radius)*
					engine->GetEz(i1-1, j1, l);
			engine->SetHy(i1-1, j1, l, value);

			value = HBottom[l-k1] + c_times_dt/grid.GetDz(l)*
					(engine->GetEy(i1, j1, l+1) - engine->GetEy(i1, j1, l))
					- c_times_dt/grid.GetDy(j1)*2/log(grid.GetDy(j1)/radius)*
					engine->GetEz(i1, j1+1, l);
			engine->SetHx(i1, j1, l, value);

			value = HFront[l-k1] + c_times_dt/grid.GetDz(l)*
					(engine->GetEy(i1, j1-1, l+1) - engine->GetEy(i1, j1-1, l))
					+ c_times_dt/grid.GetDy(j1-1)*2/log(grid.GetDy(j1-1)/radius)*
					engine->GetEz(i1, j1-1, l);
			engine->SetHx(i1, j1-1, l, value);

			HRight[l-k1]  = engine->GetHy(i1, j1, l);
			HLeft[l-k1]   = engine->GetHy(i1-1, j1, l);
			HBottom[l-k1] = engine->GetHx(i1, j1, l);
			HFront[l-k1]  = engine->GetHx(i1, j1-1, l);
		}
	} else if (orientation == X) {
		for (int l = i1; l < i2; l++) {
			if (l == iExcitation) continue;

			value = HRight[l-i1] + c_times_dt/grid.GetDx(l)*
					(engine->GetEz(l+1, j1, k1-1) - engine->GetEz(l, j1, k1-1))
					 + c_times_dt/grid.GetDz(k1-1)*2/log(grid.GetDz(k1-1)/radius)*
					 engine->GetEx(l, j1, k1-1);
			engine->SetHy(l, j1, k1-1, value);

			value = HLeft[l-i1] + c_times_dt/grid.GetDx(l)*
					(engine->GetEz(l+1, j1, k1) - engine->GetEz(l, j1, k1))
					- c_times_dt/grid.GetDz(k1)*2/log(grid.GetDz(k1)/radius)*
					engine->GetEx(l, j1, k1+1);
			engine->SetHy(l, j1, k1, value);

			value = HFront[l-i1] + c_times_dt/grid.GetDx(l)*
					(engine->GetEy(l, j1-1, k1) - engine->GetEy(l+1, j1-1, k1))
					- c_times_dt/grid.GetDy(j1-1)*2/log(grid.GetDy(j1-1)/radius)*
					engine->GetEx(l, j1-1, k1);
			engine->SetHz(l, j1-1, k1, value);

			value = HBottom[l-i1] + c_times_dt/grid.GetDx(l)*
					(engine->GetEy(l, j1, k1) - engine->GetEy(l+1, j1, k1))
					+ c_times_dt/grid.GetDy(j1)*2/log(grid.GetDy(j1)/radius)*
					engine->GetEx(l, j1+1, k1);
			engine->SetHz(l, j1, k1, value);

			HRight[l-i1]  = engine->GetHy(l, j1, k1-1);
			HLeft[l-i1]   = engine->GetHy(l, j1, k1);
			HFront[l-i1]  = engine->GetHz(l, j1-1, k1);
			HBottom[l-i1] = engine->GetHz(l, j1, k1);
		}
	} else {
		for (int l = j1; l < j2; l++) {
			if (l == jExcitation) continue;
			value = HRight[l-j1] + c_times_dt/grid.GetDy(l)*
					(engine->GetEx(i1-1, l+1, k1) - engine->GetEx(i1-1, l, k1))
					 + c_times_dt/grid.GetDx(i1-1)*2/log(grid.GetDx(i1-1)/radius)*
					 engine->GetEy(i1-1, l, k1);
			engine->SetHz(i1-1, l, k1, value);

			value = HLeft[l-j1] + c_times_dt/grid.GetDy(l)*
					(engine->GetEx(i1, l+1, k1) - engine->GetEx(i1, l, k1))
					- c_times_dt/grid.GetDx(i1)*2/log(grid.GetDx(i1)/radius)*
					engine->GetEy(i1+1, l, k1);
			engine->SetHz(i1, l, k1, value);

			value = HFront[l-j1] + c_times_dt/grid.GetDy(l)*
					(engine->GetEz(i1, l, k1-1) - engine->GetEz(i1, l+1, k1-1))
					- c_times_dt/grid.GetDz(k1-1)*2/log(grid.GetDz(k1-1)/radius)*
					engine->GetEy(i1, l, k1-1);
			engine->SetHx(i1, l, k1-1, value);

			value = HBottom[l-j1] + c_times_dt/grid.GetDy(l)*
					(engine->GetEz(i1, l, k1) - engine->GetEz(i1, l+1, k1))
					+ c_times_dt/grid.GetDz(k1)*2/log(grid.GetDz(k1)/radius)*
					engine->GetEy(i1, l, k1+1);
			engine->SetHx(i1, l, k1, value);

			HRight[l-j1]  = engine->GetHz(i1-1, l, k1);
			HLeft[l-j1]   = engine->GetHz(i1, l, k1);
			HFront[l-j1]  = engine->GetHx(i1, l, k1-1);
			HBottom[l-j1] = engine->GetHx(i1, l, k1);
		}
	}

	for (int f = 0; f < NFreq; f++) {
		RD1[f] = cos(-omega[f]*t);
		RD2[f] = sin(-omega[f]*t);
		IF1[f] += IOut[T]*RD1[f];
		IF2[f] += IOut[T]*RD2[f];
	}
}

void DipoleFDTDCore::SimulationWillFinish() {

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double Z0 = dto.GetLineImpedance();
	int NFreq = dto.GetNFrequency();
//	double dt = engine->GetDeltaT();
	int timeSteps = engine->GetTimeSteps();


	complex<double> Vf;
	complex<double> If;
	complex<double> Zf;
	double  s11;
//	complex<double> Vr;
//	complex<double> Vi;
//	complex<double> Vp;
//	complex<double> ejkt;//, ejkr;

	for (int f = 0; f < NFreq; f++) {
		Vf = complex<double>(VF1[f]/timeSteps,VF2[f]/timeSteps);
		If = complex<double>(IF1[f]/timeSteps,IF2[f]/timeSteps);
//		Vi = complex<double>(VI1[f],VI2[f]);
//		Vr = complex<double>(VR1[f],VR2[f]);
//		Vp = complex<double>(VP1[f],VP2[f]);

		//correção no coeficiente de reflexão para a entrada da antena
//		ejkr = polar<double>(1, 0*omega[f]*deltaSExcitation/SPEED_OF_LIGHT_VACUUM);
//		ejkt = polar<double>(1, omega[f]*dt/2);

		//Zf = Z0*(1. + Vr*ejkr/Vi)/(1. - Vr*ejkr/Vi);
//		Zf = Vf*ejkt/If;
		Zf = Vf/If;
		Zout1[f] = real(Zf);
		Zout2[f] = imag(Zf);

		//s11 = abs(Vr/Vi);
		s11 = abs((Zf - complex<double>(Z0,0))/(Zf + complex<double>(Z0,0)));

		if(s11 < 1e-5) s11 = 1e-5;
		S11[f] = 20*log10(s11);

		VSWR[f] = (1 + s11)/(1 - s11);
	}


}


bool DipoleFDTDCore::HasResults() {
	return true;
}
bool DipoleFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	int orientation = dto.GetOrientation().GetValue();
	xmin = dto.GetX();
	ymin = dto.GetY();
	zmin = dto.GetZ();
	xmax = dto.GetX();
	ymax = dto.GetY();
	zmax = dto.GetZ();

	if (orientation == X) {
		xmin -= dto.GetLength()/2;
		xmax += dto.GetLength()/2;
	} else if (orientation == Y) {
		ymin -= dto.GetLength()/2;
		ymax += dto.GetLength()/2;
	} else if (orientation == Z) {
		zmin -= dto.GetLength()/2;
		zmax += dto.GetLength()/2;
	}
	return true;
}

ElementResults DipoleFDTDCore::GetElementsResults() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int steps = engine->GetTimeSteps();
	int NFreq = dto.GetNFrequency();

	/* Pega o rótulo para as variáveis de tempo e frequência, e seu multiplicador */
	wxString normalized_time_label = engine->GetUnits()->GetUserDefinedTimeUnit().first;
	double normalized_time_factor = engine->GetUnits()->GetUserDefinedTimeUnit().second;
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;

	/* Colunas */
	GenericTable::ColumnDataRepresentation timeDataE;
	GenericTable::ColumnDataRepresentation timeDataH;
	GenericTable::ColumnDataRepresentation frequencyData;
	GenericTable::ColumnDataRepresentation vData;
	GenericTable::ColumnDataRepresentation iData;
	GenericTable::ColumnDataRepresentation zrData;
	GenericTable::ColumnDataRepresentation ziData;
	GenericTable::ColumnDataRepresentation s11Data;
	GenericTable::ColumnDataRepresentation vswrData;
	GenericTable::ColumnDataRepresentation excitationData;

	/* Monta a tabela */
	for (int T = 0; T < steps; T++) {
		timeDataE.push_back(timeE[T]/normalized_time_factor);
		timeDataH.push_back(timeH[T]/normalized_time_factor);
		vData.push_back(VOut[T]);
		iData.push_back(IOut[T]*1000);
		excitationData.push_back(excitationValue[T]);
	}

	for (int f = 0; f < NFreq; f++) {
		frequencyData.push_back(frequency[f]/normalized_frequency_factor);
		zrData.push_back(Zout1[f]);
		ziData.push_back(Zout2[f]);
		s11Data.push_back(S11[f]);
		vswrData.push_back(VSWR[f]);
	}
	/* Cria as tabelas e adiciona os dados */
	GenericTable vTable;
	GenericTable iTable;
	GenericTable zTable;
	GenericTable s11Table;
	GenericTable vswrTable;
	GenericTable excitationTable;

	vTable.AddColumn(timeDataE);
	vTable.AddColumn(vData);

	iTable.AddColumn(timeDataH);
	iTable.AddColumn(iData);

	zTable.AddColumn(frequencyData);
	zTable.AddColumn(zrData);
	zTable.AddColumn(ziData);

	s11Table.AddColumn(frequencyData);
	s11Table.AddColumn(s11Data);

	vswrTable.AddColumn(frequencyData);
	vswrTable.AddColumn(vswrData);

	excitationTable.AddColumn(timeDataE);
	excitationTable.AddColumn(excitationData);

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(true);

	/* Adiciona o rótulo das colunas das tabelas */
	wxString timeColumnLabel("Time (");
	timeColumnLabel.Append(normalized_time_label).Append(")");
	wxString frequencyColumnLabel("Frequency (");
	frequencyColumnLabel.Append(normalized_frequency_label).Append(")");

	vector<wxString> outputVoltageColunsLabel;
	outputVoltageColunsLabel.push_back(timeColumnLabel);
	outputVoltageColunsLabel.push_back("Voltage (V)");
	vTable.SetColumnsLabel(outputVoltageColunsLabel);

	vector<wxString> outputCurrentColunsLabel;
	outputCurrentColunsLabel.push_back(timeColumnLabel);
	outputCurrentColunsLabel.push_back("Current (mA)");
	iTable.SetColumnsLabel(outputCurrentColunsLabel);

	vector<wxString> impedanceColunsLabel;
	impedanceColunsLabel.push_back(frequencyColumnLabel);
	impedanceColunsLabel.push_back("Impedance - real (ohms)");
	impedanceColunsLabel.push_back("Impedance - imaginary (ohms)");
	zTable.SetColumnsLabel(impedanceColunsLabel);

	vector<wxString> s11ColumnsLabel;
	s11ColumnsLabel.push_back(frequencyColumnLabel);
	s11ColumnsLabel.push_back("S11 (dB)");
	s11Table.SetColumnsLabel(s11ColumnsLabel);

	vector<wxString> vswrColumnsLabel;
	vswrColumnsLabel.push_back(frequencyColumnLabel);
	vswrColumnsLabel.push_back("VSWR");
	vswrTable.SetColumnsLabel(vswrColumnsLabel);

	vector<wxString> excitationColumnsLabel;
	excitationColumnsLabel.push_back(timeColumnLabel);
	excitationColumnsLabel.push_back("Excitation value");
	excitationTable.SetColumnsLabel(excitationColumnsLabel);

	list<ResultSmartPointer> result;
	result.push_back(ResultSmartPointer(new TableResult("Output voltage", vTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Output current", iTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Impedance", zTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("S11", s11Table, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("VSWR", vswrTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Excitation", excitationTable, canBeInterpretedAsChart)));

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}

bool DipoleFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid grid = engine->GetGrid();

	double radius = dto.GetWireRadius();
	int orientation = dto.GetOrientation().GetValue();

	int iEx = engine->GetGrid().GetXCell(dto.GetX());
	int jEx = engine->GetGrid().GetYCell(dto.GetY());
	int kEx = engine->GetGrid().GetZCell(dto.GetZ());

	cout << "i1 = " << iEx << endl;
	cout << "j1 = " << jEx << endl;
	cout << "k1 = " << kEx << endl;

	if (orientation == Z) {
		if (radius > grid.GetDx(iEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394x/2"));
			AppendErrorMessage(errorMessage);
		}
		if (radius > grid.GetDy(jEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394y/2"));
			AppendErrorMessage(errorMessage);
		}
	}
	if (orientation == X) {
		if (radius > grid.GetDy(jEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394y/2"));
			AppendErrorMessage(errorMessage);
		}
		if (radius > grid.GetDz(kEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394z/2"));
			AppendErrorMessage(errorMessage);
		}
	}
	if (orientation == Y) {
		if (radius > grid.GetDx(iEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394x/2"));
			AppendErrorMessage(errorMessage);
		}
		if (radius > grid.GetDz(kEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394z/2"));
			AppendErrorMessage(errorMessage);
		}
	}
	return elementOK;
}
