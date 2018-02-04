/*
 * MonopoleFDTDCore.cpp
 *
 *  Created on: 21/12/2011
 *      Author: leandrocarisio
 */

#include "MonopoleFDTDCore.h"

#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"


MonopoleFDTDCore::MonopoleFDTDCore() : velocity_factor(1) {

}

MonopoleFDTDCore::~MonopoleFDTDCore() {
}


ElementCoreSmartPointer MonopoleFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new MonopoleFDTDCore);
}

void MonopoleFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	MonopoleDTO* monopoleDTO = static_cast<MonopoleDTO*>(elementDTOSmartPtr.get());

	dto = *monopoleDTO;

	cout << "MonopoleFDTDCore::Configure()" << endl;
}

void MonopoleFDTDCore::SimulationWillStart() {
	cout << "MonopoleFDTDCore::SimulationWillStart()" << endl;

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	iExcitation = i1 = i2 = engine->GetGrid().GetXCell(dto.GetX());
	jExcitation = j1 = j2 = engine->GetGrid().GetYCell(dto.GetY());
	kExcitation = k1 = k2 = engine->GetGrid().GetZCell(dto.GetZ());

	int orientation = dto.GetOrientation().GetValue();
	if (orientation == X) {
		i2 = engine->GetGrid().GetXCell(dto.GetX() + dto.GetLength());
		l1 = i1;
		l2 = i2;
		deltaSExcitation = engine->GetGrid().GetDx(iExcitation);
	}
	else if (orientation == Y) {
		j2 = engine->GetGrid().GetYCell(dto.GetY() + dto.GetLength());
		l1 = j1;
		l2 = j2;
		deltaSExcitation = engine->GetGrid().GetDy(jExcitation);
	}
	else if (orientation == Z) {
		k2 = engine->GetGrid().GetZCell(dto.GetZ() + dto.GetLength());
		l1 = k1;
		l2 = k2;
		deltaSExcitation = engine->GetGrid().GetDz(kExcitation);
	}
	cout << "Ponto inicial (" << i1 << ", " << j1 << ", " << k1 << ")" << endl;
	cout << "Ponto final (" << i2 << ", " << j2 << ", " << k2 << ")" << endl;
	cout << "Ponto meio (" << iExcitation << ", " << jExcitation << ", " << kExcitation << ")" << endl;

	HLeft   = Array1D<double>(l2-l1+1,0.0);
	HRight  = Array1D<double>(l2-l1+1,0.0);
	HFront  = Array1D<double>(l2-l1+1,0.0);
	HBottom = Array1D<double>(l2-l1+1,0.0);

	V = Array1D<double>(dto.GetLinePoints(),0.0);
	I = Array1D<double>(dto.GetLinePoints(),0.0);

	c_times_dt = SPEED_OF_LIGHT_VACUUM * engine->GetDeltaT();

	time = Array1D<double>(engine->GetTimeSteps(),0.0);
	VOut = Array1D<double>(engine->GetTimeSteps(), 0.0);
	IOut = Array1D<double>(engine->GetTimeSteps(), 0.0);
	excitationValue = Array1D<double>(engine->GetTimeSteps(),0.0);
//	VRef = Array1D<double>(engine->GetTimeSteps(), 0.0);
//	VInc = Array1D<double>(engine->GetTimeSteps(), 0.0);

	int Nfreq = dto.GetNFrequency();

	RD1 = Array1D<double>(Nfreq,0.0);
	RD2 = Array1D<double>(Nfreq,0.0);
	VF1 = Array1D<double>(Nfreq,0.0);
	VF2 = Array1D<double>(Nfreq,0.0);
//	VR1 = Array1D<double>(Nfreq,0.0);
//	VR2 = Array1D<double>(Nfreq,0.0);
//	VI1 = Array1D<double>(Nfreq,0.0);
//	VI2 = Array1D<double>(Nfreq,0.0);
	IF1 = Array1D<double>(Nfreq,0.0);
	IF2 = Array1D<double>(Nfreq,0.0);
	Zout1 = Array1D<double>(Nfreq,0.0);
	Zout2 = Array1D<double>(Nfreq,0.0);
	VSWR = Array1D<double>(Nfreq,0.0);
	S11 = Array1D<double>(Nfreq,0.0);

	frequency = Array1D<double>(Nfreq,0.0);
	omega = Array1D<double>(Nfreq,0.0);
	double FInit = dto.GetInitialFrequency();
	double FStep = dto.GetFrequencyStep();
	for (int f = 0; f < Nfreq; f++) {
		frequency[f] = FInit + f*FStep;
		omega[f] = 2.0*PI*(FInit + f*FStep);
	}

	Sc_1D_lower = c_times_dt/deltaSExcitation;
	PreviousVLower = Array2D<double>(3,2, 0.0);

	// Modelamento do Monopolo
	//	Linhas comentadas para começar a usar Mesh. Transferido para ElectricFieldsChanged
//	if (orientation == Z) {
//		for (int k = k1; k < k2; k++) {
//			engine->SetGaz(iExcitation, jExcitation, k, 0.0);
//		}
//	}
//	else if (orientation == X) {
//		for (int i = i1; i < i2; i++) {
//			engine->SetGax(i, jExcitation, kExcitation, 0.0);
//		}
//	}
//	else if (orientation == Y) {
//		for (int j = j1; j < j2; j++) {
//			engine->SetGay(iExcitation, j, kExcitation, 0.0);
//		}
//	}

//	V1 = 0;
//	V2 = 0;

	dto.GetExcitation().Init();
}

void MonopoleFDTDCore::DFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int T = engine->GetCurrentInterationNumber();

//	int orientation = dto.GetOrientation().GetValue();
	int linePoints = dto.GetLinePoints();
	int sourcePoints = dto.GetSourcePoints();
	double Z0 = dto.GetLineImpedance();
	int NFreq = dto.GetNFrequency();

//	double V1 = V[1];
	double S = dto.GetExcitation().GetExcitationValue(t);
	excitationValue[T] = S;

	for (int l = 1; l < linePoints; l++) {
		V[l] = V[l] - c_times_dt*Z0*(I[l]-I[l-1])/deltaSExcitation;
	}
	V[sourcePoints] = V[sourcePoints] - c_times_dt*Z0*(I[sourcePoints]-I[sourcePoints-1])/deltaSExcitation
			+ c_times_dt*S/deltaSExcitation;

	// ABC (Carga de terminacao com R = Z0)
	V[0] = (-1/(1/Sc_1D_lower+2+Sc_1D_lower))*(
			(1/Sc_1D_lower-2+Sc_1D_lower)*(V[2]+PreviousVLower[0][0])
			+ 2*(Sc_1D_lower-1/Sc_1D_lower)*(PreviousVLower[0][1]+PreviousVLower[2][1]-V[1]-PreviousVLower[1][0])
			- 4*(1/Sc_1D_lower+Sc_1D_lower)*PreviousVLower[1][1]) - PreviousVLower[2][0];

	//update the field history values
	PreviousVLower[0][0] = PreviousVLower[0][1];
	PreviousVLower[1][0] = PreviousVLower[1][1];
	PreviousVLower[2][0] = PreviousVLower[2][1];
	PreviousVLower[0][1] = V[0];
	PreviousVLower[1][1] = V[1];
	PreviousVLower[2][1] = V[2];

	VOut[T] = V[linePoints-1];
	time[T] = t;

	for (int f = 0; f < NFreq; f++) {
		RD1[f] = cos(-omega[f]*t);
		RD2[f] = sin(-omega[f]*t);
		VF1[f] += V[linePoints-1]*RD1[f];
		VF2[f] += V[linePoints-1]*RD2[f];
	}
}
void MonopoleFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	int orientation = dto.GetOrientation().GetValue();
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

void MonopoleFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int T = engine->GetCurrentInterationNumber();

	int orientation = dto.GetOrientation().GetValue();
	int linePoints = dto.GetLinePoints();
	int sourcePoints = dto.GetSourcePoints();
	double Z0 = dto.GetLineImpedance();
	int NFreq = dto.GetNFrequency();
	double radius = dto.GetWireRadius();

	double S = dto.GetExcitation().GetExcitationValue(t);
	double value;

	for (int l = 0; l < linePoints-1; l++) {
		I[l] = I[l] - c_times_dt*(V[l+1] - V[l])/deltaSExcitation/Z0;
	}
	I[sourcePoints] = I[sourcePoints] - c_times_dt*(V[sourcePoints+1] - V[sourcePoints])/deltaSExcitation/Z0
			+ c_times_dt*S/Z0/deltaSExcitation;

	class Grid grid = engine->GetGrid();

	if (orientation == Z) {
		value = HRight[l1-k1] - c_times_dt/grid.GetDz(l1)*
				(engine->GetEx(i1, j1, l1+1)
				 - 2*V[linePoints-1]/log(grid.GetDx(i1)/radius)/grid.GetDx(i1))
				 + c_times_dt/grid.GetDx(i1)*2/log(grid.GetDx(i1)/radius)*
				 engine->GetEz(i1+1, j1, l1);
		engine->SetHy(i1, j1, l1, value);

		value = HLeft[l1-k1] - c_times_dt/grid.GetDz(l1)*
				(engine->GetEx(i1-1, j1, l1+1)
				+ 2*V[linePoints-1]/log(grid.GetDx(i1-1)/radius)/grid.GetDx(i1-1))
				- c_times_dt/grid.GetDx(i1-1)*2/log(grid.GetDx(i1-1)/radius)*
				engine->GetEz(i1-1, j1, l1);
		engine->SetHy(i1-1, j1, l1, value);

		value = HBottom[l1-k1] + c_times_dt/grid.GetDz(l1)*
				(engine->GetEy(i1, j1, l1+1)
				- 2*V[linePoints-1]/log(grid.GetDy(j1)/radius)/grid.GetDy(j1))
				- c_times_dt/grid.GetDy(j1)*2/log(grid.GetDy(j1)/radius)*
				engine->GetEz(i1, j1+1, l1);
		engine->SetHx(i1, j1, l1, value);

		value = HFront[l1-k1] + c_times_dt/grid.GetDz(l1)*
				(engine->GetEy(i1, j1-1, l1+1)
				+ 2*V[linePoints-1]/log(grid.GetDy(j1-1)/radius)/grid.GetDy(j1-1))
				+ c_times_dt/grid.GetDy(j1-1)*2/log(grid.GetDy(j1-1)/radius)*
				engine->GetEz(i1, j1-1, l1);
		engine->SetHx(i1, j1-1, l1, value);

		HRight[l1-k1]  = engine->GetHy(i1, j1, l1);
		HLeft[l1-k1]   = engine->GetHy(i1-1, j1, l1);
		HBottom[l1-k1] = engine->GetHx(i1, j1, l1);
		HFront[l1-k1]  = engine->GetHx(i1, j1-1, l1);
	}
	else if (orientation == X)
	{
		value = HRight[l1-i1] + c_times_dt/grid.GetDx(l1)*
				(engine->GetEz(l1+1, j1, k1-1)
				 + 2*V[linePoints-1]/log(grid.GetDz(k1-1)/radius)/grid.GetDz(k1-1))
				 + c_times_dt/grid.GetDz(k1-1)*2/log(grid.GetDz(k1-1)/radius)*
				 engine->GetEx(l1, j1, k1-1);
		engine->SetHy(l1, j1, k1-1, value);

		value = HLeft[l1-i1] + c_times_dt/grid.GetDx(l1)*
				(engine->GetEz(l1+1, j1, k1)
				- 2*V[linePoints-1]/log(grid.GetDz(k1)/radius)/grid.GetDz(k1))
				- c_times_dt/grid.GetDz(k1)*2/log(grid.GetDz(k1)/radius)*
				engine->GetEx(l1, j1, k1+1);
		engine->SetHy(l1, j1, k1, value);

		value = HFront[l1-i1] - c_times_dt/grid.GetDx(l1)*
				(engine->GetEy(l1+1, j1-1, k1)
				+ 2*V[linePoints-1]/log(grid.GetDy(j1-1)/radius)/grid.GetDy(j1-1))
				- c_times_dt/grid.GetDy(j1-1)*2/log(grid.GetDy(j1-1)/radius)*
				engine->GetEx(l1, j1-1, k1);
		engine->SetHz(l1, j1-1, k1, value);

		value = HBottom[l1-i1] - c_times_dt/grid.GetDx(l1)*
				(engine->GetEy(l1+1, j1, k1)
				- 2*V[linePoints-1]/log(grid.GetDy(j1)/radius)/grid.GetDy(j1))
				+ c_times_dt/grid.GetDy(j1)*2/log(grid.GetDy(j1)/radius)*
				engine->GetEx(l1, j1+1, k1);
		engine->SetHz(l1, j1, k1, value);

		HRight[l1-i1]  = engine->GetHy(l1, j1, k1-1);
		HLeft[l1-i1]   = engine->GetHy(l1, j1, k1);
		HFront[l1-i1]  = engine->GetHz(l1, j1-1, k1);
		HBottom[l1-i1] = engine->GetHz(l1, j1, k1);
	}  else if (orientation == Y) {
		value = HRight[l1-j1] + c_times_dt/grid.GetDy(l1)*
				(engine->GetEx(i1-1, l1+1, k1)
				 + 2*V[linePoints-1]/log(grid.GetDx(i1-1)/radius)/grid.GetDx(i1-1))
				 + c_times_dt/grid.GetDx(i1-1)*2/log(grid.GetDx(i1-1)/radius)*
				 engine->GetEy(i1-1, l1, k1);
		engine->SetHz(i1-1, l1, k1, value);

		value = HLeft[l1-j1] + c_times_dt/grid.GetDy(l1)*
				(engine->GetEx(i1, l1+1, k1)
				- 2*V[linePoints-1]/log(grid.GetDx(i1)/radius)/grid.GetDx(i1))
				- c_times_dt/grid.GetDx(i1)*2/log(grid.GetDx(i1)/radius)*
				engine->GetEy(i1+1, l1, k1);
		engine->SetHz(i1, l1, k1, value);

		value = HFront[l1-j1] - c_times_dt/grid.GetDy(l1)*
				(engine->GetEz(i1, l1+1, k1-1)
				+ 2*V[linePoints-1]/log(grid.GetDz(k1-1)/radius)/grid.GetDz(k1-1))
				- c_times_dt/grid.GetDz(k1-1)*2/log(grid.GetDz(k1-1)/radius)*
				engine->GetEy(i1, l1, k1-1);
		engine->SetHx(i1, l1, k1-1, value);

		value = HBottom[l1-j1] - c_times_dt/grid.GetDy(l1)*
				(engine->GetEz(i1, l1+1, k1)
				- 2*V[linePoints-1]/log(grid.GetDz(k1)/radius)/grid.GetDz(k1))
				+ c_times_dt/grid.GetDz(k1)*2/log(grid.GetDz(k1)/radius)*
				engine->GetEy(i1, l1, k1+1);
		engine->SetHx(i1, l1, k1, value);

		HRight[l1-j1]  = engine->GetHz(i1-1, l1, k1);
		HLeft[l1-j1]   = engine->GetHz(i1, l1, k1);
		HFront[l1-j1]  = engine->GetHx(i1, l1, k1-1);
		HBottom[l1-j1] = engine->GetHx(i1, l1, k1);
	}

	//Acoplamento 3D -> 1D
	if (orientation == Z) {
		I[linePoints-1] = grid.GetDx(i1)*
				(engine->GetHx(i1, j1-1, l1) -
				engine->GetHx(i1, j1, l1))/ETA0
				+ grid.GetDy(j1)*
				(engine->GetHy(i1, j1, l1) -
				engine->GetHy(i1-1, j1, l1))/ETA0;
	} else if (orientation == X) {
		I[linePoints-1] = grid.GetDz(k1)*
				(engine->GetHz(l1, j1, k1) -
				engine->GetHz(l1, j1-1, k1))/ETA0
				+ grid.GetDy(j1)*
				(engine->GetHy(l1, j1, k1-1) -
				engine->GetHy(l1, j1, k1))/ETA0;
	} else if (orientation == Y) {
		I[linePoints-1] = grid.GetDx(i1)*
				(engine->GetHx(i1, l1, k1) -
				engine->GetHx(i1, l1, k1-1))/ETA0
				+ grid.GetDz(k1)*
				(engine->GetHz(i1-1, l1, k1) -
				engine->GetHz(i1, l1, k1))/ETA0;

	}

	// Modelamento do monopolo
	for (int l = l1 + 1; l < l2; l++) {
		if (orientation == Z) {
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
		} else if (orientation == X) {
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
		} else if(orientation == Y){
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

	IOut[T] = I[linePoints-1];//(I[LinePoints-1] + I[LinePoints-2])/2;//

	for (int f = 0; f < NFreq; f++)	{
		RD1[f] = cos(-omega[f]*t);
		RD2[f] = sin(-omega[f]*t);
		IF1[f] += I[linePoints-1]*RD1[f];
		IF2[f] += I[linePoints-1]*RD2[f];
	}
}

void MonopoleFDTDCore::SimulationWillFinish() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double Z0 = dto.GetLineImpedance();
	int NFreq = dto.GetNFrequency();
//	double dt = engine->GetDeltaT();
	int timeSteps = engine->GetTimeSteps();

	std::complex<double> Vf;
	std::complex<double> If;
	std::complex<double> Zf;
//	std::complex<double> ejkt;
	double tau;

	for (int f = 0; f < NFreq; f++) {
		Vf = std::complex<double>(VF1[f]/timeSteps,VF2[f]/timeSteps);
		If = std::complex<double>(IF1[f]/timeSteps,IF2[f]/timeSteps);

		//correção no coeficiente de reflexão para a entrada da antena
//		ejkt = polar<double>(1, -omega[f]*dt/2);

		if (If == 0.0) If = std::complex<double>(1e-30,0);
		Zf = Vf/If;
//		Zf = Vf*ejkt/If;
		Zout1[f] = real(Zf);
		Zout2[f] = imag(Zf);

		tau = abs((Zf - std::complex<double>(Z0,0))/(Zf + std::complex<double>(Z0,0)));
		if (tau < 1e-5) tau = 1e-5;
		S11[f] = 20*log10(tau);
		VSWR[f] = (1. + tau)/(1. - tau);
	}
 }

bool MonopoleFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	int orientation = dto.GetOrientation().GetValue();
	xmin = dto.GetX();
	ymin = dto.GetY();
	zmin = dto.GetZ();
	xmax = dto.GetX();
	ymax = dto.GetY();
	zmax = dto.GetZ();

	if (orientation == X) {
		xmax += dto.GetLength();
	} else if (orientation == Y) {
		ymax += dto.GetLength();
	} else if (orientation == Z) {
		zmax += dto.GetLength();
	}
	return true;
}

bool MonopoleFDTDCore::HasResults() {
	return true;
}

ElementResults MonopoleFDTDCore::GetElementsResults() {
	cout << "DipoleFDTDCore::GetElementsResults()" << endl;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int steps = engine->GetTimeSteps();
	int NFreq = dto.GetNFrequency();

	/* Pega o rótulo para as variáveis de tempo e frequência, e seu multiplicador */
	wxString normalized_time_label = engine->GetUnits()->GetUserDefinedTimeUnit().first;
	double normalized_time_factor = engine->GetUnits()->GetUserDefinedTimeUnit().second;
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;

	/* Rótulo das linhas */
	GenericTable::ColumnDataRepresentation timeData;
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
		timeData.push_back(time[T]/normalized_time_factor);
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

	vTable.AddColumn(timeData);
	vTable.AddColumn(vData);

	iTable.AddColumn(timeData);
	iTable.AddColumn(iData);

	zTable.AddColumn(frequencyData);
	zTable.AddColumn(zrData);
	zTable.AddColumn(ziData);

	s11Table.AddColumn(frequencyData);
	s11Table.AddColumn(s11Data);

	vswrTable.AddColumn(frequencyData);
	vswrTable.AddColumn(vswrData);

	excitationTable.AddColumn(timeData);
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

bool MonopoleFDTDCore::IsElementConsistent() {
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
